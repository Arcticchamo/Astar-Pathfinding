#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <SDL\SDL.h>
#include <string>

#include "Input.h"
#include "Resource.h"

class Instructions
{
private:
	SDL_Rect m_instructionsRect;
	std::string m_textureName;

	SDL_Rect m_notificationRect;

public:
	Instructions(int _screenWidth, int _screenHeight, int _deviation);
	~Instructions();

	void Render(SDL_Renderer *_renderer);

};

#endif