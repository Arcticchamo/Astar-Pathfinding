#include "PathFinding.h"

Pathfinding::Pathfinding(int _x, int _y)
{
	m_nodesAlongX = _x;
	m_nodesAlongY = _y;

	m_startNodeFound = false;
	m_endNodeFound = false;
	m_runAlgorithm = false;
	m_distanceCalculated = false;
	m_endFound = false;
}

void Pathfinding::GetNodeMap(NodeMap *_nodemap)
{
	//Get a reference of the nodemap
	m_nodemap = _nodemap;
}

bool Pathfinding::PathfindingAlgorithm()
{
	//If neither the start or end point have been found
	//We access the nodemap to find the start and end.
	//If successful, the algorithm will start to compute, 
	//otherwise the algorithm will not run.
	if (!m_startNodeFound || !m_endNodeFound) 
	{
		m_runAlgorithm = m_nodemap->GetStartAndEnd(m_startNode[0], m_startNode[1], 
												   m_endNode[0], m_endNode[1], 
												   m_startNodeFound, m_endNodeFound);
	}
	
	if (m_runAlgorithm)
	{
		if (!m_distanceCalculated) 
				CalculateDistance();

		if (!m_endFound)
		{
			//Assign children to the current Node
			m_endFound = m_nodemap->AssignChildren(); 

			if (!m_endFound)
			{
				m_nodemap->NextNode();
				return true;
			}
			else 
			{
				m_runAlgorithm = false;
				return false;
			}
		}
		
	}
	return false;
}

void Pathfinding::CalculateDistance()
{
	//Calculate the distance from the start node to the end node
	m_distanceCalculated = m_nodemap->CalculateDistance(m_startNode[0], 
														m_startNode[1], 
														m_endNode[0], 
														m_endNode[1]);
}

void Pathfinding::DeactivatePathfinding()
{
	//Delete the nodemap reference
	m_nodemap = nullptr;
	delete m_nodemap;
}