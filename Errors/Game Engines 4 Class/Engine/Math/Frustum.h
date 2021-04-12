#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glm/matrix.hpp>
#include <glew.h>
#include <iostream>

class Frustum
{
protected:

public:
	Frustum();
	~Frustum();
	void CalculateFrustum();

	bool checkBox(float x, float y, float z, float size);
private:
	float frustum[6]; // [0] = top / [1] = bottom / [2] = left/ [3] = right / [4] = near / [5] = far
};

#endif // !FRUSTUM_H