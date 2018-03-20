#ifndef INPUT_H
#define INPUT_H

#include <SDL\SDL.h>
#include <string>

class Input
{
private:
	static std::string m_selectedNode;

public:
	Input();
	~Input();

	static void SetUp();

	static SDL_Rect GetMousePosition();
	static bool CheckKeyPressed(SDL_Event _event);
	static std::string GetSelectedName();
};

#endif