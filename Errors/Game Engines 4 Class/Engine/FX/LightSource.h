#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <vector>
#include <glm/glm.hpp>

class LightSource
{
public:
	LightSource(glm::vec3 lightPosition_,
		float ambientLight_, float diffuseLight_, float specularLight_,
		glm::vec3 lightColour_);
	~LightSource();

	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position_);
	glm::vec3 GetLightColour();
	void SetLightColour(glm::vec3 lightColour_);
	float GetAmbientLight();
	void SetAmbientLight(float ambientLight_);
	float GetDiffuseLight();
	void SetDiffuseLight(float diffuseLight_);
	void SetSpecularLight(float specularLight_);

private:
	glm::vec3 position;
	glm::vec3 lightColour;

	float ambientLight;
	float diffuseLight;
	float specularLight;
};

#endif //!LIGHTSOURCE_H