#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <glm/glm.hpp>
#include <glew.h>
#include <iostream>

class Frustum
{
protected:

public:
	Frustum();
	~Frustum();
	void CalculateFrustum(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	bool checkBox();
private:
	glm::vec4 frustum[6]; // [0] = top / [1] = bottom / [2] = left/ [3] = right / [4] = near / [5] = far
};

#endif // !FRUSTUM_H