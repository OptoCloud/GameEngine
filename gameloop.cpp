// gameloop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "gameloop.h"

#include <iostream>
#include <chrono>
#include <thread>

#include <SDL2/SDL_opengl.h>

namespace Game
{
	namespace Window
	{
		constexpr int	   VSYNC_IS_ENABLED = false;
		constexpr uint32_t FLAGS = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
		constexpr uint16_t WIDTH = 640;
		constexpr uint16_t HEIGHT = 480;
	}
}

constexpr uint16_t TARGET_TICKRATE = 60;
constexpr uint16_t TARGET_FRAMERATE = 0;
constexpr uint32_t MICROSECONDS_PER_SECOND = 1000000;
constexpr uint32_t MICROSECONDS_PER_UPDATE = MICROSECONDS_PER_SECOND / TARGET_TICKRATE;
constexpr uint32_t MICROSECONDS_PER_FRAME = TARGET_FRAMERATE > 0 ? MICROSECONDS_PER_SECOND / TARGET_FRAMERATE : 0;

Game::GameWindow::GameWindow(Object* parent) : Object(parent)
{
	windowName = "Window!";
	SetIsRunning(true);
}

Game::GameWindow::~GameWindow()
{
	std::cout << "DECONSTRUCTOR CALLED!" << std::endl;
}

int Game::GameWindow::RunGame()
{
	if (!GetIsRunning()) { return 0; } // @TODO: find a better way to see if game has already been ran

	int retval = Initialize();

	if (retval == 1)
	{
		retval = GameLoop();
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return retval;
}

int Game::GameWindow::Initialize()
{
	int initWindow = InitWindow();
	if (initWindow != 1)
	{
		return -1;
	}
	int initGL = InitOpenGL();
	if (initGL != 1)
	{
		return -1;
	}

	onKeyUp += &OnKeyUp;
	onKeyDown += &OnKeyDown;

	return 1;
}

int Game::GameWindow::InitWindow()
{
	int sdlInitReturn = SDL_Init(SDL_INIT_VIDEO);

	if (sdlInitReturn < 0)
	{
		std::cout << __FUNCTION__ << " - Could not initialize SDL! SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return -1;
	}

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);

	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Game::Window::WIDTH, Game::Window::HEIGHT, Game::Window::FLAGS);
	if (window == nullptr)
	{
		std::cout << __FUNCTION__ << " - Counld not create SDL window! SDL Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr)
	{
		std::cout << __FUNCTION__ << " - OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	SDL_GL_MakeCurrent(window, glContext);

	SDL_GL_SetSwapInterval(Window::VSYNC_IS_ENABLED);

	return 1;
}

int Game::GameWindow::InitOpenGL()
{
	glewExperimental = GL_TRUE;

	GLenum nGlewError = glewInit();
	if (nGlewError != GLEW_OK)
	{
		std::cout << __FUNCTION__ << " - Error initializing GLEW " << glewGetErrorString(nGlewError) << std::endl;
		return -1;
	}

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_FRAMEBUFFER_SRGB);

	_defaultShaderId = CompileGLShader(
		"DefaultShader",

		//Vertex Shader
		"#version 330 core\n"
		"in vec4 position;"
		"in vec4 color;"
		"out vec4 colorV;"
		"void main()"
		"{"
		"	gl_Position = position;"
		"	colorV = color;"
		"}",

		// Fragment Shader
		"#version 330 core\n"
		"in vec4 colorV;"
		"out vec4 outClr;"
		"void main()"
		"{"
		"	outClr = colorV;"
		"}"
	);

	std::cout << "Vendor:   " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version:  " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL:     " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	return 1;
}

int Game::GameWindow::GameLoop()
{
	std::chrono::steady_clock::time_point now{};
	std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
	uint64_t microsecondsRegistered = 0;
	uint64_t elapsed = 0;
	uint64_t lag = 0;
	int64_t frameLag = 0;
	std::string str;

	while (GetIsRunning())
	{
		now = std::chrono::steady_clock::now();
		elapsed = static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(now - startTime).count()) - microsecondsRegistered;
		microsecondsRegistered += elapsed;
		lag += elapsed;
		frameLag += elapsed;

		_fpsTimer += elapsed;
		if (_fpsTimer >= MICROSECONDS_PER_SECOND)
		{
			str = windowName + " FPS: " + std::to_string(_fps).c_str() + " UPS: " + std::to_string(_ups).c_str();
			SDL_SetWindowTitle(window, str.c_str());
			//std::cout << "FPS: " << _fps << " UPS: " << _ups << std::endl;

			_fpsTimer -= MICROSECONDS_PER_SECOND;
			_ups = 0;
			_fps = 0;
		}

		ProcessEvents();

		while (lag >= MICROSECONDS_PER_UPDATE)
		{
			UpdateLogic();
			lag -= MICROSECONDS_PER_UPDATE;
		}

		if (frameLag >= MICROSECONDS_PER_FRAME)
		{
			RenderFrame(static_cast<float>(lag) / static_cast<float>(MICROSECONDS_PER_UPDATE));
			frameLag = 0;
		}
	}
	return 1;
}

