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
	//You do not need to include the entire path, the resource manager
	//Will look for everything in the Resources folder, so you then need to only provide th erest of the path to the file
	//Like so
	//loadFromPath("Player.png")
	//If you had the player.png in another folder, then youd call it like this
	//loadFromPath("Characters/Player.png")

	m_map["Game BG"] = loadFromPath("Backgrounds-01.png", renderer);
	m_map["Player"] = loadFromPath("Player/Player.png", renderer);
	m_map["Record"] = loadFromPath("Record/Record.png", renderer);
	//Load all 3 platform pieces for each colour
	for (int i = 0; i < 3; i++)
	{
		m_map["Booth" + std::to_string(i)] = loadFromPath("DJBooth/DJBooth" + std::to_string(i) + ".png", renderer);
	}


	//Loading in GUI
	m_map["Button Off"] = loadFromPath("GUI/ButtonOff.png", renderer);
	m_map["Exit Button"] = loadFromPath("GUI/ExitButton.png", renderer);
	m_map["Local Play Button"] = loadFromPath("GUI/LocalButton.png", renderer);
	m_map["Multiplayer Button"] = loadFromPath("GUI/MultiButton.png", renderer);
	m_map["Options Button"] = loadFromPath("GUI/OptionsButton.png", renderer);

	//The colours of the platforms
	auto platforms = std::vector<std::string>({"Green", "Blue", "Orange", "Pink"});
	for (auto& colour : platforms)
	{
		//Load all 3 platform pieces for each colour
		for (int i = 0; i < 3; i++)
		{
			m_map["Platform " + colour + " " + std::to_string(i)] = loadFromPath("Platforms/" + colour + "/" + std::to_string(i) + ".png", renderer);
		}
	}
}

void ResourceHandler::loadLevelData()
{
	//Open an ifstream on the file
	std::ifstream ifs(m_filePath + "LevelData.txt");

	//Load the data into the string content
	std::string content((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	//Parse the loaded in file to a json object
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

TTF_Font* ResourceHandler::loadFont(std::string filePath, std::string name)
{
	const char * path = filePath.c_str();
	m_fontMap[name] = TTF_OpenFont(path, 32);
	return m_fontMap[name];
}

TTF_Font * ResourceHandler::getFont(std::string name)
{
	return m_fontMap[name];
}

SDL_Texture * ResourceHandler::getTexture(std::string name)
{
	return m_map.at(name);
}