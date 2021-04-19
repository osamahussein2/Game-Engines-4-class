#version 450 core

in vec3 Normal;
in vec2 TexCoords;

//uniform sampler2D inputTexture;
uniform vec3 viewPosition;
uniform vec3 cameraPosition;

in vec3 FragPosition;
out vec4 fColour;

struct LightSource {
    vec3 lightPos;
    vec3 lightColor;

	float ambientLight; 
	float diffuseLight;
	float specularLight;
};

struct Material {

	sampler2D diffuseMap; // newmtl
	float shininess; //Ns
	float transparency; //d

	vec3 ambient; //Ka
	vec3 diffuse; //Kd
	vec3 specular; //Ks

	//std::string name;
};

uniform Material material;
uniform LightSource light;

void main() {
//fColour = texture(inputTexture, TexCoords);

vec3 ambient = light.ambientLight * material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColor;
vec3 norm = normalize(Normal);
vec3 lightDir = normalize(light.lightPos - FragPosition); 
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColor;


vec3 viewDir = normalize(viewPosition - FragPosition);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
vec3 specular = (spec * material.specular) * light.lightColor;

vec3 result = (ambient + diffuse + specular);

fColour = vec4(result, material.transparency);
}