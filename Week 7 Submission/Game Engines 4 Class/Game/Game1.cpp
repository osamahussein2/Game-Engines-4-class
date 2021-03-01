#include "Game1.h"

Game1::Game1() : GameInterface()
{
	currentScene = nullptr;
	currentSceneNum = 0;
}

Game1::~Game1()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate()
{
	if (PrimaryEngine::GetInstance()->GetCurrentScene() == 0) {

		currentScene = new StartScene();
		currentSceneNum = 0;
		return currentScene->OnCreate();
	}

	std::cout << "Engine's scene isn't intialized to 0" << std::endl;
	return false;
}

void Game1::Update(const float deltaTime_)
{
	// Get the change in time from previous time to current time in the current scene
	if (currentSceneNum != PrimaryEngine::GetInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game1::Render()
{
	// Render the current scene on screen
	currentScene->Render();
}

void Game1::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	// This function below will allow us to switch scenes
	switch (PrimaryEngine::GetInstance()->GetCurrentScene()) {
	case 1:
		currentScene = new GameScene();
		break;
	default:
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = PrimaryEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate()) {
		std::cout << "Scene failed to be created" << std::endl;
		PrimaryEngine::GetInstance()->Exit();
	}
}
