#include "Input.h"

std::string Input::m_selectedNode;

void Input::SetUp()
{
	m_selectedNode = "Base";
}

SDL_Rect Input::GetMousePosition()
{
	SDL_Rect mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	return mousePos;
}

bool Input::CheckKeyPressed(SDL_Event _event)
{
	switch (_event.key.keysym.sym)
	{
	case SDLK_s: 
		//Start Node
		m_selectedNode = "Start";
		return false;
		break;
	case SDLK_e:
		//End Node
		m_selectedNode = "End";
		return false;
		break;
	case SDLK_b:
		//Base Node
		m_selectedNode = "Base";
		return false;
		break;
	case SDLK_u:
		//Blocked Node
		m_selectedNode = "Blocked";
		return false;
		break;
	case SDLK_d:
		//Rough Node
		m_selectedNode = "Rough";
		return false;
		break;
	case SDLK_r:
		//Reset Node
		return false;
		break;
	case SDLK_SPACE:
		//Start Algorithm
		return true;
		break;
	default:
		return false;
		break;
	}
	return false;
}

std::string Input::GetSelectedName()
{
	return m_selectedNode;
}