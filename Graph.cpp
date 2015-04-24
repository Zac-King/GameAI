#include "Graph.h"


const vec2 *Graph::getPostitions()   const{ return m_positions; }
float **Graph::getAdjacencyMatrix()  const{ return m_adjacencyMatrix; }
const unsigned int Graph::size()	 const{ return m_nNodes; }
const unsigned int Graph::maxSize()	 const{ return m_maxNodes; }

/// Constructor  /////////////////////////////////////////////////////
Graph::Graph(int a_nNodes) : m_maxNodes(a_nNodes), m_nNodes(0)		
{
	m_positions = new vec2[m_maxNodes];
	m_adjacencyMatrix = new float *[m_maxNodes];
	for (int i = 0; i < m_maxNodes; ++i)
	{
		m_adjacencyMatrix[i] = new float[m_maxNodes];
		memset(m_adjacencyMatrix[i], 0, 4 * m_maxNodes);
	}
	memset(m_positions, 0, sizeof(vec2)* m_maxNodes);
}
/// Deconstructor  ///////////////////////////////////////////////////
Graph::~Graph()
{
	for (int i = 0; i < m_maxNodes; ++i)
		delete[] m_adjacencyMatrix[i];
	delete[] m_adjacencyMatrix;
	delete[] m_positions;
}
/// Add Node to Graph  ///////////////////////////////////////////////
int  Graph::addNode(const vec2 &pos)
{
	if (m_nNodes == m_maxNodes)
		return -1;

	m_positions[m_nNodes] = pos;
	m_nNodes++;
	return m_nNodes - 1;
}
/// Set Edge between Nodes  //////////////////////////////////////////
bool Graph::setEdge(unsigned int nid1, unsigned int nid2, float weight)
{
	if (nid1 >= m_nNodes || nid2 >= m_nNodes || weight < 0)
		return false;
	m_adjacencyMatrix[nid1][nid2] = weight;
	m_adjacencyMatrix[nid2][nid1] = weight;
	return true;
}
/// Find Closest Node to Position  ///////////////////////////////////
int  Graph::findNode(const vec2 &pos)
{
	float d;
	for (int i = 0; i < m_maxNodes; ++i)
	{
		if (i == 0)
			d = distance(pos, m_positions[i]);
		else
		{
			auto a = distance(pos, m_positions[i]);
			if (a <= d)
				d = a;
		}
	}
	return d;
}
//////////////////////////////////////////////////////////////////////
void Graph::removeBlock(const vec2 &a, const vec2 &b)
{
	for (int i = 0; i < m_nNodes; ++i)
	{		//  ( x > a.x  &&  x < b.x	||	x > b.x  &&  x < a.x ) && ( y > a.y  &&  y < b.y	||	y > b.y  &&  y < a.y)		
		if (((m_positions[i].x > a.x && m_positions[i].x < b.x) || (m_positions[i].x > b.x && m_positions[i].x < a.x)) && 
			 (m_positions[i].y > a.y && m_positions[i].y < b.y) || (m_positions[i].y > b.y && m_positions[i].y < a.y))
		for (int j = 0; j < m_nNodes; ++j)
		{
			m_adjacencyMatrix[i][j] = 0;
			m_adjacencyMatrix[j][i] = 0;
		}
	}

	auto obstacle = aabb(mid(a,b),b-a);
	for (int i = 0; i < m_nNodes; ++i)
		for (int j = 0; j < m_nNodes; ++j)
			if (m_adjacencyMatrix[i][j] > 0)
			{			
				auto l = line(m_positions[i],m_positions[j]);	
				if (line_aabb(l,obstacle).result)
					m_adjacencyMatrix[i][j] = 0;
			}
}

Graph* Graph::makeGrid(int rows, int cols, float width, float height , float padding)
{
	height -= padding*2;
	width -= padding*2;
	Graph *g = new Graph(rows*cols);
	// Making all the nodes
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
			g->addNode(vec2((r * height / (rows - 1)) + padding, (c * width / (cols - 1)) + padding));
	}
	// Setting all the edges
	for (int i = 0; i < g->size(); ++i)
	{
		if ((i+1) % cols != 0)		// Up
			g->setEdge(i, (i + 1), distance(g->getPostitions()[i], g->getPostitions()[i + 1]));

		if(i + cols < g->size())	// Right
			g->setEdge(i, i + cols, distance(g->getPostitions()[i], g->getPostitions()[i + cols]));

		if ((i + 1) % rows != 0)	// Up and Right
			g->setEdge(i, (i + rows + 1), distance(g->getPostitions()[i], g->getPostitions()[i + rows + 1]));

		if ((i + 1) % rows != 1)	// Down and Left
			g->setEdge(i, i + rows - 1, distance(g->getPostitions()[i], g->getPostitions()[i + rows - 1]));
	}
	return g;
}

void Graph::drawGraph(const Solver &md, mat4 orth)
{
	for (int i = 0; i < this->size(); ++i)
	{
		for (int j = 0; j < this->size(); ++j)
		{
			if (this->getAdjacencyMatrix()[i][j] > 0)
				draw_line(orth, line(this->getPostitions()[i], this->getPostitions()[j]), vec4(0.3, 0.1, 0.1, 1));
		}

		vec4 color;
		switch (md.get_md()[i].state)
		{
		case eDISCOVERED:	color = vec4(0, 0.3, 6, 0);		break;
		case eFRONTIER:		color = vec4(4, 4, 0, 1);		break;
		case eEXPLORED:		color = vec4(.4, .4, .4, 1);	break;
		case ePATH:			color = vec4(1, 1, 1, 1);		break;
		case eSTART:		color = vec4(0, 7, .25, 0);		break;
		case eGOAL:			color = vec4(0, 7, 0.5, 0);		break;
		}
		draw_point(orth, point(this->getPostitions()[i]), color);
	}

}
