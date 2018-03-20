#include "NodeMap.h"

NodeMap::NodeMap()
{

}

void NodeMap::SetUp(SDL_Renderer *_renderer, 
					const int _width, 
					const int _height, 
					const int _x, 
					const int _y)
{
	m_renderer = _renderer;

	m_nodesAlongX = _x;
	m_nodesAlongY = _y;

	//First calculate the size of each node
	m_nodeWidth = _width / _x;
	m_nodeHeight = _height / _y;

	//Fill the nodemap with each node
	for (int i = 0; i < _y; i++)
	{
		std::vector<Node> NodeLayer;
		for (int j = 0; j < _x; j++)
		{
			int Xpos = m_nodeWidth * j;
			int Ypos = m_nodeHeight * i;
			NodeLayer.push_back(Node(m_nodeWidth, m_nodeHeight, Xpos, Ypos, "Base"));
		}
		m_nodegrid.push_back(NodeLayer);
	}
	
}

void NodeMap::RenderNodeMap()
{
	for (int i = 0; i < m_nodesAlongY; i++)
	{
		for (int j = 0; j < m_nodesAlongX; j++)
		{
			SDL_RenderCopy(m_renderer, 
				Resources::GetTexture(m_nodegrid.at(i).at(j).GetTextureName()),
				NULL, 
				&m_nodegrid.at(i).at(j).GetRect()); 
		}
	}
}

void NodeMap::ChangeTileType(int _x, int _y)
{
	for (int i = 0; i < m_nodesAlongY; i++)
	{
		for (int j = 0; j < m_nodesAlongX; j++)
		{
			if (CollisionCheck(m_nodegrid.at(i).at(j).GetRect(), _x, _y))
			{
				m_nodegrid.at(i).at(j).SetTextureName(Input::GetSelectedName());
				ApplyTileAttributes(i, j);
				return;
			}
		}
	}
}

void NodeMap::ApplyTileAttributes(int _i, int _j)
{
	std::string NodeTextName = m_nodegrid.at(_i).at(_j).GetTextureName();

	//If the node is the start or end node, the node cannot be blocked or 
	//have any restraint as it is a key node.
	if (NodeTextName == "Base") 
	{
		m_nodegrid.at(_i).at(_j).ChangeAttributes(0, false, false, false);
	}
	else if (NodeTextName == "Start")
	{
		m_nodegrid.at(_i).at(_j).ChangeAttributes(0, false, true, false);
	}
	else if (NodeTextName == "End")
	{
		m_nodegrid.at(_i).at(_j).ChangeAttributes(0, false, false, true);
	}
	else if (NodeTextName == "Rough")
	{
		m_nodegrid.at(_i).at(_j).ChangeAttributes(2, false, false, false);
	}
	else if (NodeTextName == "Blocked")
	{
		m_nodegrid.at(_i).at(_j).ChangeAttributes(50, true, false, false);
	}
}

bool NodeMap::CollisionCheck(SDL_Rect _nodeRect, int _mx, int _my)
{
	if (_mx < _nodeRect.x) return false;
	if (_my < _nodeRect.y) return false;
	if (_mx > _nodeRect.x + _nodeRect.w) return false;
	if (_my > _nodeRect.y + _nodeRect.h) return false;
	return true;
}

bool NodeMap::GetStartAndEnd(int &_start1, int &_start2,
							int &_end1, int &_end2,
							bool &_s, bool &_e)
{
	for (int i = 0; i < m_nodesAlongY; i++)
	{
		for (int j = 0; j < m_nodesAlongX; j++)
		{
			if (m_nodegrid.at(i).at(j).GetStart() && !_s) {_s = true; _start1 = i; _start2 = j;}
			if (m_nodegrid.at(i).at(j).GetEnd() && !_e) {_e = true; _end1 = i; _end2 = j;}
			if (_s && _e) 
			{
				m_endNode = &m_nodegrid.at(_end1).at(_end2);
				m_currentNode = &m_nodegrid.at(_start1).at(_start2);
				return true;
			}
		}
	}

	if (!_s || !_e) 
	{
		std::cout << "ERROR!: Start or End Node was not found!" << std::endl;
		return false;
	}
	return false;
}

