#include "Frustum.h"

Frustum::Frustum()
{
	frustum[0][0] = 0.0f; frustum[0][1] = 0.0f; frustum[0][2] = 0.0f; frustum[0][3] = 0.0f;
	frustum[1][0] = 0.0f; frustum[1][1] = 0.0f; frustum[1][2] = 0.0f; frustum[1][3] = 0.0f;
	frustum[2][0] = 0.0f; frustum[2][1] = 0.0f; frustum[2][2] = 0.0f; frustum[2][3] = 0.0f;
	frustum[3][0] = 0.0f; frustum[3][1] = 0.0f; frustum[3][2] = 0.0f; frustum[3][3] = 0.0f;
	frustum[4][0] = 0.0f; frustum[4][1] = 0.0f; frustum[4][2] = 0.0f; frustum[4][3] = 0.0f;
	frustum[5][0] = 0.0f; frustum[5][1] = 0.0f; frustum[5][2] = 0.0f; frustum[5][3] = 0.0f;
}

Frustum::~Frustum()
{

}

void Frustum::NormalizePlane(float frustum[6][4], int side)
{
	float magnitude = (float)sqrt(frustum[side][X] * frustum[side][X] +
		frustum[side][Y] * frustum[side][Y] +
		frustum[side][Z] * frustum[side][Z]);

	// Divide the plane's values by it's magnitude
	frustum[side][X] /= magnitude;
	frustum[side][Y] /= magnitude;
	frustum[side][Z] /= magnitude;
	frustum[side][O] /= magnitude;
}

