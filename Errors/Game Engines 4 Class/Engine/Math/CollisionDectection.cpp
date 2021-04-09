#include "CollisionDectection.h"
#include "Ray.h"
#include "../Core/PrimaryEngine.h"

CollisionDectection::~CollisionDectection()
{
}

Ray CollisionDectection::MousePositionToWorldRay(glm::vec2 mouseCoords_, float screenWidth_, float screenHeight_, Camera* camera_)
{
	glm::vec4 rayStartNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f,
		-1.0f, 1.0f);
	glm::vec4 rayEndNDC((mouseCoords_.x / screenWidth_ - 0.5f) * 2.0f, (mouseCoords_.y / screenHeight_ - 0.5f) * 2.0f,
		0.0f, 1.0f);

	glm::mat4 inverse = glm::inverse(camera_->GetPersective() * camera_->GetView());

	glm::vec4 rayStartWorld = inverse * rayStartNDC;
	rayStartWorld /= rayStartWorld.w;

	glm::vec4 rayEndWorld = inverse * rayEndNDC;
	rayEndWorld /= rayEndWorld.w;

	glm::vec3 rayDirectionWorld(rayEndWorld - rayStartWorld);
	rayDirectionWorld = glm::normalize(rayDirectionWorld);

	return Ray(glm::vec3(rayStartWorld), rayDirectionWorld);
}

bool CollisionDectection::RayOBBIntersection(Ray* ray_, BoundingBox* box_)
{
	glm::mat4 modelMatrix = box_->transform;
	glm::vec3 rayOrigin = ray_->origin;
	glm::vec3 rayDirection = ray_->direction;
	glm::vec3 boxMin = box_->minVert;
	glm::vec3 boxMax = box_->maxVert;
	float tMin = PrimaryEngine::GetInstance()->GetCamera()->GetNearPlane();
	float tMax = PrimaryEngine::GetInstance()->GetCamera()->GetFarPlane();
	glm::vec3 worldPosition(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	glm::vec3 delta = worldPosition - rayOrigin;

	// x axis
	glm::vec3 xAxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
	float dotDelta = glm::dot(delta, xAxis);
	float dotDirection = glm::dot(rayDirection, xAxis);
	if (fabs(dotDirection) > 0.001f) {
		float t1 = (dotDelta + boxMin.x) / dotDirection;
		float t2 = (dotDelta + boxMax.x) / dotDirection;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-dotDelta + boxMin.x > 0.0f || -dotDelta + boxMax.x < 0.0f) {
			return false;
		}
	}

	// y axis
	glm::vec3 yAxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
	float dotDeltaY = glm::dot(delta, yAxis);
	float dotDirectionY = glm::dot(rayDirection, yAxis);
	if (fabs(dotDirection) > 0.001f) {
		float t1 = (dotDeltaY + boxMin.y) / dotDirectionY;
		float t2 = (dotDeltaY + boxMax.y) / dotDirectionY;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-dotDeltaY + boxMin.y > 0.0f || -dotDeltaY + boxMax.y < 0.0f) {
			return false;
		}
	}

	// z axis
	glm::vec3 zAxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
	float dotDeltaZ = glm::dot(delta, zAxis);
	float dotDirectionZ = glm::dot(rayDirection, zAxis);
	if (fabs(dotDirection) > 0.001f) {
		float t1 = (dotDeltaZ + boxMin.z) / dotDirectionZ;
		float t2 = (dotDeltaZ + boxMax.z) / dotDirectionZ;

		if (t1 > t2) {
			float w = t1;
			t1 = t2;
			t2 = w;
		}

		if (t2 < tMax) {
			tMax = t2;
		}

		if (t1 > tMin) {
			tMin = t1;
		}

		if (tMax < tMin) {
			return false;
		}
	}
	else {
		if (-dotDeltaZ + boxMin.z > 0.0f || -dotDeltaZ + boxMax.z < 0.0f) {
			return false;
		}
	}

	ray_->intersectionDistance = tMin;
	return true;
}
