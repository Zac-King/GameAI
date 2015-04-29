#include "dep\shapes.h"
#include <iostream>
#include "Graph.h"
#include "Solver.h"
#include "GLFW\glfw3.h"
#include <cassert>
#include <time.h>
#include "Entity.h"
#include <iostream>

//DFS : Stack
//		- Checks deepest node first
//BFS : Queue
//		- Checks nearest 
//
//Dijkstra: Priority Queue (sorted by Actual cost)
//		- Sort by weight of edges
//A-Star  : Priority Queue (sorted by actual and estimated cost)
//		- Sort by weight of edges and a guess
//Greedy  : Priority Queue (sorted by estimated cost)
//		- Sort by a guess

void dumpAM(float **am, int size)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if(am[i][j])
			 std::cout << am[i][j] << " ";
			else std::cout << " " << 0 << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void dumpRow(float **am, int size, int row)
{
	for (int i = 0; i < size; ++i)
	{
		if (am[i][row])
			std::cout << am[i][row] << " ";
		else std::cout << " " << 0 << " ";
	}
	std::cout << std::endl;
}

void main()
{
	auto a = line(vec2(0, 1), vec2(5, 1));
	auto b = aabb(vec2(5, 1), vec2(2, 2));
	auto c = aabb(vec2(10, 1), vec2(2, 2));

	auto p = line(vec2(0, 0), vec2(5, 5));
	auto q = line(vec2(5, 0), vec2(0, 5));
	
	assert(line_aabb(a,b).result == true);


	srand(time(NULL));

	mul   (mat4::rotate2D(PI/4), vec2(12, 0)) == vec2(0, 12);
	mulaff(mat4::translate2D(vec2(12, 0)), vec2(12, 0)) == vec2(24, 0);

	auto w = openContext(1280, 720);	//defualt 640 x 480
	auto m = mat4::ortho(-25, 1305, -25, 745, 0, 100);

	Graph *g = Graph::makeGrid(32, 32, 720, 1280, 0);
	Solver s(g->size(), g->getAdjacencyMatrix(), g->getPostitions());
	float delay = 0.000;
	float dt, current, total = 0;  glfwSetTime(0);

	int LastGoal = 0;	int NewGoal = 0;
	bool newPath = true;

	Entity e(100, g->getPostitions()[0]);

	std::vector<aabb>bottle;
	bottle.push_back(aabb(vec2(250, 220), vec2(90, 30)));	// bottom
	bottle.push_back(aabb(vec2(135, 320), vec2(30, 180)));  // left side
	bottle.push_back(aabb(vec2(360, 320), vec2(30, 180)));  // right side
	bottle.push_back(aabb(vec2(205, 410), vec2(30, 180)));
	bottle.push_back(aabb(vec2(295, 410), vec2(30, 180)));

	for (int i = 0; i < bottle.size(); ++i)
		g->removeBlock(bottle[i].min(), bottle[i].max());
	

	while (updateContext(w))
	{
		current = glfwGetTime(); 
		dt = current - total;
		total = current;
		if (dt > .16) dt = .16;

		if (newPath)
		{
			bool trying = true;
			LastGoal = NewGoal;
			while (trying)
			{
				NewGoal = rand() % g->maxSize();
				for (int i = 0; i < g->size(); ++i)
					if (g->getAdjacencyMatrix()[NewGoal][i] > 0)
						trying = false;
			}
			//store the path in the entity
			e.path		 = Solver::solve(g->size(), g->getAdjacencyMatrix(), g->getPostitions(), LastGoal, NewGoal);
			e.smoothPath = Solver::smooth(e.path, bottle);
				//std::cout << e.path.size() << std::endl;
			newPath = false;
		}
		
		// Update Entity (The Circle)
		e.update(dt);
		// Draw graph / Entity
		//g->drawGraph(s, m);
		e.drawEntity(m, 7);
		// Draw Obstacles
		for (int i = 0; i < bottle.size(); ++i)
			draw_aabb(m, bottle[i], vec4(0, 1, 0, 0));
		
		// Draw path
		for (int i = 1; i < e.path.size(); ++i)	
		{
			//float r = rand() % 2;
			//float g = rand() % 2;
			//float b = rand() % 2;
			//float w = rand() % 2;
			draw_line(m, line(e.path[i - 1], e.path[i]), vec4(.7, .7, .6, .8));	
		}
		for (int i = 1; i < e.smoothPath.size(); ++i)
		{
			draw_line(m, line(e.smoothPath[i - 1], e.smoothPath[i]), vec4(1, 0, 1, 1));
		}

		if (e.index == e.smoothPath.size())
		{	e.index = 0;	newPath = true;	}
		

	}
	
	closeContext(w);
	
}