#include "PrimaryEngine.h"

std::unique_ptr<PrimaryEngine> PrimaryEngine::engineInstance = nullptr;

PrimaryEngine::PrimaryEngine()
{
	window = nullptr;
	isRunning = false;
	fps = 60;
	gameInterface = nullptr;
	currentSceneNum = 0;
}

PrimaryEngine::~PrimaryEngine()
{
}

PrimaryEngine* PrimaryEngine::GetInstance()
{
	// GetInstance function helps run the engine properly

	if (engineInstance.get() == nullptr) {
		engineInstance.reset(new PrimaryEngine);
	}
	return engineInstance.get();
}

bool PrimaryEngine::OnCreate(std::string name_, int width_, int height_)
{
	Debug::OnCreate();
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Failed to open window", "PrimaryEngine.cpp", __LINE__);
		OnDestroy();
		return isRunning = false;
	}

	HandleShaders::GetInstance()->CreateProgram("colourShader", "Engine/Shaders/ColorVertexShader.glsl", 
		"Engine/Shaders/ColorFragShader.glsl");

	HandleShaders::GetInstance()->CreateProgram("basicShader", "Engine/Shaders/VertexShader.glsl",
		"Engine/Shaders/FragmentShader.glsl");

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::Error("Game has failed to intialize", "PrimaryEngine.cpp", __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}

	Debug::Info("Everything worked", "PrimaryEngine.cpp", __LINE__);
	timer.Start();
	return isRunning = true;
}

void PrimaryEngine::Run()
{
	while (isRunning) {
		timer.UpdateFrameTicks();
		Update(timer.GetDeltaTime()); // 1 second / 60 frames = 0.016
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}

	while (!isRunning) {
		OnDestroy(); // If isRunning has an error, then use the OnDestroy method to close the engine
	}
}

void PrimaryEngine::Exit()
{
	isRunning = false;
}

bool PrimaryEngine::GetIsRunning() const
{
	// Just return isRunning and don't modify it

	return isRunning;
}

int PrimaryEngine::GetCurrentScene() const
{
	return currentSceneNum;
}

float PrimaryEngine::GetScreenWidth() const
{
	return static_cast<float>(window->GetWidth());
}

float PrimaryEngine::GetScreenHeight() const
{
	return static_cast<float>(window->GetHeight());
}

Camera* PrimaryEngine::GetCamera() const
{
	return camera;
}

void PrimaryEngine::SetGameInterface(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
}

void PrimaryEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void PrimaryEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void PrimaryEngine::Update(const float deltaTime_)
{
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
		std::cout << deltaTime_ << std::endl;
	}
}

void PrimaryEngine::Render()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // glColor will decide with color I want to use depending on the RGBA values
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // glClear clears the color buffer

	if (gameInterface) {
		gameInterface->Render();
	}

	// Get Game Renderer
	SDL_GL_SwapWindow(window->GetWindow());
}

void PrimaryEngine::OnDestroy()
{
	HandleShaders::GetInstance()->OnDestroy();
	HandleTextures::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();

	// Clean up or delete window

	delete gameInterface;
	gameInterface = nullptr;
	delete window;
	window = nullptr;
	delete camera;
	camera = nullptr;
	SDL_Quit();
	exit(0);
}
