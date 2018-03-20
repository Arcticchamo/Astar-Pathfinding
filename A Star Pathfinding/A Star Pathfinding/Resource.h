#ifndef RESOURCE_H
#define RESOURCE_H

#include <SDL\SDL.h>
#include <string>
#include <vector>

//Struct to store textures
struct NodeTexture{
	SDL_Texture *m_texture;
	std::string m_name;
};

//Uses a static class to be able to store and access certain variables
class Resources
{
private:
	static std::vector<NodeTexture> s_resourceTextures;

public:
	Resources();
	~Resources();

	static void StartUp(SDL_Renderer* _renderer);
	static SDL_Texture* GetTexture(std::string _name);
	static void CleanUp();

};


#endif