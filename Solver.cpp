#include "Solver.h"

/// Constructor  /////////////////////////////////////////////////////
Solver::Solver(unsigned a_nNodes, float **am, const vec2 *pos)
	   : m_nNodes(a_nNodes), e_adjacencyMatrix(am), e_pos(pos)
{
	m_md = new SolverMetaData[m_nNodes];	
}
/// Deconstructor  ///////////////////////////////////////////////////
Solver::~Solver()
{
	delete[] m_md;	// Clearing the MetaData
}
/// Setting MetaData  ////////////////////////////////////////////////
void Solver::path(unsigned a_start, unsigned a_goal)
{
	m_start = a_start;
	m_goal = a_goal;
	m_md[m_goal].state = eGOAL;
	m_md[m_start].state = eSTART;

	for (int i = 0; i < m_nNodes; ++i)
		m_md[i] = SolverMetaData();
	
	
	m_md[m_start].previous = m_start;
	m_md[m_start].g = 0;
	
	frontier.push_front(m_start);	// goes to next node
}
/// MetaData Getter  /////////////////////////////////////////////////
const SolverMetaData* Solver::get_md() const 
	{ return m_md; }
//////////////////////////////////////////////////////////////////////
const std::vector<int> &Solver::getSolution() const 
{ return solution; };
//////////////////////////////////////////////////////////////////////
std::vector<vec2> Solver::getSolvedPath() const
{
	std::vector<vec2> p;
	for each(int i in solution) p.push_back(e_pos[i]);
	return p;
}

std::vector<vec2> Solver::smooth(const std::vector<vec2> &path, const std::vector<aabb> &obstacles)
{
	std::vector<vec2> s;
	int curr = 0; 
	int prev = 0;
	int next = 0;

	s.push_back(path.front());

		//For each node
			//cast a line
			//For each obstacle
				//does the line collide with ANY obstacles?
					// add the previous node to the solution
					// set current to previous


	for (int i = 1; i < path.size(); ++i)	// each node
	{
		bool test = false;
		auto l = line(s.back(),path[i]);

		for (int j = 0; j < obstacles.size(); ++j)	// each obstacle
			test |= line_aabb(l, obstacles[j]).result;
		
		if (test) // if we collided...
		{			
			s.push_back(path[i-1]);
		}
	}
	
	s.push_back(path.back());
	return s;
}
/// Update Solver  ///////////////////////////////////////////////////
Solver::eResult Solver::step()
{
	if (frontier.empty()) return failed;		// check to see if empty
	frontier.sort(CompareFunctor(this));

	m_current = frontier.front();
	frontier.pop_front();

	if (m_current == m_goal) 					// If at Goal, return true.	Complete
	{
		while (!frontier.empty()) frontier.pop_front();
		int t = m_current;
		do
		{
			solution.push_back(t);
			m_md[t].state = ePATH;
			t = m_md[t].previous;
		} while (t != m_start && t >= 0 && t < m_nNodes);
		
		solution.push_back(m_start);
		std::reverse(solution.begin(), solution.end());

		m_md[m_start].state = eSTART;
		m_md[m_goal].state = eGOAL;
		return succeeded;
	}
	m_md[m_current].state = eEXPLORED;

	for (int i = 0; i < m_nNodes; ++i)		// Continue to solve path
	{
		if (e_adjacencyMatrix[m_current][i] > 0 && m_md[i].state != eEXPLORED)
		{
			// Push onto Frontier
			if (m_md[i].state == eDISCOVERED)
			{
				frontier.push_front(i);
				m_md[i].state = eFRONTIER;
			}
			// Calculate G score
			unsigned g = e_adjacencyMatrix[m_current][i] + m_md[m_current].g;
			unsigned h = distance(e_pos[i], e_pos[m_goal]);
			unsigned f = g + h;
			if (f < m_md[i].g)
			{
				m_md[i].f = f;
				m_md[i].g = g;
				m_md[i].h = h;
				m_md[i].previous = m_current;
			}
		}
	}
	
	return trying;
}
//////////////////////////////////////////////////////////////////////
std::vector<vec2> Solver::solve(unsigned a_nNodes, float **am, const vec2 *pos, int start, int goal)
{
	auto r = Solver(a_nNodes, am, pos);
	r.path(start, goal);
	r.doSolve();
	return r.getSolvedPath();
}