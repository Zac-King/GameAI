#pragma once
#include "dep\cmathutils.h"
#include "dep\shapes.h"
#include <queue>	//BFS
#include <stack>	//DFS
#include <list>		//Dijkstra's	Could also use Priority queue
enum MD_STATE { eDISCOVERED, eFRONTIER, eEXPLORED, ePATH, eSTART, eGOAL };

struct SolverMetaData
{
	MD_STATE state;
	unsigned int g, f, h;
	unsigned previous;
	SolverMetaData() : state(eDISCOVERED), g(UINT_MAX){}
};

class Solver
{
	SolverMetaData *m_md;
	std::vector<int>solution;
	std::list<unsigned> frontier;	// Changing this changes path method
	const vec2 *e_pos;
	float **e_adjacencyMatrix;
	unsigned m_nNodes;
	unsigned m_start, m_goal, m_current;

public:
	Solver(unsigned a_nNodes, float **am, const vec2 *pos);
	~Solver();

	struct CompareFunctor
	{
		Solver *s;
		CompareFunctor(Solver *s) : s(s){}
		bool operator()(int left, int right)
		{	return s->get_md()[left].f < s->get_md()[right].f;	}
	};

	const SolverMetaData *get_md() const;
	const std::vector<int> &getSolution() const;
	std::vector<vec2> getSolvedPath() const;
	static std::vector<vec2> smooth(const std::vector<vec2> &path, const std::vector<aabb> &obstacles);

	void doSolve()	{ while (!step()); }
	void path(unsigned a_start, unsigned a_goal);
	bool operator()(int left, int right);
	enum eResult { trying, failed, succeeded };
	eResult step();

	static std::vector<vec2> solve(unsigned a_nNodes, float **am, const vec2 *pos, int start, int goal);
};