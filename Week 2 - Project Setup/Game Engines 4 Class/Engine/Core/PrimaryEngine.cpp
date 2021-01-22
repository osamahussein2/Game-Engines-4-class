#include "PrimaryEngine.h"

std::unique_ptr<PrimaryEngine> PrimaryEngine::engineInstance = nullptr;

PrimaryEngine::PrimaryEngine()
{
	window = nullptr;
	isRunning = false;
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
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		std::cout << "Failed to open window" << std::endl;
		OnDestroy();
		return isRunning = false;
	}
	return isRunning = true;
}

void PrimaryEngine::Run()
{
	while (isRunning) {
		Update(0.016f); // 1 second / 60 frames = 0.016
		Render();
	}

	while (!isRunning) {
		OnDestroy(); // If isRunning has an error, then use the OnDestroy method to close the engine
	}
}

bool PrimaryEngine::GetIsRunning()
{
	// Just return isRunning and don't modify it

	return isRunning;
}

void PrimaryEngine::Update(const float deltaTime_)
{
}

void PrimaryEngine::Render()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // glColor will decide with color I want to use depending on the RGBA values
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // glClear clears the color buffer

	// Get Game Renderer
	SDL_GL_SwapWindow(window->GetWindow());
}

void PrimaryEngine::OnDestroy()
{
	// Clean up or delete window

	delete window;
	window = nullptr;
	SDL_Quit();
	exit(0);
}
