#ifndef SDL_H
#define SDL_H

#include <SDL\SDL.h>
#include <iostream>

class SDLapi
{
private: 
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;

public:
	//Constructors
	SDLapi();
	SDLapi(int _screenWidth, int _screenHeight);
	SDLapi(std::string _title, int _screenWidth, int _screenHeight);

	~SDLapi();

	//Setting Up
	bool SetUpWindow(std::string _title, int _screenWidth, int _screenHeight);
	bool SetUpRenderer();

	void RenderScene();

	SDL_Renderer* GetRenderer()
	{
		return m_renderer;
	}

	void DeactivateSDL();
};

#endif