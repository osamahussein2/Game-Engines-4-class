#ifndef COLLISIONDECTECTION_H
#define COLLISIONDECTECTION_H

#include "../Camera/Camera.h"

struct Ray;
struct BoundingBox;

class CollisionDectection
{
public:
	CollisionDectection(const CollisionDectection&) = delete;
	CollisionDectection(CollisionDectection&&) = delete;
	CollisionDectection& operator=(const CollisionDectection&) = delete;
	CollisionDectection& operator=(CollisionDectection&&) = delete;

	CollisionDectection() = delete;
	~CollisionDectection();

	static Ray MousePositionToWorldRay(glm::vec2 mouseCoords_, float screenWidth_, float screenHeight_, Camera* camera_);
	static bool RayOBBIntersection(Ray* ray_, BoundingBox* box_);
};

#endif // !COLLISIONDECTECTION_H