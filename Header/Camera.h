#pragma once
#include "SDL.h"
#include "Vector2f.h"

class Camera
{
public:
	Camera();

	void update(double dt);
	void centerCamera(float x, float y);
	void centerCamera(Vector2f pos);
	void zoom(float scalar);
	void setZoom(SDL_Renderer* renderer);

	float x() { return m_view.x; }
	float y() { return m_view.y; }
	float getScale() { return m_scalar; }

	const float MAX_ZOOM = 1.55f;
	const float MIN_ZOOM = 1.0f;
private:
	void center();

	Vector2f m_centerPoint;
	SDL_Rect m_view;

	//Dimensions of the camera
	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;
	const int HALF_WIDTH = 960;
	const int HALF_HEIGHT = 540;

	float m_scalar;
	float m_desiredScalar;
};