#include <iostream>
#include <thread>
#include <chrono>

#include "gameloop.h"

int main()
{
	Game::GameWindow* window = new Game::GameWindow();

	return window->RunGame();
}

//Add support for:
// SFML
// GLEW
// SDL
// GLFW
// DirectX
// Opus
// PortAudio?
// SteamVR
// OculusVR
// C# scripting?

// Libraries to include:
// nlohmann/json
// OpenSSL
// Bullet
// Protobuf
