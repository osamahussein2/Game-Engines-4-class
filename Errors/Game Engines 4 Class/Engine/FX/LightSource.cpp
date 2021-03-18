#include "LightSource.h"

LightSource::LightSource(glm::vec3 lightPos_,
	float ambientLight_, float diffuseLight_, float specularLight_,
	glm::vec3 lightColor_)
{
	lightPos = lightPos_;
	ambientLight = ambientLight_;
	diffuseLight = diffuseLight_;
	specularLight = specularLight_;
	lightColor = lightColor_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition() const
{
	return lightPos;
}

void LightSource::SetPosition(glm::vec3 lightPos_)
{
	lightPos = lightPos_;
}

float LightSource::GetAmbientLight() const
{
	return ambientLight;
}

void LightSource::SetAmbientLight(float ambientLight_)
{
	ambientLight = ambientLight_;
}

float LightSource::GetDiffuseLight() const
{
	return diffuseLight;
}

void LightSource::SetDiffuseLight(float diffuseLight_)
{
	diffuseLight = diffuseLight_;
}

float LightSource::GetSpecularLight() const
{
	return specularLight;
}

void LightSource::SetSpecularLight(float specularLight_)
{
	specularLight = specularLight_;
}

glm::vec3 LightSource::GetLightColor() const
{
	return lightColor;
}

void LightSource::SetLightColor(glm::vec3 lightColor_)
{
	lightColor = lightColor_;
}
