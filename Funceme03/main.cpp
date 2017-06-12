#include <iostream>
#include <stdio.h>

#include "graphdriver.h"

constexpr auto P = Type::PROVIDER;
constexpr auto J = Type::JOINT;
constexpr auto C = Type::CLIENT;

int main()
{
	//Provider
	Vertex v0(P, 0, 200);

	//Joints
	Vertex v1(J, 1);

	//Clients
	Vertex v2(C, 2, 20);
	Vertex v3(C, 3, 30);
	Vertex v4(C, 4, 10);


	//The adjacency connection on the graph
	std::vector<Edge> edges =
	{
		{ &v0, &v2 },
		{ &v0, &v1 },
		{ &v1, &v3 },
		{ &v1, &v4 }
	};

	auto graphSize = edges.size() + 1;
	GraphDriver graphDriver(graphSize, edges);
	graphDriver.run(&v0);

	getchar();
}

