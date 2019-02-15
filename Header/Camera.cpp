#include "Camera.h"

Camera::Camera()
{
	zoom(1.f);

	//Set the view
	m_view.x = 0;
	m_view.y = 0;
	m_view.w = SCREEN_WIDTH;
	m_view.h = SCREEN_HEIGHT;
}

void Camera::centerCamera(float x, float y)
{
	m_centerPoint.x = x;
	m_centerPoint.y = y;
	center();
}

void Camera::centerCamera(Vector2f pos)
{
	m_centerPoint = pos;
	center();
}

void Camera::zoom(float scalar)
{
	m_scalar = scalar;

	if (m_scalar < MIN_ZOOM)
		m_scalar = MIN_ZOOM;
	if (m_scalar > MAX_ZOOM)
		m_scalar = MAX_ZOOM;
}

void Camera::setZoom(SDL_Renderer * renderer)
{
	SDL_RenderSetScale(renderer, m_scalar, m_scalar);

	m_view.x /= m_scalar;
	m_view.y /= m_scalar;
	m_view.w = SCREEN_WIDTH / m_scalar;
	m_view.h = SCREEN_HEIGHT / m_scalar;
}

void Camera::center()
{
	m_view.x = m_centerPoint.x * m_scalar - (SCREEN_WIDTH / 2);
	m_view.y = m_centerPoint.y * m_scalar - (SCREEN_HEIGHT / 2);

	//if (m_view.x < 0)
	//	m_view.x = 0;
	//if (m_view.y < 0)
	//	m_view.y = 0;
	//if (m_view.x + m_view.w > SCREEN_WIDTH)
	//	m_view.x = SCREEN_WIDTH - (SCREEN_WIDTH / m_scalar) /2;
	/*if (m_view.y + m_view.h > SCREEN_HEIGHT)
		m_view.y = SCREEN_HEIGHT - m_view.h; */
}
