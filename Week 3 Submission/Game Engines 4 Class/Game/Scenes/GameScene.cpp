#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::OnCreate()
{
	// Print to the console that game scene is on screen
	std::cout << "game scene" << std::endl;
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	// Update the game scene timer
	std::cout << "game scene timer: " << deltaTime_ << std::endl;
	
}

void GameScene::Render()
{
}