void Game::GameWindow::ProcessEvents()
{
	SDL_Event evnt;
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
			case SDL_EventType::SDL_KEYUP:
				onKeyUp.trigger(this, &evnt.key);
				break;
			case SDL_EventType::SDL_KEYDOWN:
				HandleInput(evnt.key.keysym);
				onKeyDown.trigger(this, &evnt.key);
				break;
			case SDL_EventType::SDL_QUIT:
				SetIsRunning(false);
				break;
			default:
				break;
		}
	}
}

bool isFullscreen = false; // @REMOVE

void Game::GameWindow::HandleInput(SDL_Keysym keysym)
{
	switch (keysym.scancode)
	{
		case SDL_SCANCODE_ESCAPE:
			SetIsRunning(false);
			break;
		case SDL_SCANCODE_F11:
			isFullscreen = !isFullscreen;
			SDL_SetWindowFullscreen(window, Game::Window::FLAGS | (isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0));
			break;
		default:
			//std::cout << "Scancode: " << keysym.scancode << " Symbol: " << "'" << static_cast<char>(keysym.sym) << "'" << std::endl;
			break;
	}
}

void Game::GameWindow::UpdateLogic()
{
	_ups++;
	_runTime++;
}

void Game::GameWindow::RenderFrame(float percentThroughFrame)
{
	//glViewport(0, 0, Game::Window::HEIGHT, Game::Window::WIDTH);
	//glClearDepth(1.0);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);

	glUseProgram(_defaultShaderId);

	glBegin(GL_TRIANGLES);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glVertex2f(0.0f, 1.0f);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
	glVertex2f(-1.0f, -1.0f);

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);

	glEnd();

	SDL_GL_SwapWindow(window);

	//std::this_thread::sleep_for(std::chrono::milliseconds(12));


	_fps++;
}

GLuint Game::GameWindow::CompileGLShader(const char* pchShaderName, const char* pchVertexShader, const char* pchFragmentShader)
{
	GLuint unProgramID = glCreateProgram();

	GLuint nSceneVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(nSceneVertexShader, 1, &pchVertexShader, NULL);
	glCompileShader(nSceneVertexShader);

	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(nSceneVertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
	{
		printf("%s - Unable to compile vertex shader %d!\n", pchShaderName, nSceneVertexShader);
		glDeleteProgram(unProgramID);
		glDeleteShader(nSceneVertexShader);
		return 0;
	}
	glAttachShader(unProgramID, nSceneVertexShader);
	glDeleteShader(nSceneVertexShader); // the program hangs onto this once it's attached

	GLuint  nSceneFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(nSceneFragmentShader, 1, &pchFragmentShader, NULL);
	glCompileShader(nSceneFragmentShader);

	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(nSceneFragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
	if (fShaderCompiled != GL_TRUE)
	{
		printf("%s - Unable to compile fragment shader %d!\n", pchShaderName, nSceneFragmentShader);
		glDeleteProgram(unProgramID);
		glDeleteShader(nSceneFragmentShader);
		return 0;
	}

	glAttachShader(unProgramID, nSceneFragmentShader);
	glDeleteShader(nSceneFragmentShader); // the program hangs onto this once it's attached

	glLinkProgram(unProgramID);

	GLint programSuccess = GL_TRUE;
	glGetProgramiv(unProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		printf("%s - Error linking program %d!\n", pchShaderName, unProgramID);
		glDeleteProgram(unProgramID);
		return 0;
	}

	glUseProgram(unProgramID);
	glUseProgram(0);

	return unProgramID;
}

void Game::GameWindow::OnKeyUp(void* sender, SDL_KeyboardEvent* e)
{
	std::cout << "Up  : " << static_cast<char>(e->keysym.sym) << std::endl;
}

void Game::GameWindow::OnKeyDown(void* sender, SDL_KeyboardEvent* e)
{
	std::cout << "Down: " << static_cast<char>(e->keysym.sym) << std::endl;
}
