#include "StartScene.h"

StartScene::StartScene()
{
	// Intialize scene variable
	sceneManager = nullptr;
}

StartScene::~StartScene()
{
	delete sceneManager;
	sceneManager = nullptr;
}

bool StartScene::OnCreate()
{
	// Print to the console that start scene is on screen
	std::cout << "start scene" << std::endl;
	
	// Get game scene on screen

	sceneManager = new GameScene();
	return sceneManager->OnCreate();

	return true;
}

void StartScene::Update(const float deltaTime_)
{
	// Shows the Game Scene's timer to the console (by the way, I'm using the Scene class not the Game Scene class)
	sceneManager->Update(deltaTime_);

	// This will update the start scene timer in the console
	std::cout << "start scene timer: " << deltaTime_ << std::endl;
}

void StartScene::Render()
{
}
