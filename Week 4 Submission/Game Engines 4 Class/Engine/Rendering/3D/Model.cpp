#include "Model.h"

Model::Model() : meshes(std::vector<Mesh*>())
{
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
}

void Model::Render()
{
	for (auto m : meshes) {
		m->Render();
	}
}

void Model::AddMesh(Mesh* mesh_)
{
	// push_back means to add the mesh onto the scene (which is done in the GameScene class)

	meshes.push_back(mesh_);
}
