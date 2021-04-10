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
	//std::cout << "start scene" << std::endl;
	
	// Get game scene on screen

	PrimaryEngine::GetInstance()->SetCurrentScene(1);

	return true;
}

void StartScene::Update(const float deltaTime_)
{
	// This will update the start scene timer in the console
	std::cout << "start scene timer: " << deltaTime_ << std::endl;
}

void StartScene::Render()
{
}
