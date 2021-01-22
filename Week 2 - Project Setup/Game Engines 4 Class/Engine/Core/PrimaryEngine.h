#ifndef PRIMARYENGINE_H
#define PRIMARYENGINE_H

#include "Window.h"
#include <memory>

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
	bool GetIsRunning();
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
};

#endif // !PRIMARYENGINE_H