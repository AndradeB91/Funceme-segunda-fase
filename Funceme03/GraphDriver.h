#pragma once
#include "graph.h"

class GraphDriver
{
public:
	GraphDriver() = default;
	GraphDriver(int graphSize, std::vector<Edge> edges);
	~GraphDriver();

	void printGraph();

	void run(Vertex* provider);

private:
	Graph m_graph;
	void buildAdjList(std::vector<Edge> edges);

	bool reachingClients(int step, Vertex *provider, float *clientsRequest);
	bool stepExecution(int step, Vertex *provider);
};


