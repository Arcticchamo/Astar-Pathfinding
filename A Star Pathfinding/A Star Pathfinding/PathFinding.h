#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "NodeMap.h"
#include "Node.h"

#include <vector>

class Pathfinding
{
private:
	NodeMap *m_nodemap; //Reference the Node Map
	//std::vector<Node*> m_closeList; //Store any used Nodes within

	//How many nodes are along the x and y 
	int m_nodesAlongX, m_nodesAlongY;


	int m_startNode[2];
	int m_endNode[2];

	bool m_startNodeFound, m_endNodeFound;
	bool m_distanceCalculated;
	bool m_runAlgorithm;
	bool m_endFound;

public:

	Pathfinding(int _x, int _y);
	
	void GetNodeMap(NodeMap *_nodemap);

	bool PathfindingAlgorithm();
	void CalculateDistance();

	void DeactivatePathfinding();

	~Pathfinding(){}
};

#endif