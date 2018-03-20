#ifndef NODE_H
#define NODE_H

#include <SDL\SDL.h>
#include <string>

class Node
{
private:
	std::string m_textureName; //Which texture to use

	//Store the position and size data as an SDL rect. 
	SDL_Rect m_nodeRect; 

	int m_gCost, //Distance from the start point
		m_hCost, //Distance from the end point
		m_restraint; //Additional cost to traverse

	bool m_startNode, 
		 m_endNode, 
		 m_isParent, 
		 m_isBlocked;

	Node* m_parent;
	std::vector<Node*> m_children;

public:
	Node(){}
	
	//Set the parameters of the Node
	Node(int _width, int _height, int _x, int _y, std::string _texture) 
	{
		m_nodeRect.w = _width;
		m_nodeRect.h = _height;
		m_nodeRect.x = _x;
		m_nodeRect.y = _y; 
		m_textureName = _texture;

		m_gCost = m_hCost = m_restraint = 0;
		m_startNode = m_endNode = m_isParent = m_isBlocked = false;
		m_parent = nullptr;
	}

	void SetTextureName(std::string _name)
	{
		m_textureName = _name;
	}

	std::string GetTextureName()
	{
		return m_textureName;
	}

	bool GetStart()
	{
		return m_startNode;
	}

	bool GetEnd()
	{
		return m_endNode;
	}

	SDL_Rect GetRect()
	{
		return m_nodeRect;
	}

	void SetHCost(int _h)
	{
		m_hCost = _h;
	}

	int GetHCost()
	{
		return m_hCost;
	}

	void SetGCost(int _g)
	{
		m_gCost = _g;
	}

	int GetGCost()
	{
		return m_gCost;
	}

	int GetFCost()
	{
		//Get the F cost by adding these 3 points
		return m_gCost + m_hCost + m_restraint;
	}

	void ChangeAttributes(int _restraint, bool _blocked, bool _startNode, bool _endNode)
	{
		m_restraint = _restraint;
		m_isBlocked = _blocked;
		m_startNode = _startNode;
		m_endNode = _endNode;
	}

	bool GetIsParent()
	{
		return m_isParent;
	}

	bool GetIsBlocked()
	{
		return m_isBlocked;
	}

	int GetNumberOfChildren()
	{
		return m_children.size();
	}

	Node* GetChild(int _i)
	{
		return m_children.at(_i);
	}

	void RemoveChild(int _i)
	{
		int Position = _i - 1;
		if (Position < 0) Position = 0;

		m_children.erase(m_children.begin() + Position);
		
	}

	void SetAsParent()
	{
		m_textureName = "Parent";
		m_isParent = true;
	}

	void AddChild(Node *_child)
	{
		m_children.push_back(_child);
	}

	void ChangeToChild(Node *_parent, std::string _tileName, int _gCost, int _hCost)
	{
		m_parent = _parent;
		m_textureName = _tileName;
		m_gCost = _gCost;
		m_hCost = _hCost;
	}

	void NodeDeactivation()
	{
		//Dereference any pointers left
		m_parent = nullptr;
		delete m_parent;

		for (unsigned int i = 0; i < m_children.size(); i++)
		{
			m_children.at(i) = nullptr;
			delete m_children.at(i);
		}
	}

	~Node()
	{}

};


#endif