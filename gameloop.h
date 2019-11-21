#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <GL/glxew.h>

#include "types/types.h"
#include "logic/object.h"
#include "logic/eventhandler/eventhandler.h"

/*
 Game namespace
*/
namespace Game
{
	/*
	 Game class
	 This contains the game runtime and control over it
	*/
	class GameWindow : public Object
	{
		public:
		EventHandler<void*, SDL_KeyboardEvent*> onKeyUp;
		EventHandler<void*, SDL_KeyboardEvent*> onKeyDown;

		void SetIsRunning(bool value) { _isRunning = value; }; /* Setter for _isRunning, game will stop if this gets set to false */
		bool GetIsRunning() { return _isRunning; }; /* Getter for _isRunning */
		int GetFps() { return _fps; }; /* Getter for _fps */
		int GetUps() { return _ups; }; /* Getter for _ups */

		GameWindow(Object* parent = nullptr); /* Object is inherited to this class */
		~GameWindow();

		int RunGame(); /* Start game application, cant be ran twice */

		private:

		std::string windowName; /* Name of the application, this will show up in the title of the window */

		bool     _isRunning;
		uint64_t _fpsTimer;
		uint16_t _fps = 0; /* (Frames Per Second) counter for how many frames gets rendered per seconds */
		uint16_t _ups = 0; /* (Updates Per Second) counter for how many physics updates gets calcuated per seconds */
		uint64_t _runTime = 0; /* total tick count since application started */

		SDL_Window* window = nullptr;
		SDL_Surface* surface = nullptr;
		SDL_GLContext glContext = nullptr;

		GLuint _defaultShaderId = 0;

		int Initialize(); /* Initialize most SDL, and vars */
		int InitWindow(); /* Initialize SDL window */
		int InitOpenGL(); /* Initialize OpenGL */
		int GameLoop(); /* Main game loop */
		void ProcessEvents(); /* Handle events */
		void HandleInput(SDL_Keysym keysym); /* handles inputs in the gamewindow */
		void UpdateLogic(); /* Update physics of the game */
		void RenderFrame(float percentThroughFrame); /* Render a frame, takes in a parameter for how distant the last and next logic updates are */
		GLuint CompileGLShader(const char* pchShaderName, const char* pchVertexShader, const char* pchFragmentShader); /* Compiles vertex and fragment shaders */

		static void OnKeyUp(void* sender, SDL_KeyboardEvent* e);
		static void OnKeyDown(void* sender, SDL_KeyboardEvent* e);
	};
}
