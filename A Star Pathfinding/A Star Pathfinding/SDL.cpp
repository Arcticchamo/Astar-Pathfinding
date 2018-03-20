#include "SDL.h"

SDLapi::SDLapi()
{
	//Error check to see if SDL does not initialize 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL INIT failed: " << SDL_GetError() << std::endl;
		return;
	}

	//Generate the window - uses pregenerated values
	bool WindowSetup = SetUpWindow("Window", 800, 600); //Default values

	//Generate the renderer
	bool RendererSetup = SetUpRenderer(); 

	//Error check to see if the window or renderer was not generated
	if (WindowSetup == false || RendererSetup == false)
	{
		SDL_Quit(); 
		std::cout << "SDL Window and Renderer Setup failed: " << SDL_GetError() << std::endl;
		return;
	}
}

SDLapi::SDLapi(int _screenWidth, int _screenHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL INIT failed: " << SDL_GetError() << std::endl;
		return;
	}

	bool WindowSetup = SetUpWindow("Window", _screenWidth, _screenHeight); 

	bool RendererSetup = SetUpRenderer(); 

	if (WindowSetup == false || RendererSetup == false)
	{
		SDL_Quit(); 
		std::cout << "SDL Window and Renderer Setup failed: " << SDL_GetError() << std::endl;
		return;
	}
}

SDLapi::SDLapi(std::string _title, int _screenWidth, int _screenHeight)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL INIT failed: " << SDL_GetError() << std::endl;
		return;
	}

	bool WindowSetup = SetUpWindow(_title, _screenWidth, _screenHeight);

	bool RendererSetup = SetUpRenderer(); 

	if (WindowSetup == false || RendererSetup == false)
	{
		SDL_Quit(); 
		std::cout << "SDL Window and Renderer Setup failed: " << SDL_GetError() << std::endl;
		return;
	}
}

SDLapi::~SDLapi()
{}

bool SDLapi::SetUpWindow(std::string _title, int _screenWidth, int _screenHeight)
{
	m_window = SDL_CreateWindow(
		_title.c_str(), 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		_screenWidth,
		_screenHeight,
		SDL_WINDOW_SHOWN);
		
	if (m_window == nullptr) return false;
	else return true;
}

bool SDLapi::SetUpRenderer()
{
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);

	if (m_renderer == nullptr) return false;
	else return true;
}

void SDLapi::RenderScene()
{
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);
}

void SDLapi::DeactivateSDL()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}