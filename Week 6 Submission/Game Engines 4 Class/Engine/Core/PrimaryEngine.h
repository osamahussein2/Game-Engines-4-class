#ifndef PRIMARYENGINE_H
#define PRIMARYENGINE_H

#include "Window.h"
#include <memory>
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"

#include "../Rendering/3D/GameObject.h"

#include "Graphics/HandleShaders.h"

#include "../Camera/Camera.h"

class PrimaryEngine
{
public:
	PrimaryEngine(const PrimaryEngine&) = delete;
	PrimaryEngine(PrimaryEngine&&) = delete;
	PrimaryEngine& operator=(const PrimaryEngine&) = delete;
	PrimaryEngine& operator=(PrimaryEngine&&) = delete;

	static PrimaryEngine* GetInstance();

	
	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	void Exit();

	bool GetIsRunning() const;
	int GetCurrentScene() const;
	float GetScreenWidth() const;
	float GetScreenHeight() const;
	Camera* GetCamera() const;

	void SetGameInterface(GameInterface* gameInterface_);
	void SetCurrentScene(int sceneNum_);
	void SetCamera(Camera* camera_);

private:
	PrimaryEngine();
	~PrimaryEngine();
	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	static std::unique_ptr<PrimaryEngine> engineInstance;
	friend std::default_delete<PrimaryEngine>;

	Window* window;
	bool isRunning;
	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;
};

#endif // !PRIMARYENGINE_H