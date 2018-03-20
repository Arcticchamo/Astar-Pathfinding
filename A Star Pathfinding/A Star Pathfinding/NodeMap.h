#ifndef NODEMAP_H
#define NODEMAP_H

#include <iostream>
#include <SDL\SDL.h>
#include <vector>

#include "Input.h"
#include "Node.h" 
#include "Resource.h"

class NodeMap
{
private: 
	int m_nodesAlongX;
	int m_nodesAlongY;
	int m_nodeWidth;
	int m_nodeHeight;
	SDL_Renderer *m_renderer;

	Node *m_currentNode;
	Node *m_endNode; 

protected:
	std::vector< std::vector<Node> > m_nodegrid;
	std::vector< Node* > m_closedList;

public: 
	NodeMap();
	~NodeMap();

	//Number of nodes through width and height
	void SetUp(SDL_Renderer *_renderer, 
		const int _width, 
		const int _height, 
		const int _x, 
		const int _y);

	void RenderNodeMap();

	void ChangeTileType(int _x, int _y);
	void ApplyTileAttributes(int _i, int _j);
	bool CollisionCheck(SDL_Rect _nodeRect, int _mx, int _my);
	
	bool GetStartAndEnd(int &_start1, int &_start2,
						int &_end1, int &_end2,
						bool &_s, bool &_e);
	bool CalculateDistance(int _startY, int _startX, int _endY, int _endX);
	int CalculateDistance(Node *_node);
	bool AssignChildren();
	void NextNode();

	void DeactivateNodeMap();
};

#endif 