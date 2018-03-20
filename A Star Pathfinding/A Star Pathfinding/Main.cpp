#include <iostream> 
#include <SDL\SDL.h>
#undef main

#include "Input.h"
#include "Instructions.h"
#include "NodeMap.h"
#include "PathFinding.h"
#include "Resource.h"
#include "SDL.h"

const int SCREENWIDTH = 900;
const int SCREENHEIGHT = 600;
const int NODESALONGX = 20;
const int NODESALONGY = 20;

int main()
{
	SDLapi sdl("A* Pathfinding", SCREENWIDTH, SCREENHEIGHT); 
	
	NodeMap nodemap;
	Resources::StartUp(sdl.GetRenderer());
	nodemap.SetUp(sdl.GetRenderer(), SCREENWIDTH - 300, SCREENHEIGHT, NODESALONGX, NODESALONGY);
	Instructions instructions(SCREENWIDTH, SCREENHEIGHT, 300);
	Input::SetUp();

	Pathfinding pathFinding(NODESALONGX, NODESALONGY);
	pathFinding.GetNodeMap(&nodemap);

	bool GameLoop = true;
	bool RunAlgorithm = false;
	SDL_Event Event;

	while (GameLoop)
	{
		SDL_RenderClear(sdl.GetRenderer());

		while(SDL_PollEvent(&Event) != 0)
		{
			if (Event.type == SDL_QUIT)
			{
				GameLoop = false;
			}

			if (Event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (Event.button.button == SDL_BUTTON_LEFT)
				{
					SDL_Rect temp = Input::GetMousePosition();
					nodemap.ChangeTileType(temp.x, temp.y);
				}
			}

			if (Event.type == SDL_KEYDOWN)
			{
				//Input check key actions
				RunAlgorithm = Input::CheckKeyPressed(Event);
			}
		}
		
		if (RunAlgorithm) 
			RunAlgorithm = pathFinding.PathfindingAlgorithm();

		nodemap.RenderNodeMap();
		instructions.Render(sdl.GetRenderer());

		SDL_RenderPresent(sdl.GetRenderer());
	}

	pathFinding.DeactivatePathfinding();
	nodemap.DeactivateNodeMap();
	Resources::CleanUp();
	sdl.DeactivateSDL();
	return 0;
}