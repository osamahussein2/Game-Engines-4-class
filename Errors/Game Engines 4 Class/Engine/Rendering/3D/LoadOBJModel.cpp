#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(std::vector<glm::vec3>()), normals(std::vector<glm::vec3>()), 
textureCoords(std::vector<glm::vec2>()), indices(std::vector<unsigned int>()), normalIndices(std::vector<unsigned int>()), 
textureIndices(std::vector<unsigned int>()), meshVertices(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), 
currentTexture(0) // replace it with currentMaterial(Material())
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}

	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.textureID = currentTexture; // replace this with mesh.material = currentMaterial (from the week 10 videos)

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentTexture = 0; // replace this with currentMaterial = Material();
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;
	while (std::getline(in, line)) {
		// VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
		}
		// NORMAL DATA
		if (line.substr(0, 3) == "vn ") {
			std::stringstream vn(line.substr(3));
			float vnX, vnY, vnZ;
			vn >> vnX >> vnY >> vnZ;
			normals.push_back(glm::vec3(vnX, vnY, vnZ));
		}
		// TEXTURE DATA
		if (line.substr(0, 3) == "vt ") {
			std::stringstream vt(line.substr(3));
			float vtX, vtY;
			vt >> vtX >> vtY;
			textureCoords.push_back(glm::vec2(vtX, vtY));
		}
		// FACE DATA
		if (line.substr(0, 2) == "f ") {
			std::stringstream f(line.substr(2));

			int vertexIndex[3], textureIndex[3], normalIndex[3];

			f >> vertexIndex[0] >> textureIndex[0] >> normalIndex[0] >> vertexIndex[1] >> textureIndex[1] >> normalIndex[1]
				>> vertexIndex[2] >> textureIndex[2] >> normalIndex[2]; 

			indices.push_back(vertexIndex[0] - 1);
			textureIndices.push_back(textureIndex[0] - 1);
			normalIndices.push_back(normalIndex[0] - 1);
			indices.push_back(vertexIndex[1] - 1);
			textureIndices.push_back(textureIndex[1] - 1);
			normalIndices.push_back(normalIndex[1] - 1);
			indices.push_back(vertexIndex[2] - 1);
			textureIndices.push_back(textureIndex[2] - 1); 
			normalIndices.push_back(normalIndex[2] - 1);
		}
		// NEW MESH
		else if (line.substr(0, 7) == "newmtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	in.close();
	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentTexture = HandleTextures::GetInstance()->GetTextures(matName_);
	if (currentTexture == 0) {
		HandleTextures::GetInstance()->CreateTextures(matName_, "Resources/Textures/" + matName_ + ".png");
		currentTexture = HandleTextures::GetInstance()->GetTextures(matName_);
	} // replace this whole code with currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	std::ifstream in(matFilePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open MTL file: " + matFilePath_, "LoadOBJModel.cpp", __LINE__);
	}
	std::string line;
	while (std::getline(in, line)) {
		if (line.substr(0, 7) == "newmtl ") {
			LoadMaterial(line.substr(7));
		}
	}
	in.close(); // MaterialHandler::LoadMaterial(matFilePath_);
}
