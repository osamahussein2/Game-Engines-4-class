#include "GameScene.h"

GameScene::GameScene()
{
	model = nullptr;
	shape = nullptr;
}

GameScene::~GameScene()
{
	model = nullptr;

	delete shape;
	shape = nullptr;
}

bool GameScene::OnCreate()
{
	PrimaryEngine::GetInstance()->SetCamera(new Camera());
	PrimaryEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 6.0f));
	/*HandleTextures::GetInstance()->CreateTextures("CheckerboardTexture",
		"./Resources/Textures/CheckerboardTexture.png");*/

	PrimaryEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f),
		0.1f, 0.5f, 0.5f,
		glm::vec3(1.0f, 1.0f, 1.0f)));

	CollisionHandler::GetInstance()->OnCreate();


	// Cube model is implemented here

	/*Vertex v;
	std::vector<Vertex> vertexList;
	vertexList.reserve(36);*/

	/*{
		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.583f, 0.771f, 0.014f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.609f, 0.115f, 0.436f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.327f, 0.483f, 0.844f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.822f, 0.569f, 0.201f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.435f, 0.602f, 0.223f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.310f, 0.747f, 0.185f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.597f, 0.770f, 0.761f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.559f, 0.436f, 0.730f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.359f, 0.583f, 0.152f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.483f, 0.596f, 0.789f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.559f, 0.861f, 0.639f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.195f, 0.548f, 0.859f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.014f, 0.184f, 0.576f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.771f, 0.328f, 0.970f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.406f, 0.615f, 0.116f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.676f, 0.977f, 0.133f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.971f, 0.572f, 0.833f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.140f, 0.616f, 0.489f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.997f, 0.513f, 0.064f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.945f, 0.719f, 0.592f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.543f, 0.021f, 0.978f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.279f, 0.317f, 0.505f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.167f, 0.620f, 0.077f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.347f, 0.857f, 0.137f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.055f, 0.953f, 0.042f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.714f, 0.505f, 0.345f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.783f, 0.290f, 0.734f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.722f, 0.645f, 0.174f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.302f, 0.455f, 0.848f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.225f, 0.587f, 0.040f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.517f, 0.713f, 0.338f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 0.0f);
		v.colour = glm::vec3(0.053f, 0.959f, 0.120f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.393f, 0.621f, 0.362f);
		vertexList.push_back(v);

		v.position = glm::vec3(0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(1.0f, 1.0f);
		v.colour = glm::vec3(0.673f, 0.211f, 0.457f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 1.0f);
		v.colour = glm::vec3(0.820f, 0.883f, 0.371f);
		vertexList.push_back(v);

		v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
		v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		v.textureCoordinates = glm::vec2(0.0f, 0.0f);
		v.colour = glm::vec3(0.982f, 0.099f, 0.879f);
		vertexList.push_back(v);
	}*/


	// I commented out the original code that helped to create the triangle

	/*vertexList.reserve(3);
	v.position = glm::vec3(0.0f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);
	v.position = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);*/

	// Create the mesh object
	// I've added extra lines of code to show how these new functions work (e.g. scale, rotation, angle)
	// The reason why I included the set angle code is to show the shaders for the different vertices of the cube

	Model* diceModel = new Model("Resources/Models/Dice.obj", "Resources/Materials/Dice.mtl",
		HandleShaders::GetInstance()->GetShader("basicShader"));

	Model* appleModel = new Model("Resources/Models/Apple.obj", "Resources/Materials/Apple.mtl",
		HandleShaders::GetInstance()->GetShader("basicShader"));

	SceneGraph::GetInstance()->AddModel(diceModel);
	SceneGraph::GetInstance()->AddModel(appleModel);

	SceneGraph::GetInstance()->AddGameObject(new GameObject(diceModel, glm::vec3(-1.5f, 0.0f, 0.0f)), "Dice");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(appleModel, glm::vec3(1.5f, 0.0f, 0.0f)), "Apple");

	/*SubMesh subMesh;
	subMesh.vertexList = vertexList;
	subMesh.textureID = HandleTextures::GetInstance()->GetTextures("CheckerboardTexture");
	model->AddMesh(new Mesh(subMesh,
		HandleShaders::GetInstance()->GetShader("basicShader")));*/
	//model->SetScale(glm::vec3(0.5f));
	//model->SetRotation(glm::vec3(90.0f));
	//model->SetAngle(30.0f);
	//shape = new GameObject(model);
	
	diceModel = nullptr;
	appleModel = nullptr;

	// Print to the console that game scene is on screen
	//std::cout << "game scene" << std::endl;
	
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	SceneGraph::GetInstance()->Update(deltaTime_);

	//shape->Update(deltaTime_);

	// Update the game scene timer
	//std::cout << "game scene timer: " << deltaTime_ << std::endl;
	
}

void GameScene::Render()
{
	// Render the model & game Objects into the scene
	SceneGraph::GetInstance()->Render(PrimaryEngine::GetInstance()->GetCamera());

	// I can't get the frustum to work
	/*Frustum* appleFrustum = new Frustum();
	Frustum* diceFrustum = new Frustum();

	appleFrustum->checkBox(0.0f, 0.0f, 0.0f, 0.0f);*/

	// Render the triangle inside this scene
	//shape->Render(PrimaryEngine::GetInstance()->GetCamera());
}
