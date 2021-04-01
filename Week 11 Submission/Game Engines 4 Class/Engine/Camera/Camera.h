#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "../FX/LightSource.h"

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	void AddLightSource(LightSource* lightSource_);
	std::vector<LightSource*> ListOfLightSources() const;

	void ProcessMouseMovement(glm::vec2 offset_);
	void ProcessMouseZoom(int y_);

	glm::mat4 GetView() const;
	glm::mat4 GetPersective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;
private:
	void UpdateCameraVectors();
	glm::vec3 position;
	glm::mat4 persective, orthographic, view;
	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;
	glm::vec3 forward, up, right, worldUp;

	std::vector<LightSource*> light[2];
};

#endif // !CAMERA_H