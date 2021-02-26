#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <vector>
#include <glm/glm.hpp>

class LightSource
{
public:
	LightSource(glm::vec3 lightPos_,
		float ambientLight_, float diffuseLight_, float specularLight_,
		glm::vec3 lightColor_);
	~LightSource();

	glm::vec3 GetPosition() const;
	void SetPosition(glm::vec3 lightPos_);

	float GetAmbientLight() const;
	void SetAmbientLight(float ambientLight_);

	float GetDiffuseLight() const;
	void SetDiffuseLight(float diffuseLight_);

	float GetSpecularLight() const;
	void SetSpecularLight(float specularLight_);

	glm::vec3 GetLightColor() const;
	void SetLightColor(glm::vec3 lightColor_);

private:
	glm::vec3 lightPos, lightColor;
	float ambientLight, diffuseLight, specularLight;
};

#endif //!LIGHTSOURCE_H