#include "Camera.h"

#include "../Core/PrimaryEngine.h"

Camera::Camera() : position(glm::vec3()), fieldOfView(0.0f), forward(glm::vec3()), up(glm::vec3()), right(glm::vec3()),
worldUp(glm::vec3()), nearPlane(0.0f), farPlane(0.0f), yaw(0.0f), pitch(0.0f), persective(glm::mat4()), 
orthographic(glm::mat4()), view(glm::mat4())
{
	fieldOfView = 45.0f;
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	persective = glm::perspective(fieldOfView, 
		PrimaryEngine::GetInstance()->GetScreenWidth() / PrimaryEngine::GetInstance()->GetScreenHeight(),
		nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, PrimaryEngine::GetInstance()->GetScreenWidth(), 
		0.0f, PrimaryEngine::GetInstance()->GetScreenHeight(),
		1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera()
{
	if (light[0].size() > 0) {
		for (auto light : light[0]) {
			delete light;
			light = nullptr; 
		}

		light[0].clear();
	}

	if (light[1].size() > 0) {
		for (auto light1 : light[1]) {
			delete light1;
			light1 = nullptr;
		}

		light[1].clear();
	}
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVectors();
}

void Camera::AddLightSource(LightSource* lightSource_)
{
	light[0].push_back(lightSource_); 

	light[1].push_back(lightSource_);
}

std::vector<LightSource*> Camera::ListOfLightSources() const
{
	return light[0], light[1];
}

glm::mat4 Camera::GetView() const
{
	return view;
}

glm::mat4 Camera::GetPersective() const
{
	return persective;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

void Camera::UpdateCameraVectors()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));

	view = glm::lookAt(position, position + forward, up);
}
