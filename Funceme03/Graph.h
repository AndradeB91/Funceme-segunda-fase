#pragma once
#include <vector>
#include <iostream>

#include "edge.h"

class Graph
{
public:
	Graph() = default;
	Graph(int numVertices);
	~Graph();

	std::vector<Vertex *> getNeighbors(Vertex* vertex);
	std::vector<Vertex *>* getAdjList();
	const int &getNumVertices();

private:
	int m_numVertices{};
	std::vector<Vertex *>* m_adjList;
	Vertex* m_provider;
};