bool NodeMap::CalculateDistance(int _startY, int _startX, int _endY, int _endX)
{
	//Temp Costs needed for calculations
	int Xdifference = 0, Ydifference = 0, Cost = 0;
	int StartX = 0, StartY = 0, EndX = 0, EndY = 0;

	//Calculate the positional numbers depending on there width and height.
	//If x pos is 400 and width is 40, then the node is the 10th node along the X axis
	StartX = (int)m_nodegrid.at(_startY).at(_startX).GetRect().x / m_nodeWidth;
	StartY = (int)m_nodegrid.at(_startY).at(_startX).GetRect().y / m_nodeHeight;
	EndX = (int)m_nodegrid.at(_endY).at(_endX).GetRect().x / m_nodeWidth;
	EndY = (int)m_nodegrid.at(_endY).at(_endX).GetRect().y / m_nodeHeight;

	//Find the differences between the 2 nodes
	if (StartX == EndX) Xdifference = 0;
	else if (StartX < EndX) Xdifference = EndX - StartX;
	else if (StartX > EndX) Xdifference = StartX - EndX;

	if (StartY == EndY) Ydifference = 0;
	else if (StartY < EndY) Ydifference = EndY - StartY;
	else if (StartY > EndY) Ydifference = StartY - EndY;

	//Path costs are effected by the direction they travel in
	//if either up, down, left or right, the cost will be 10
	//if diagonal in any direction, the cost becomes 14 
	if (Xdifference == Ydifference) Cost = 14 * Xdifference; //Means there is a straight diagonal path to the end
	else if (Xdifference < Ydifference)
	{
		//Means that there is a slight diagonal path then straight
		Cost = 14 * Xdifference; //Add the diagonal path cost
		Cost += 10 * (Ydifference - Xdifference); //Then add the straight
	}
	else if (Xdifference > Ydifference)
	{
		Cost = 14 * Ydifference;
		Cost += 10 * (Xdifference - Ydifference);
	}
	//The cost should now equal the distance value from start to end

	m_nodegrid.at(_startY).at(_startX).SetHCost(Cost);
	m_nodegrid.at(_endY).at(_endX).SetGCost(Cost);
	return true; //Distance has been calculated
}

