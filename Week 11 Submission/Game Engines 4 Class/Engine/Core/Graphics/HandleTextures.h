#ifndef HANDLETEXTURES_H
#define HANDLETEXTURES_H

#include <memory>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "../Debug.h"
#include <glew.h>

struct Texture {
	GLuint textureID = 0;
	float width = 0.0f;
	float height = 0.0f;
	std::string textureName = "";
};

class HandleTextures
{
public:
	HandleTextures(const HandleTextures&) = delete;
	HandleTextures(HandleTextures&&) = delete;
	HandleTextures& operator=(const HandleTextures&) = delete;
	HandleTextures& operator=(HandleTextures&&) = delete;
	static HandleTextures* GetInstance();
	void OnDestroy();

	void CreateTextures(const std::string& textureName_, const std::string& textureFilePath_);
	const GLuint GetTextures(const std::string& textureName_);
	const Texture* GetTextureData(const std::string textureName_);
private:
	HandleTextures();
	~HandleTextures();

	static std::unique_ptr<HandleTextures> textureInstance;
	friend std::default_delete<HandleTextures>;
	static std::vector<Texture*> textures;
};

#endif //!HANDLETEXTURES_H