void Frustum::CalculateFrustum()
{
	float projectionMatrix[16]; // This will hold our projection matrix
	float modelMatrix[16]; // This will hold our model view matrix
	float clippingPlanes[16]; // This will hold the clipping planes

	// Below, we pass in GL_PROJECTION_MATRIX to store our projection matrix variable inside it
	glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrix);

	// By passing in GL_MODELVIEW_MATRIX, we can store our model view matrix variable inside it
	glGetFloatv(GL_MODELVIEW_MATRIX, modelMatrix);

	// Multiply the projectionMatrix by the modelViewMatrix to find clippingPlanes

	clippingPlanes[0] = modelMatrix[0] * projectionMatrix[0] + modelMatrix[1] * projectionMatrix[4] + modelMatrix[2] * projectionMatrix[8] + modelMatrix[3] * projectionMatrix[12];
	clippingPlanes[1] = modelMatrix[0] * projectionMatrix[1] + modelMatrix[1] * projectionMatrix[5] + modelMatrix[2] * projectionMatrix[9] + modelMatrix[3] * projectionMatrix[13];
	clippingPlanes[2] = modelMatrix[0] * projectionMatrix[2] + modelMatrix[1] * projectionMatrix[6] + modelMatrix[2] * projectionMatrix[10] + modelMatrix[3] * projectionMatrix[14];
	clippingPlanes[3] = modelMatrix[0] * projectionMatrix[3] + modelMatrix[1] * projectionMatrix[7] + modelMatrix[2] * projectionMatrix[11] + modelMatrix[3] * projectionMatrix[15];

	clippingPlanes[4] = modelMatrix[4] * projectionMatrix[0] + modelMatrix[5] * projectionMatrix[4] + modelMatrix[6] * projectionMatrix[8] + modelMatrix[7] * projectionMatrix[12];
	clippingPlanes[5] = modelMatrix[4] * projectionMatrix[1] + modelMatrix[5] * projectionMatrix[5] + modelMatrix[6] * projectionMatrix[9] + modelMatrix[7] * projectionMatrix[13];
	clippingPlanes[6] = modelMatrix[4] * projectionMatrix[2] + modelMatrix[5] * projectionMatrix[6] + modelMatrix[6] * projectionMatrix[10] + modelMatrix[7] * projectionMatrix[14];
	clippingPlanes[7] = modelMatrix[4] * projectionMatrix[3] + modelMatrix[5] * projectionMatrix[7] + modelMatrix[6] * projectionMatrix[11] + modelMatrix[7] * projectionMatrix[15];

	clippingPlanes[8] = modelMatrix[8] * projectionMatrix[0] + modelMatrix[9] * projectionMatrix[4] + modelMatrix[10] * projectionMatrix[8] + modelMatrix[11] * projectionMatrix[12];
	clippingPlanes[9] = modelMatrix[8] * projectionMatrix[1] + modelMatrix[9] * projectionMatrix[5] + modelMatrix[10] * projectionMatrix[9] + modelMatrix[11] * projectionMatrix[13];
	clippingPlanes[10] = modelMatrix[8] * projectionMatrix[2] + modelMatrix[9] * projectionMatrix[6] + modelMatrix[10] * projectionMatrix[10] + modelMatrix[11] * projectionMatrix[14];
	clippingPlanes[11] = modelMatrix[8] * projectionMatrix[3] + modelMatrix[9] * projectionMatrix[7] + modelMatrix[10] * projectionMatrix[11] + modelMatrix[11] * projectionMatrix[15];

	clippingPlanes[12] = modelMatrix[12] * projectionMatrix[0] + modelMatrix[13] * projectionMatrix[4] + modelMatrix[14] * projectionMatrix[8] + modelMatrix[15] * projectionMatrix[12];
	clippingPlanes[13] = modelMatrix[12] * projectionMatrix[1] + modelMatrix[13] * projectionMatrix[5] + modelMatrix[14] * projectionMatrix[9] + modelMatrix[15] * projectionMatrix[13];
	clippingPlanes[14] = modelMatrix[12] * projectionMatrix[2] + modelMatrix[13] * projectionMatrix[6] + modelMatrix[14] * projectionMatrix[10] + modelMatrix[15] * projectionMatrix[14];
	clippingPlanes[15] = modelMatrix[12] * projectionMatrix[3] + modelMatrix[13] * projectionMatrix[7] + modelMatrix[14] * projectionMatrix[11] + modelMatrix[15] * projectionMatrix[15];

	// Clipping planes we received above and extract the sides from them by using the frustum[6][4].

	// This will extract the RIGHT side of the frustum
	frustum[RIGHT][X] = clippingPlanes[3] - clippingPlanes[0];
	frustum[RIGHT][Y] = clippingPlanes[7] - clippingPlanes[4];
	frustum[RIGHT][Z] = clippingPlanes[11] - clippingPlanes[8];
	frustum[RIGHT][O] = clippingPlanes[15] - clippingPlanes[12];

	// Normalize the RIGHT side
	NormalizePlane(frustum, RIGHT);

	// This will extract the LEFT side of the frustum
	frustum[LEFT][X] = clippingPlanes[3] + clippingPlanes[0];
	frustum[LEFT][Y] = clippingPlanes[7] + clippingPlanes[4];
	frustum[LEFT][Z] = clippingPlanes[11] + clippingPlanes[8];
	frustum[LEFT][O] = clippingPlanes[15] + clippingPlanes[12];

	// Normalize the LEFT side
	NormalizePlane(frustum, LEFT);

	// This will extract the BOTTOM side of the frustum
	frustum[BOTTOM][X] = clippingPlanes[3] + clippingPlanes[1];
	frustum[BOTTOM][Y] = clippingPlanes[7] + clippingPlanes[5];
	frustum[BOTTOM][Z] = clippingPlanes[11] + clippingPlanes[9];
	frustum[BOTTOM][O] = clippingPlanes[15] + clippingPlanes[13];

	// Normalize the BOTTOM side
	NormalizePlane(frustum, BOTTOM);

	// This will extract the TOP side of the frustum
	frustum[TOP][X] = clippingPlanes[3] - clippingPlanes[1];
	frustum[TOP][Y] = clippingPlanes[7] - clippingPlanes[5];
	frustum[TOP][Z] = clippingPlanes[11] - clippingPlanes[9];
	frustum[TOP][O] = clippingPlanes[15] - clippingPlanes[13];

	// Normalize the TOP side
	NormalizePlane(frustum, TOP);

	// This will extract the BACK side of the frustum
	frustum[BACK][X] = clippingPlanes[3] - clippingPlanes[2];
	frustum[BACK][Y] = clippingPlanes[7] - clippingPlanes[6];
	frustum[BACK][Z] = clippingPlanes[11] - clippingPlanes[10];
	frustum[BACK][O] = clippingPlanes[15] - clippingPlanes[14];

	// Normalize the BACK side
	NormalizePlane(frustum, BACK);

	// This will extract the FRONT side of the frustum
	frustum[FRONT][X] = clippingPlanes[3] + clippingPlanes[2];
	frustum[FRONT][Y] = clippingPlanes[7] + clippingPlanes[6];
	frustum[FRONT][Z] = clippingPlanes[11] + clippingPlanes[10];
	frustum[FRONT][O] = clippingPlanes[15] + clippingPlanes[14];

	// Normalize the FRONT side
	NormalizePlane(frustum, FRONT);
}

