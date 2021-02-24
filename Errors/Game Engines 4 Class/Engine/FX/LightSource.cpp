#include "LightSource.h"

LightSource::LightSource(glm::vec3 lightPosition_,
	float ambientLight_, float diffuseLight_, float specularLight_,
	glm::vec3 lightColour_) : ambientLight(0.0f), diffuseLight(0.0f), specularLight(0.0f)
{
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition()
{
	return position;
}

void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}

glm::vec3 LightSource::GetLightColour()
{
	return lightColour;
}

void LightSource::SetLightColour(glm::vec3 lightColour_)
{
	lightColour = lightColour_;
}

float LightSource::GetAmbientLight()
{
	return ambientLight;
}

void LightSource::SetAmbientLight(float ambientLight_)
{
	ambientLight = ambientLight_;
}

float LightSource::GetDiffuseLight()
{
	return diffuseLight;
}

void LightSource::SetDiffuseLight(float diffuseLight_)
{
	diffuseLight = diffuseLight_;
}

void LightSource::SetSpecularLight(float specularLight_)
{
	specularLight = specularLight_;
}
