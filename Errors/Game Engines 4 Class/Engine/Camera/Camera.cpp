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
	light1 = nullptr;
	delete light1;

	light2 = nullptr;
	delete light2;

	light3 = nullptr;
	delete light3;
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
	
}

void Camera::ListOfLightSources(LightSource* light1_)
{
	light1 = light1_;
	//light2 = light2_;
	//light3 = light3_;
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
