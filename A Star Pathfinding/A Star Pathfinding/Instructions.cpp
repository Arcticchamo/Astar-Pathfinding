#include "Instructions.h"

Instructions::Instructions(int _screenWidth, int _screenHeight, int _deviation)
{
	m_instructionsRect.h = _screenHeight;
	m_instructionsRect.w = _deviation;
	m_instructionsRect.x = _screenWidth - _deviation;
	m_instructionsRect.y = 0;

	m_notificationRect.h = 40;
	m_notificationRect.w = 40;
	m_notificationRect.x = _screenWidth - (_deviation - 25);
	m_notificationRect.y = _screenHeight - 50;

	m_textureName = "Instructions";
}

Instructions::~Instructions()
{

}

void Instructions::Render(SDL_Renderer *_renderer)
{
	SDL_RenderCopy(_renderer, Resources::GetTexture(m_textureName), NULL, &m_instructionsRect);
	SDL_RenderCopy(_renderer, Resources::GetTexture(Input::GetSelectedName()), NULL, &m_notificationRect);
}