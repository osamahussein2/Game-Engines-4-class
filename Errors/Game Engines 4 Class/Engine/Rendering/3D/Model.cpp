#include "Model.h"

Model::Model(const std::string& objPath_, const std::string& matPath_, GLuint shaderProgram_) : meshes(std::vector<Mesh*>()), 
shaderProgram(0), modelInstances(std::vector<glm::mat4>()), objModel(nullptr)
{
	shaderProgram = shaderProgram_;
	meshes.reserve(10);
	modelInstances.reserve(5);
	objModel = new LoadOBJModel();
	objModel->LoadModel(objPath_, matPath_);
	LoadModel();
}

Model::~Model()
{
	if (meshes.size() > 0) {
		for (auto m : meshes) {
			delete m;
			m = nullptr;
		}

		meshes.clear();
	}

	if (modelInstances.size() > 0) {
		modelInstances.clear();
	}
}

void Model::Render(Camera* camera_)
{
	glUseProgram(shaderProgram);
	for (auto m : meshes) {
		m->Render(camera_, modelInstances);
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	// push_back means to add the mesh onto the scene (which is done in the GameScene class)

	meshes.push_back(mesh_); 
}

unsigned int Model::CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances.push_back(CreateTransform(position_, angle_, rotation_, scale_));
	return modelInstances.size() - 1;
}

void Model::UpdateInstance(unsigned int index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_)
{
	modelInstances[index_] = CreateTransform(position_, angle_, rotation_, scale_);
}

glm::mat4 Model::GetTransform(unsigned int index_) const
{
	return modelInstances[index_];
}

glm::mat4 Model::CreateTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_) const
{
	glm::mat4 model;
	model = glm::translate(model, position_);
	model = glm::rotate(model, angle_, rotation_);
	model = glm::scale(model, scale_);
	return model;
}

void Model::LoadModel()
{
	for (int i = 0; i < objModel->GetSubMeshes().size(); i++) {
		meshes.push_back(new Mesh(objModel->GetSubMeshes()[i], shaderProgram));
	}
	delete objModel;
	objModel = nullptr;
}
