#include "Resource.h"

std::vector<NodeTexture> Resources::s_resourceTextures;

Resources::Resources()
{

}

Resources::~Resources()
{

}

void Resources::StartUp(SDL_Renderer* _renderer)
{
	//Generate a temporary texture
	NodeTexture newTexture;

	//Generate each texture and assign it a name
	//Then push it into the vector to access it 
	SDL_Surface *tempSurface = SDL_LoadBMP("Base.bmp");
	newTexture.m_name = "Base";
	newTexture.m_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	s_resourceTextures.push_back(newTexture);

	tempSurface = SDL_LoadBMP("Blocked.bmp");
	newTexture.m_name = "Blocked";
	newTexture.m_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	s_resourceTextures.push_back(newTexture);	

	tempSurface = SDL_LoadBMP("Child.bmp");
	newTexture.m_name = "Child";
	newTexture.m_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	s_resourceTextures.push_back(newTexture);	

	tempSurface = SDL_LoadBMP("End.bmp");
	newTexture.m_name = "End";
	newTexture.m_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	s_resourceTextures.push_back(newTexture);	

	tempSurface = SDL_LoadBMP("Parent.bmp");
	newTexture.m_name = "Parent";
	newTexture.m_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	s_resourceTextures.push_back(newTexture);	

	tempSurface = SDL_LoadBMP("Rough.bmp");
	newTexture.m_name = "Rough";
	newTexture.m_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	s_resourceTextures.push_back(newTexture);	

	tempSurface = SDL_LoadBMP("Start.bmp");
	newTexture.m_name = "Start";
	newTexture.m_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	s_resourceTextures.push_back(newTexture);	

	tempSurface = SDL_LoadBMP("Instructions.bmp");
	newTexture.m_name = "Instructions";
	newTexture.m_texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	s_resourceTextures.push_back(newTexture);	

	//Clean up surface
	SDL_FreeSurface(tempSurface);
	tempSurface = nullptr;
	delete tempSurface;
}

SDL_Texture* Resources::GetTexture(std::string _name)
{
	for (unsigned int i = 0; i < s_resourceTextures.size(); i++)
	{
		if (s_resourceTextures.at(i).m_name == _name)
		{
			return s_resourceTextures.at(i).m_texture;
		}
	}

	return nullptr;
}

void Resources::CleanUp()
{
	for (unsigned int i = 0; i < s_resourceTextures.size(); i++)
	{
		SDL_DestroyTexture(s_resourceTextures.at(i).m_texture);
		s_resourceTextures.at(i).m_texture = nullptr;
		delete s_resourceTextures.at(i).m_texture;
	}
}