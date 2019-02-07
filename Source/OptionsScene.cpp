#include "OptionsScene.h"

/// <summary>
/// 
/// </summary>
OptionsScene::OptionsScene()
{
	button_tst = new SDL_Rect();
	button_tst->x = 100;
	button_tst->y = 100;
	button_tst->w = 100;
	button_tst->h = 50;

	const char * path = "assets/fonts/arial.ttf";
	m_font = TTF_OpenFont(path, 32);
}

/// <summary>
/// 
/// </summary>
OptionsScene::~OptionsScene()
{
	SDL_FreeSurface(txtSurface);
	SDL_DestroyTexture(txt_texture);
	TTF_CloseFont(m_font);
}

/// <summary>
/// 
/// </summary>
void OptionsScene::start()
{
	std::cout << "Starting Options Scene\n";
}

/// <summary>
/// 
/// </summary>
void OptionsScene::stop()
{
	std::cout << "Stopping Options Scene\n";
}

/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void OptionsScene::update(double dt)
{

}

/// <summary>
/// 
/// </summary>
/// <param name="renderer"></param>
void OptionsScene::draw(SDL_Renderer & renderer)
{
	SDL_RenderClear(&renderer);
	SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(&renderer, button_tst);

	txtSurface = TTF_RenderText_Solid(m_font, "Options", fgColour);

	txt_texture = SDL_CreateTextureFromSurface(&renderer, txtSurface);

	SDL_RenderCopy(&renderer, txt_texture, NULL, &txtPos);

	SDL_RenderPresent(&renderer);

	SDL_FreeSurface(txtSurface);
	SDL_DestroyTexture(txt_texture);
}

/// <summary>
/// 
/// </summary>
/// <param name="input"></param>
void OptionsScene::handleInput(InputSystem& input)
{

}