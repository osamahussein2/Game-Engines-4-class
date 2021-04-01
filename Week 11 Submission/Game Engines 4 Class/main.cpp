//#include <SDL.h>
#include "Engine/Core/PrimaryEngine.h"
#include "Game/Game1.h"

PrimaryEngine* engine;

int main(int argc, char* argv[]) {

	PrimaryEngine::GetInstance()->SetGameInterface(new Game1);

	//This will call the engine class and make it show up on screen

	if (!PrimaryEngine::GetInstance()->OnCreate("Engines 4", 800, 600)) {
		std::cout << "The engine has failed to run" << std::endl; // If the error happens, then show this message and return 0
		return 0;
	}
	
	PrimaryEngine::GetInstance()->Run(); // If there's no errors, then run the engine!
	return 0;
}