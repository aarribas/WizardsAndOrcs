#pragma once
#include "stlastar.h" // See header for copyright and usage information

// Definitions

class MapSearchNode
{
public:
	unsigned int x;	 // the (x,y) positions of the node
	unsigned int y;	
	
	MapSearchNode() { x = y = 0; }
	MapSearchNode( unsigned int px, unsigned int py ) { x=px; y=py; }

	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
	float GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );
	void PrintNodeInfo();
	void SetMap(int *map,int mapWidth, int mapHeight);
	int GetMap( int x, int y );

private:
	int *m_map;
	int m_mapWidth;
	int m_mapHeight;
};