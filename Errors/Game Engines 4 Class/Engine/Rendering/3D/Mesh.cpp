#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), shaderProgram(0), modelLoc(0), viewLoc(0), 
projectionLoc(0), textureLoc(0), viewPositionVectorLoc(0), lightPositionLoc(0), ambientLightLoc(0), diffuseLightLoc(0),
specularLightLoc(0), lightColourLoc(0)
{
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0) {
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0) {
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_)
{
	glUniform1i(textureLoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.textureID);

	// Renders the mesh triangles

	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPersective()));

	glUniform3fv(viewPositionVectorLoc, 1, glm::value_ptr(camera_->GetPosition())); 
	glUniform3fv(lightPositionLoc, 1, glm::value_ptr(camera_->ListOfLightSources()[0]->GetPosition()));
	glUniform1f(ambientLightLoc, camera_->ListOfLightSources()[0]->GetAmbientLight());
	glUniform1f(diffuseLightLoc, camera_->ListOfLightSources()[0]->GetDiffuseLight());
	glUniform1f(specularLightLoc, camera_->ListOfLightSources()[0]->GetSpecularLight());
	glUniform3fv(lightColourLoc, 1, glm::value_ptr(camera_->ListOfLightSources()[0]->GetLightColor()));

	for (int i = 0; i < instances_.size(); i++) {
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	// vec3 position code
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// vec3 normal code
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	// vec3 texCoord code
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));

	// vec3 color code
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	textureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	viewPositionVectorLoc = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPositionLoc = glGetUniformLocation(shaderProgram, "light.lightPos"); 
	ambientLightLoc = glGetUniformLocation(shaderProgram, "light.ambientLight");
	diffuseLightLoc = glGetUniformLocation(shaderProgram, "light.diffuseLight");
	specularLightLoc = glGetUniformLocation(shaderProgram, "light.specularLight");
	lightColourLoc = glGetUniformLocation(shaderProgram, "light.lightColor");
}
