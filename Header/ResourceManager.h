#pragma once
#include <nlohmann/json.hpp>
#include "SDL.h"
#include "SDL_image/include/SDL_image.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "../Libraries/SDL_TTF/include/SDL_ttf.h"
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

	TTF_Font* loadFont(std::string filePath, std::string name);
	TTF_Font* getFont(std::string name);

	SDL_Texture* getTexture(std::string name);
	json& getLevelData() { return m_gameData; }
private:
	json m_gameData;
	std::string m_filePath;
	std::map<std::string, SDL_Texture*> m_map; //Where we will hold the textures

	std::map<std::string, TTF_Font*> m_fontMap;
};