#ifndef HANDLESHADERS_H
#define HANDLESHADERS_H

#include <sstream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <glew.h>
#include "../Debug.h"

class HandleShaders
{
public:
	HandleShaders(const HandleShaders&) = delete;
	HandleShaders(HandleShaders&&) = delete;
	HandleShaders& operator=(const HandleShaders&) = delete;
	HandleShaders& operator=(HandleShaders&&) = delete;

	static HandleShaders* GetInstance();

	void CreateProgram(const std::string& shaderName_, const std::string& vertexShaderName_, const std::string& FragShaderName_);
	GLuint GetShader(const std::string& shaderName_);
	void OnDestroy();

private:
	HandleShaders();
	~HandleShaders();

	static std::unique_ptr<HandleShaders> shaderInstance;
	friend std::default_delete<HandleShaders>;

	std::string ReadShader(const std::string& filePath_);
	GLuint CreateShader(GLenum shaderType, const std::string& source_, const std::string& shaderName_);

	static std::unordered_map<std::string, GLuint> programs;
};

#endif //!HANDLESHADERS_H