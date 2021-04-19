#include "Frustum.h"
#include "BoundingBox.h"

Frustum::Frustum()
{
	
}

Frustum::~Frustum()
{

}

void Frustum::CalculateFrustum(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	glm::mat4 worldSpace;

	// Use worldSpace variable to multiply the view Matrix by the projection Matrix
	worldSpace[0][0] = viewMatrix[0][0] * projectionMatrix[0][0] + viewMatrix[0][1] * projectionMatrix[1][0] + viewMatrix[0][2] * projectionMatrix[2][0] + viewMatrix[0][3] * projectionMatrix[3][0];
	worldSpace[1][0] = viewMatrix[0][0] * projectionMatrix[0][1] + viewMatrix[0][1] * projectionMatrix[1][1] + viewMatrix[0][2] * projectionMatrix[2][1] + viewMatrix[0][3] * projectionMatrix[3][1];
	worldSpace[2][0] = viewMatrix[0][0] * projectionMatrix[0][2] + viewMatrix[0][1] * projectionMatrix[1][2] + viewMatrix[0][2] * projectionMatrix[2][2] + viewMatrix[0][3] * projectionMatrix[3][2];
	worldSpace[3][0] = viewMatrix[0][0] * projectionMatrix[0][3] + viewMatrix[0][1] * projectionMatrix[1][3] + viewMatrix[0][2] * projectionMatrix[2][3] + viewMatrix[0][3] * projectionMatrix[3][3];
	
	worldSpace[0][1] = viewMatrix[1][0] * projectionMatrix[0][0] + viewMatrix[1][1] * projectionMatrix[1][0] + viewMatrix[1][2] * projectionMatrix[2][0] + viewMatrix[1][3] * projectionMatrix[3][0];
	worldSpace[1][1] = viewMatrix[1][0] * projectionMatrix[0][1] + viewMatrix[1][1] * projectionMatrix[1][1] + viewMatrix[1][2] * projectionMatrix[2][1] + viewMatrix[1][3] * projectionMatrix[3][1];
	worldSpace[2][1] = viewMatrix[1][0] * projectionMatrix[0][2] + viewMatrix[1][1] * projectionMatrix[1][2] + viewMatrix[1][2] * projectionMatrix[2][2] + viewMatrix[1][3] * projectionMatrix[3][2];
	worldSpace[3][1] = viewMatrix[1][0] * projectionMatrix[0][3] + viewMatrix[1][1] * projectionMatrix[1][3] + viewMatrix[1][2] * projectionMatrix[2][3] + viewMatrix[1][3] * projectionMatrix[3][3];
	
	worldSpace[0][2] = viewMatrix[2][0] * projectionMatrix[0][0] + viewMatrix[2][1] * projectionMatrix[1][0] + viewMatrix[2][2] * projectionMatrix[2][0] + viewMatrix[2][3] * projectionMatrix[3][0];
	worldSpace[1][2] = viewMatrix[2][0] * projectionMatrix[0][1] + viewMatrix[2][1] * projectionMatrix[1][1] + viewMatrix[2][2] * projectionMatrix[2][1] + viewMatrix[2][3] * projectionMatrix[3][1];
	worldSpace[2][2] = viewMatrix[2][0] * projectionMatrix[0][2] + viewMatrix[2][1] * projectionMatrix[1][2] + viewMatrix[2][2] * projectionMatrix[2][2] + viewMatrix[2][3] * projectionMatrix[3][2];
	worldSpace[3][2] = viewMatrix[2][0] * projectionMatrix[0][3] + viewMatrix[2][1] * projectionMatrix[1][3] + viewMatrix[2][2] * projectionMatrix[2][3] + viewMatrix[2][3] * projectionMatrix[3][3];
	
	worldSpace[0][3] = viewMatrix[3][0] * projectionMatrix[0][0] + viewMatrix[3][1] * projectionMatrix[1][0] + viewMatrix[3][2] * projectionMatrix[2][0] + viewMatrix[3][3] * projectionMatrix[3][0];
	worldSpace[1][3] = viewMatrix[3][0] * projectionMatrix[0][1] + viewMatrix[3][1] * projectionMatrix[1][1] + viewMatrix[3][2] * projectionMatrix[2][1] + viewMatrix[3][3] * projectionMatrix[3][1];
	worldSpace[2][3] = viewMatrix[3][0] * projectionMatrix[0][2] + viewMatrix[3][1] * projectionMatrix[1][2] + viewMatrix[3][2] * projectionMatrix[2][2] + viewMatrix[3][3] * projectionMatrix[3][2];
	worldSpace[3][3] = viewMatrix[3][0] * projectionMatrix[0][3] + viewMatrix[3][1] * projectionMatrix[1][3] + viewMatrix[3][2] * projectionMatrix[2][3] + viewMatrix[3][3] * projectionMatrix[3][3];

	// Extract the right side of the frustum
	frustum[0].x = worldSpace[3][0] - worldSpace[0][0];
	frustum[0].y = worldSpace[3][1] - worldSpace[0][1];
	frustum[0].z = worldSpace[3][2] - worldSpace[0][2];
	frustum[0].w = worldSpace[3][3] - worldSpace[0][3];
	
	// Extract the left side of the frustum
	frustum[1].x = worldSpace[3][0] + worldSpace[0][0];
	frustum[1].y = worldSpace[3][1] + worldSpace[0][1];
	frustum[1].z = worldSpace[3][2] + worldSpace[0][2];
	frustum[1].w = worldSpace[3][3] + worldSpace[0][3];

	// Extract the bottom side of the frustum
	frustum[2].x = worldSpace[3][0] + worldSpace[1][0];
	frustum[2].y = worldSpace[3][1] + worldSpace[1][1];
	frustum[2].z = worldSpace[3][2] + worldSpace[1][2];
	frustum[2].w = worldSpace[3][3] + worldSpace[1][3];

	// Extract the top side of the frustum
	frustum[3].x = worldSpace[3][0] - worldSpace[1][0];
	frustum[3].y = worldSpace[3][1] - worldSpace[1][1];
	frustum[3].z = worldSpace[3][2] - worldSpace[1][2];
	frustum[3].w = worldSpace[3][3] - worldSpace[1][3];
	
	// Extract the far plane of the frustum
	frustum[4].x = worldSpace[3][0] - worldSpace[2][0];
	frustum[4].y = worldSpace[3][1] - worldSpace[2][1];
	frustum[4].z = worldSpace[3][2] - worldSpace[2][2];
	frustum[4].w = worldSpace[3][3] - worldSpace[2][3];

	// Extract the near plane of the frustum
	frustum[5].x = worldSpace[3][0] + worldSpace[2][0];
	frustum[5].y = worldSpace[3][1] + worldSpace[2][1];
	frustum[5].z = worldSpace[3][2] + worldSpace[2][2];
	frustum[5].w = worldSpace[3][3] + worldSpace[2][3];

	// For loop is used here to normalize the planes of the frustum
	for (int i = 0; i < 6; i++)
	{
		frustum[i] = glm::normalize(frustum[i]);
	}

}

