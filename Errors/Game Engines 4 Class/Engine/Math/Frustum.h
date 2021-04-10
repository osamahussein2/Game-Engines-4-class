#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glm/matrix.hpp>
#include <glew.h>
#include <iostream>

class Frustum
{
protected:
	enum FrustumSide
	{
		RIGHT = 0,
		LEFT = 1,
		BOTTOM = 2,
		TOP = 3,
		BACK = 4,
		FRONT = 5
	};

	enum PlaneData
	{
		X = 0, // The X value of the plane's normal
		Y = 1, // The Y value of the plane's normal
		Z = 2, // The Z value of the plane's normal
		O = 3 // The distance the plane is from the origin
	};


public:
	Frustum();
	~Frustum();
	void NormalizePlane(float frustum[6][4], int side);
	void CalculateFrustum();

	bool findPoint(float x, float y, float z);
	bool findCube(float x, float y, float z, float size);
	bool findSphere(float x, float y, float z, float radius);
private:
	float frustum[6][4];
};

#endif // !FRUSTUM_H