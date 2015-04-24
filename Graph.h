#pragma once
#include "dep/cmathutils.h"
#include "dep\shapes.h"
#include "Solver.h"
#include <vector>

class Graph
{
	vec2   *m_positions;		// node Positions
	int     m_nNodes;			// number of nodes
	int		m_maxNodes;			// Maxium number of nodes
	float **m_adjacencyMatrix;	// edges

public:
	const vec2   *getPostitions() const;
	float  **getAdjacencyMatrix() const;
	const     unsigned int size() const;
	const unsigned int  maxSize() const;

	Graph(int a_nNodes);
	~Graph();

	int  addNode(const vec2 &pos);
	bool setEdge(unsigned int nid1, unsigned int nid2, float weight = 1.0);
	int  findNode(const vec2 &pos);

	void removeBlock(const vec2 &a, const vec2 &b);

	void  drawGraph(const Solver &md, mat4 orth);
	static Graph *makeGrid(int rows = 32, int cols = 32, float width = 720, float height = 480, float padding = 20);

};