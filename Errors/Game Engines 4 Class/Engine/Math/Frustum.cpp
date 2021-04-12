#include "Frustum.h"
#include "../Camera/Camera.h"
#include "BoundingBox.h"

Frustum::Frustum()
{
	frustum[0] = 0.0f; 
	frustum[1] = 0.0f; 
	frustum[2] = 0.0f; 
	frustum[3] = 0.0f; 
	frustum[4] = 0.0f; 
	frustum[5] = 0.0f;
}

Frustum::~Frustum()
{

}

void Frustum::CalculateFrustum()
{
	float modelView[16];
	float projection[16];

	// [0] = top / [1] = bottom / [2] = left/ [3] = right / [4] = near / [5] = far (first array inside Frustum float)
	// [0] = x, [1] = y, [2] = z, [3] = distanceFromOrigin (second array inside Frustum float)

	// Calculate top of frustum.
	frustum[0] = modelView[0] * projection[3] + modelView[1] * projection[7] + modelView[2] * projection[11] + modelView[3] * projection[15]
		- modelView[0] * projection[1] + modelView[1] * projection[5] + modelView[2] * projection[9] + modelView[3] * projection[13];
	
	glm::normalize(frustum[0]);

	// Calculate bottom plane of frustum.
	frustum[1] = modelView[0] * projection[3] + modelView[1] * projection[7] + modelView[2] * projection[11] + modelView[3] * projection[15]
		+ modelView[0] * projection[1] + modelView[1] * projection[5] + modelView[2] * projection[9] + modelView[3] * projection[13];
	
	glm::normalize(frustum[1]);

	// Calculate left side of frustum.
	frustum[2] = modelView[0] * projection[3] + modelView[1] * projection[7] + modelView[2] * projection[11] + modelView[3] * projection[15]
		+ modelView[0] * projection[0] + modelView[1] * projection[4] + modelView[2] * projection[8] + modelView[3] * projection[12];
	
	glm::normalize(frustum[2]);

	// Calculate right side of frustum.
	frustum[3] = modelView[0] * projection[3] + modelView[1] * projection[7] + modelView[2] * projection[11] + modelView[3] * projection[15]
		- modelView[0] * projection[0] + modelView[1] * projection[4] + modelView[2] * projection[8] + modelView[3] * projection[12];

	glm::normalize(frustum[3]);

	// Calculate near plane of frustum.
	frustum[4] = modelView[0] * projection[3] + modelView[1] * projection[7] + modelView[2] * projection[11] + modelView[3] * projection[15]
		+ modelView[0] * projection[2] + modelView[1] * projection[6] + modelView[2] * projection[10] + modelView[3] * projection[14];

	glm::normalize(frustum[4]);

	// Calculate far plane of frustum.
	frustum[5] = modelView[0] * projection[3] + modelView[1] * projection[7] + modelView[2] * projection[11] + modelView[3] * projection[15]
		- modelView[0] * projection[2] + modelView[1] * projection[6] + modelView[2] * projection[10] + modelView[3] * projection[14];

	glm::normalize(frustum[5]);

}

bool Frustum::checkBox()
{
	for (int i = 0; i < 6; i++)
	{
		BoundingBox* box = new BoundingBox();

		// Check to see if the planes of the box are inside of the frustum
		if (frustum[i] * (box->maxVert.x - box->minVert.x) + frustum[i] * (box->maxVert.y - box->minVert.y) + frustum[i] * (box->maxVert.z - box->minVert.z) + frustum[i] > 0)
		{
			continue;
		}
		if (frustum[i] * (box->maxVert.x + box->minVert.x) + frustum[i] * (box->maxVert.y - box->minVert.y) + frustum[i] * (box->maxVert.z - box->minVert.z) + frustum[i] > 0)
		{
			continue;
		}
		if (frustum[i] * (box->maxVert.x - box->minVert.x) + frustum[i] * (box->maxVert.y + box->minVert.y) + frustum[i] * (box->maxVert.z - box->minVert.z) + frustum[i] > 0)
		{
			continue;
		}
		if (frustum[i] * (box->maxVert.x + box->minVert.x) + frustum[i] * (box->maxVert.y + box->minVert.y) + frustum[i] * (box->maxVert.z - box->minVert.z) + frustum[i] > 0)
		{
			continue;
		}
		if (frustum[i] * (box->maxVert.x - box->minVert.x) + frustum[i] * (box->maxVert.y - box->minVert.y) + frustum[i] * (box->maxVert.z + box->minVert.z) + frustum[i] > 0)
		{
			continue;
		}
		if (frustum[i] * (box->maxVert.x + box->minVert.x) + frustum[i] * (box->maxVert.y - box->minVert.y) + frustum[i] * (box->maxVert.z + box->minVert.z) + frustum[i] > 0)
		{
			continue;
		}
		if (frustum[i] * (box->maxVert.x - box->minVert.x) + frustum[i] * (box->maxVert.y + box->minVert.y) + frustum[i] * (box->maxVert.z + box->minVert.z) + frustum[i] > 0)
		{
			continue;
		}
		if (frustum[i] * (box->maxVert.x + box->minVert.x) + frustum[i] * (box->maxVert.y + box->minVert.y) + frustum[i] * (box->maxVert.z + box->minVert.z) + frustum[i] > 0)
		{
			continue;
		}

		// If it returns false here, then it isn't in the frustum and print to the console that it's not rendering
		std::cout << "NOT RENDERING" << std::endl;
		return false;
	}

	// The box is inside the frustum (if it doesn't return false)
	return true;
}
