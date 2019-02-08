#pragma once
#include <nlohmann/json.hpp>
#include "SDL.h"
#include "SDL_image/include/SDL_image.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
using json = nlohmann::json;

class ResourceHandler
{
public:
	ResourceHandler(std::string filePath);
	~ResourceHandler();

	void loadTextures(SDL_Renderer& renderer);
	void loadLevelData();
	SDL_Texture* loadFromPath(std::string fileName, SDL_Renderer& renderer);
	void destroyTextures();

	SDL_Texture* getTexture(std::string name);
	json& getLevelData() { return m_gameData; }
private:
	json m_gameData;
	std::string m_filePath;
	std::map<std::string, SDL_Texture*> m_map; //Where we will hold the textures
};