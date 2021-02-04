#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	// Print to the console that start scene is on screen
	std::cout << "start scene" << std::endl;
	
	// Switch to game scene

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
