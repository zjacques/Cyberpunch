#include "ResourceManager.h"

ResourceHandler::ResourceHandler(std::string filePath) :
	m_filePath(filePath)
{
}

ResourceHandler::~ResourceHandler()
{
}

//Load all of our textures we need for the game
void ResourceHandler::loadTextures(SDL_Renderer& renderer)
{
	//Load level data first
	loadLevelData();

	//Load textures here
}

void ResourceHandler::loadLevelData()
{
	//Open an ifstream on the file
	std::ifstream ifs(m_filePath + "LevelData.txt");
	//Load the data into the string content
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	//Pars ethe loaded in file to a json object
	m_gameData = json::parse(content);
}

SDL_Texture* ResourceHandler::loadFromPath(std::string fileName, SDL_Renderer& renderer)
{
	std::string path = m_filePath + fileName;
	SDL_Texture* newTexture = NULL; //This will be the loaded texture

	//Load image
	SDL_Surface* loadedS = IMG_Load(path.c_str());
	if (loadedS == NULL)
		std::cout << "Error loading image at path " << path << std::endl;
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(&renderer, loadedS);

		if (newTexture == NULL)
			std::cout << "Unable to create texture" << std::endl;

		//Get rid of old surface
		SDL_FreeSurface(loadedS);
	}

	return newTexture;
}

void ResourceHandler::destroyTextures()
{
	//Loop through our map
	for (auto& texture : m_map)
	{
		//Destroy the texture
		SDL_DestroyTexture(texture.second);
	}
}

SDL_Texture * ResourceHandler::getTexture(std::string name)
{
	return m_map.at(name);
}