bool Frustum::checkBox()
{
	for (int i = 0; i < 6; i++)
	{
		BoundingBox* box = new BoundingBox();

		// Check to see if the planes of the box are inside of the frustum
		if ((dot(frustum[i], glm::vec4(box->minVert.x, box->minVert.y, box->minVert.z, 1.0f)) < 0.0))
		{
			continue;
		}
		if ((dot(frustum[i], glm::vec4(box->maxVert.x, box->minVert.y, box->minVert.z, 1.0f)) < 0.0))
		{
			continue;
		}
		if ((dot(frustum[i], glm::vec4(box->minVert.x, box->maxVert.y, box->minVert.z, 1.0f)) < 0.0))
		{
			continue;
		}
		if ((dot(frustum[i], glm::vec4(box->maxVert.x, box->maxVert.y, box->minVert.z, 1.0f)) < 0.0))
		{
			continue;
		}
		if ((dot(frustum[i], glm::vec4(box->minVert.x, box->minVert.y, box->maxVert.z, 1.0f)) < 0.0))
		{
			continue;
		}
		if ((dot(frustum[i], glm::vec4(box->maxVert.x, box->minVert.y, box->maxVert.z, 1.0f)) < 0.0))
		{
			continue;
		}
		if ((dot(frustum[i], glm::vec4(box->minVert.x, box->maxVert.y, box->maxVert.z, 1.0f)) < 0.0))
		{
			continue;
		}
		if ((dot(frustum[i], glm::vec4(box->maxVert.x, box->maxVert.y, box->maxVert.z, 1.0f)) < 0.0))
		{
			continue;
		}

		// If it returns false here, then it isn't in the frustum and print to the console that it's not rendering
		//std::cout << "NOT RENDERING" << std::endl;
		return false;
	}

	// The box is inside the frustum (if it doesn't return false)
	return true;
}
