#include "CollisionHandler.h"
#include "../Core/PrimaryEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
//std::vector<GameObject*> CollisionHandler::colliders = std::vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;

CollisionHandler::CollisionHandler()
{
	//colliders.reserve(10);
	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::OnCreate(float worldSize_)
{
	//colliders.clear();
	prevCollisions.clear();
	scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject* gameObject_)
{
	//colliders.push_back(gameObject_);
	if (scenePartition != nullptr) {
		scenePartition->AddObject(gameObject_);
	}
}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_)
{
	Ray mouseRay = CollisionDectection::MousePositionToWorldRay(mousePosition_, 
		PrimaryEngine::GetInstance()->GetScreenWidth(), 
		PrimaryEngine::GetInstance()->GetScreenHeight(), 
		PrimaryEngine::GetInstance()->GetCamera());

	if (scenePartition != nullptr) {

		GameObject* hitResult = scenePartition->GetCollision(mouseRay);

		if (hitResult) {
			hitResult->SetHit(true, buttonType_);
		}


		for (auto c : prevCollisions) {
			if (hitResult != c && c != nullptr) {
				c->SetHit(false, buttonType_);
			}
		}

		prevCollisions.clear();
		if (hitResult) {
			prevCollisions.push_back(hitResult);
		}
	}
}

void CollisionHandler::OnDestroy()
{
	delete scenePartition;
	scenePartition = nullptr;

	for (auto entry : prevCollisions) {
		entry = nullptr;
	}
	prevCollisions.clear();
}