bool NodeMap::AssignChildren()
{
	if (m_currentNode == nullptr) return false;

	//If the nodes are along any edge
	bool NullX, NullY, FullX, FullY;
	NullX = NullY = FullX = FullY = false;

	int CurrentNodeNumberX = 0;
	int CurrentNodeNumberY = 0;

	for (int i = 0; i < m_nodesAlongY; i++)
	{
		for (int j = 0; j < m_nodesAlongX; j++)
		{
			if (&m_nodegrid.at(i).at(j) == m_currentNode)
			{
				CurrentNodeNumberX = j;
				CurrentNodeNumberY = i;
				i = m_nodesAlongY;
				j = m_nodesAlongX;
				break;
			}
		}
	}

	//Change the node to be recognised as a parent
	m_currentNode->SetAsParent();

	//Check to see if the current node is around any edge of the node map
	if (m_currentNode->GetRect().x < m_nodeWidth) NullX = true; //Is the first X node in its row
	else if (m_currentNode->GetRect().x > (m_nodesAlongX - 1) * m_nodeWidth) FullX = true; //Is the last X node in its row
	else {NullX = false; FullX = false;}

	if (m_currentNode->GetRect().y < m_nodeHeight) NullY = true; 
	else if (m_currentNode->GetRect().y > (m_nodesAlongY - 1) * m_nodeHeight) FullY = true; 
	else {NullY = false; FullY = false;}

	Node *TempNode;

	if (!NullY) //Straight Top Node
	{
		TempNode = &m_nodegrid.at(CurrentNodeNumberY - 1).at(CurrentNodeNumberX);
		
		if (TempNode->GetIsParent() || TempNode->GetIsBlocked()){} //Do nothing here
		else 
		{
			int hCost = CalculateDistance(TempNode);
			TempNode->ChangeToChild(m_currentNode, "Child", m_currentNode->GetGCost() + 10, hCost);
			m_currentNode->AddChild(TempNode);
		}
	}
	
	if (!NullX) //Straight Left Node
	{
		TempNode = &m_nodegrid.at(CurrentNodeNumberY).at(CurrentNodeNumberX - 1);

		if (TempNode->GetIsParent() || TempNode->GetIsBlocked()){} //Do nothing here
		else 
		{
			int hCost = CalculateDistance(TempNode);
			TempNode->ChangeToChild(m_currentNode, "Child", m_currentNode->GetGCost() + 10, hCost);
			m_currentNode->AddChild(TempNode);
		}
	}

	if (!FullY) //Straight Bottom Node
	{
		TempNode = &m_nodegrid.at(CurrentNodeNumberY + 1).at(CurrentNodeNumberX);

		if (TempNode->GetIsParent() || TempNode->GetIsBlocked()){} //Do nothing here
		else 
		{
			int hCost = CalculateDistance(TempNode);
			TempNode->ChangeToChild(m_currentNode, "Child", m_currentNode->GetGCost() + 10, hCost);
			m_currentNode->AddChild(TempNode);
		}
	}

	if (!FullX) //Straight Right Node
	{
		TempNode = &m_nodegrid.at(CurrentNodeNumberY).at(CurrentNodeNumberX + 1);

		if (TempNode->GetIsParent() || TempNode->GetIsBlocked()){} //Do nothing here
		else 
		{
			int hCost = CalculateDistance(TempNode);
			TempNode->ChangeToChild(m_currentNode, "Child", m_currentNode->GetGCost() + 10, hCost);
			m_currentNode->AddChild(TempNode);
		}
	}

	if (!NullX && !NullY) //Diagonal Top Left Node
	{
		TempNode = &m_nodegrid.at(CurrentNodeNumberY - 1).at(CurrentNodeNumberX - 1);

		if (TempNode->GetIsParent() || TempNode->GetIsBlocked()){} //Do nothing here
		else 
		{
			int hCost = CalculateDistance(TempNode);
			TempNode->ChangeToChild(m_currentNode, "Child", m_currentNode->GetGCost() + 14, hCost);
			m_currentNode->AddChild(TempNode);
		}
	}

	if (!NullX && !FullY) //Diagonal Bottom Left Node
	{
		TempNode = &m_nodegrid.at(CurrentNodeNumberY + 1).at(CurrentNodeNumberX - 1);

		if (TempNode->GetIsParent() || TempNode->GetIsBlocked()){} //Do nothing here
		else 
		{
			int hCost = CalculateDistance(TempNode);
			TempNode->ChangeToChild(m_currentNode, "Child", m_currentNode->GetGCost() + 14, hCost);
			m_currentNode->AddChild(TempNode);
		}
	}

	if (!FullX && !NullY) //Diagonal Top Right Node
	{
		TempNode = &m_nodegrid.at(CurrentNodeNumberY - 1).at(CurrentNodeNumberX + 1);

		if (TempNode->GetIsParent() || TempNode->GetIsBlocked()){} //Do nothing here
		else 
		{
			int hCost = CalculateDistance(TempNode);
			TempNode->ChangeToChild(m_currentNode, "Child", m_currentNode->GetGCost() + 14, hCost);
			m_currentNode->AddChild(TempNode);
		}
	}

	if (!FullX && !FullY) //Diagonal Bottom Right Node
	{
		TempNode = &m_nodegrid.at(CurrentNodeNumberY + 1).at(CurrentNodeNumberX + 1);

		if (TempNode->GetIsParent() || TempNode->GetIsBlocked()){} //Do nothing here
		else 
		{
			int hCost = CalculateDistance(TempNode);
			TempNode->ChangeToChild(m_currentNode, "Child", m_currentNode->GetGCost() + 14, hCost);
			m_currentNode->AddChild(TempNode);
		}
	}

	if (TempNode != nullptr) 
	{
		TempNode = nullptr;
		delete TempNode;
	}

	m_closedList.push_back(m_currentNode);

	for (int i = 0; i < m_currentNode->GetNumberOfChildren(); i++)
	{
		Node *tempChildNode = m_currentNode->GetChild(i); 

		if (tempChildNode == m_endNode && tempChildNode != nullptr)
		{
			m_endNode->SetTextureName("End");
			m_closedList.push_back(m_endNode);
			tempChildNode = nullptr;
			delete tempChildNode;
			return true;
		}

		tempChildNode = nullptr;
		delete tempChildNode;
	}

	return false;
}

