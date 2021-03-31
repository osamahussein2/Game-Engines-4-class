#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}

void MaterialLoader::LoadMaterial(std::string filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;

	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			if (m.diffuseMap != 0) {
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}

			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;	
		}

		// Ambient
		if (line.substr(0, 4) == "	Ka ") {
			std::stringstream ka(line.substr(4));
			float kaX, kaY, kaZ;
			ka >> kaX >> kaY >> kaZ;
			m.ambient = glm::vec3(kaX, kaY, kaZ);
		}
		// Diffuse
		if (line.substr(0, 4) == "	Kd ") {
			std::stringstream kd(line.substr(4));
			float kdX, kdY, kdZ;
			kd >> kdX >> kdY >> kdZ;
			m.diffuse = glm::vec3(kdX, kdY, kdZ);
		}
		// Specular
		if (line.substr(0, 4) == "	Ks ") {
			std::stringstream ks(line.substr(4));
			float ksX, ksY, ksZ;
			ks >> ksX >> ksY >> ksZ;
			m.specular = glm::vec3(ksX, ksY, ksZ);
		}
		// Transparency
		if (line.substr(0, 3) == "	d ") {
			std::stringstream d(line.substr(3));
			float dValue;
			d >> dValue;
			m.transparency = dValue;
		}
		// Shininess
		if (line.substr(0, 4) == "	Ns ") { 
			std::stringstream Ns(line.substr(4));
			float NsValue;
			Ns >> NsValue;
			m.shininess = NsValue;
		}
	}

	if (m.diffuseMap != 0) {
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = HandleTextures::GetInstance()->GetTextures(fileName_);
	if (currentTexture == 0) {
		HandleTextures::GetInstance()->CreateTextures(fileName_, "Resources/Textures/" + fileName_ + ".png");
		currentTexture = HandleTextures::GetInstance()->GetTextures(fileName_);
	}
	return currentTexture;
}
