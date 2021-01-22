//#include <SDL.h>
#include "Engine/Core/PrimaryEngine.h"

PrimaryEngine* engine;

int main(int argc, char* argv[]) {

	//This will call the engine class and make it show up on screen

	if (!PrimaryEngine::GetInstance()->OnCreate("Engines 4", 800, 600)) {
		std::cout << "The engine has failed to run" << std::endl;
		return 0;
	}
	
	PrimaryEngine::GetInstance()->Run();
	return 0;
}