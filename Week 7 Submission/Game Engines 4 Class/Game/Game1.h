#ifndef GAME1_H
#define GAME1_H

#include "../Engine/Core/PrimaryEngine.h"
#include "Scenes/GameScene.h"
#include "Scenes/StartScene.h"

class Game1 : public GameInterface
{
public:
	Game1();
	virtual ~Game1();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;

private:
	void BuildScene();
	int currentSceneNum;
	Scene* currentScene;
	
};

#endif //!GAME1_H