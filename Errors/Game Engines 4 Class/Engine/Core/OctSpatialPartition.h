#ifndef OCTSPATIALPARTITION_H
#define OCTSPATIALPARTITION_H

#include "../Math/Ray.h"
#include "../Rendering/3D/GameObject.h"

constexpr auto CHILDREN_NUMBER = 8;

enum class OctChildren {
	OCT_TLF, // TOP LEFT FRONT
	OCT_BLF, // BOTTOM LEFT FRONT
	OCT_BRF, // BOTTOM RIGHT FRONT
	OCT_TRF, // TOP RIGHT FRONT
	OCT_TLR, // TOP LEFT REAR
	OCT_BLR, // BOTTOM LEFT REAR
	OCT_BRR, // BOTTOM RIGHT REAR
	OCT_TRR // TOP RIGHT REAR
};

class OctNode
{
public:
	OctNode(glm::vec3 position_, float size_, OctNode* parent_);
	~OctNode();
	void Octify(int depth_);
	OctNode* GetParent();
	OctNode* GetChild(OctChildren childPos_);
	void AddCollisionObject(GameObject* gameObject_);
	int GetObjectCount() const;
	bool isLeaf() const;
	BoundingBox* GetBoundingBox() const;
	int GetChildCount() const;
private:
	friend class OctSpatialPartition;
	BoundingBox* octBounds;
	OctNode* parent;
	OctNode* children[CHILDREN_NUMBER];
	std::vector<GameObject*> objectList;
	float size;
	static int childNum;
};

class OctSpatialPartition {
public:
	OctSpatialPartition(float worldSize_);
	~OctSpatialPartition();
	void AddObject(GameObject* gameObject_);
	GameObject* GetCollision(Ray ray_);
private:
	OctNode* root;
	std::vector<OctNode*> rayIntersectionList;
	void AddObjectToCell(OctNode* cell_, GameObject* gameObject_);
	void PrepareCollisionQuery(OctNode* cell_, Ray ray_);
};

#endif // !OCTSPATIALPARTITION_H