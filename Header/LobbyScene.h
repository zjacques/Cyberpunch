#pragma once
#include "Scene.h"
#include "OnlineSystem.h"

class LobbyScene : public Scene {
public:
	LobbyScene();
	void start();
	void stop();
	void update(double dt);
	void draw(SDL_Renderer& renderer);
	void handleInput(InputSystem& input);

private:
	TTF_Font * m_font;
	SDL_Rect m_textRect;
	SDL_Color  * m_textColour;
	SDL_Texture * m_textTexture;

	OnlineSystem* m_network;
	
};