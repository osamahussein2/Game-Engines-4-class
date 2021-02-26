#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;

uniform sampler2D inputTexture;
uniform vec3 viewPosition;
uniform vec3 cameraPosition;

out vec3 FragPosition;
out vec4 fColour;

struct LightSource {
    vec3 lightPos;
    vec3 lightColor;

	float ambientLight; 
	float diffuseLight;
	float specularLight;
};

uniform LightSource light;

void main() {
//fColour = texture(inputTexture, TexCoords);

vec3 ambient = light.ambientLight * texture(inputTexture, TexCoords).rgb * light.lightColor;
vec3 norm = normalize(Normal);
vec3 lightDir = normalize(light.lightPos - FragPosition);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = (diff * light.diffuseLight) * texture(inputTexture, TexCoords).rgb * light.lightColor;

vec3 viewDir = normalize(viewPosition - FragPosition);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specular = (spec * light.specularLight) * light.lightColor;

vec3 result = (ambient + diffuse + specular);

fColour = vec4(result, 1.0f);
}