int NodeMap::CalculateDistance(Node *_node)
{
	int Xdifference = 0, Ydifference = 0, Cost = 0;
	int StartX = 0, StartY = 0, EndX = 0, EndY = 0;

	StartX = _node->GetRect().x / m_nodeWidth; 
	StartY = _node->GetRect().y / m_nodeHeight;
	EndX = m_endNode->GetRect().x / m_nodeWidth;
	EndY = m_endNode->GetRect().y / m_nodeHeight;

	if (StartX == EndX) Xdifference = 0; 
	else if (StartX < EndX) Xdifference = EndX - StartX;
	else if (StartX > EndX) Xdifference = StartX - EndX;

	if (StartY == EndY) Ydifference = 0;
	else if (StartY < EndY) Ydifference = EndY - StartY;
	else if (StartY > EndY) Ydifference = StartY - EndY;

	if (Xdifference == Ydifference) Cost = 14 * Xdifference;
	else if (Xdifference < Ydifference)
	{
		Cost = 14 * Xdifference;
		Cost += 10 * (Ydifference - Xdifference);
	}
	else if (Xdifference > Ydifference)
	{
		Cost = 14 * Ydifference;
		Cost += 10 * (Xdifference - Ydifference);
	}

	return Cost;
}

void NodeMap::NextNode()
{
	for (int i = 0; i < m_closedList.size(); i++)
	{
		for (int j = 0; j < m_closedList.at(i)->GetNumberOfChildren(); j++)
		{
			if (m_closedList.at(i)->GetChild(j) == m_currentNode)
			{
				m_closedList.at(i)->RemoveChild(j);
			}
		}
	}



	int LowestFCost = 10000;
	std::vector< Node* > NumberOfNodes;

	//Run through the entire closed list and see the Lowest F Cost 
	//in all the children
	for (unsigned int i = 0; i < m_closedList.size(); i++)
	{
		int Size = m_closedList.at(i)->GetNumberOfChildren();

		for (int j = 0; j < Size; j++)
		{
			int FCost = m_closedList.at(i)->GetChild(j)->GetFCost();

			if (LowestFCost > FCost)
			{
				LowestFCost = FCost;
			}
		}
	}

	//Then Find all the children with the lowest FCost
	for (unsigned int i = 0; i < m_closedList.size(); i++)
	{
		int Size = m_closedList.at(i)->GetNumberOfChildren();

		for (int j = 0; j < Size; j++)
		{
			int FCost = m_closedList.at(i)->GetChild(j)->GetFCost();

			if (LowestFCost == FCost)
			{
				NumberOfNodes.push_back(m_closedList.at(i)->GetChild(j));
			}
		}
	}

	if (NumberOfNodes.size() == 1)
	{
		m_currentNode = NumberOfNodes.at(0);
		return; 
	}
	else 
	{
		int LowestGCost = 10000;

		for (unsigned int i = 0; i < NumberOfNodes.size(); i++)
		{
			int GCost = NumberOfNodes.at(i)->GetGCost();

			if (LowestGCost > GCost)
			{
				LowestGCost = GCost;
			}
		}

		for (unsigned i = 0; i < NumberOfNodes.size(); i++)
		{
			int GCost = NumberOfNodes.at(i)->GetGCost();
			if (LowestGCost == GCost)
			{
				for (int j = 0; j < m_currentNode->GetNumberOfChildren(); j++)
				{
					if (m_currentNode->GetChild(j) == NumberOfNodes.at(i))
					{
						m_currentNode->RemoveChild(j);
					}
				}


				if (m_currentNode == NumberOfNodes.at(i))
				{
					std::cout<<"THIS IS BROKEN AS FUCK";
				}

				m_currentNode = NumberOfNodes.at(i);
				

				//FIND ANOTHER WAY TO DO THIS WITHOUT THE FOR LOOP
				//MAYBE DELETE AS THE LOOP GOES
				//
				//MAY NOT WORK AS THE SIZE WILL SLOWLY GO DOWN AS THE POINTERS GET DELETE
				//IF THIS IS TRUE. CREATE SOME TEMPORARY WAY FOR TESTING, THEN DO THE ABOVE
				for (unsigned int j = 0; j < NumberOfNodes.size(); j++)
				{
					if (j != i)
					{
						NumberOfNodes.at(j) = nullptr;
					}
				}
				break;
			}
		}

		NumberOfNodes.clear();
	}
}

void NodeMap::DeactivateNodeMap()
{
	for (int i = 0; i < m_nodesAlongY; i++)
	{
		for (int j = 0; j < m_nodesAlongX; j++)
		{
			m_nodegrid.at(i).at(j).NodeDeactivation();
		}
	}
	m_nodegrid.clear();

	for (int i = 0; i < m_closedList.size(); i++)
	{
		m_closedList.at(i) = nullptr;
		delete m_closedList.at(i);
	}
	m_closedList.clear();

	m_currentNode = nullptr;
	delete m_currentNode;

	m_renderer = nullptr;
	delete m_renderer;
}

NodeMap::~NodeMap()
{
}