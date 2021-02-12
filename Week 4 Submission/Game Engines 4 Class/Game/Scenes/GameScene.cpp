#include "GameScene.h"

GameScene::GameScene()
{
	shape = nullptr;
}

GameScene::~GameScene()
{
	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	// I finally made a square now

	Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(6);
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	// I commented out the original code that helped to create the triangle

	/*vertexList.reserve(3);
	v.position = glm::vec3(0.0f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);*/

	// Create the mesh object

	Model* model = new Model();
	model->AddMesh(new Mesh(vertexList));
	shape = new GameObject(model);
	
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
	// Render the triangle inside this scene
	shape->Render();
}
