#pragma once
#include "SDL.h"
#include "SDL_image/include/SDL_image.h"
#include <string>
#include <iostream>
#include <map>

class ResourceHandler
{
public:
	ResourceHandler(std::string filePath);
	~ResourceHandler();

	void loadTextures(SDL_Renderer& renderer);
	SDL_Texture* loadFromPath(std::string fileName, SDL_Renderer& renderer);
	void destroyTextures();

	SDL_Texture* getTexture(std::string name);
private:
	std::string m_filePath;
	std::map<std::string, SDL_Texture*> m_map; //Where we will hold the textures
};