bool Frustum::findPoint(float x, float y, float z)
{
	// Go through all the sides of the frustum
	for (int i = 0; i < 6; i++)
	{
		// Calculate the plane equation and check if the point is behind a side of the frustum
		if (frustum[i][X] * x + frustum[i][Y] * y + frustum[i][Z] * z + frustum[i][O] <= 0)
		{
			// The point was behind a side, so it ISN'T in the frustum
			std::cout << "NOT RENDERING" << std::endl;
			return false;
		}
	}

	// The point is inside of the frustum
	return true;
}

bool Frustum::findCube(float x, float y, float z, float size)
{
	for (int i = 0; i < 6; i++)
	{
		if (frustum[i][X] * (x - size) + frustum[i][Y] * (y - size) + frustum[i][Z] * (z - size) + frustum[i][O] > 0)
		{
			continue;
		}
		if (frustum[i][X] * (x + size) + frustum[i][Y] * (y - size) + frustum[i][Z] * (z - size) + frustum[i][O] > 0)
		{
			continue;
		}
		if (frustum[i][X] * (x - size) + frustum[i][Y] * (y + size) + frustum[i][Z] * (z - size) + frustum[i][O] > 0)
		{
			continue;
		}
		if (frustum[i][X] * (x + size) + frustum[i][Y] * (y + size) + frustum[i][Z] * (z - size) + frustum[i][O] > 0)
		{
			continue;
		}
		if (frustum[i][X] * (x - size) + frustum[i][Y] * (y - size) + frustum[i][Z] * (z + size) + frustum[i][O] > 0)
		{
			continue;
		}
		if (frustum[i][X] * (x + size) + frustum[i][Y] * (y - size) + frustum[i][Z] * (z + size) + frustum[i][O] > 0)
		{
			continue;
		}
		if (frustum[i][X] * (x - size) + frustum[i][Y] * (y + size) + frustum[i][Z] * (z + size) + frustum[i][O] > 0)
		{
			continue;
		}
		if (frustum[i][X] * (x + size) + frustum[i][Y] * (y + size) + frustum[i][Z] * (z + size) + frustum[i][O] > 0)
		{
			continue;
		}

		// If we get here, it isn't in the frustum
		std::cout << "NOT RENDERING" << std::endl;
		return false;
	}

	// The Cube is inside the frustum
	return true;
}

bool Frustum::findSphere(float x, float y, float z, float radius)
{
	// Go through all the sides of the frustum
	for (int i = 0; i < 6; i++)
	{
		// If the center of the sphere is farther away from the plane than the radius
		if (frustum[i][X] * x + frustum[i][Y] * y + frustum[i][Z] * z + frustum[i][O] <= -radius)
		{
			// The distance was greater than the radius so the sphere is outside of the frustum
			std::cout << "NOT RENDERING" << std::endl;
			return false;
		}
	}

	// The sphere is inside of the frustum!
	return true;
}
