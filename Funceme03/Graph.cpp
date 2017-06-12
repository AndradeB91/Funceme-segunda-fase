#include "graph.h"

Graph::Graph(int numVertices)
	:m_numVertices{ numVertices }
{
	m_adjList = new std::vector<Vertex* >[numVertices];
}

Graph::~Graph()
{
}

std::vector<Vertex *> Graph::getNeighbors(Vertex* vertex)
{
	return m_adjList[vertex->getId()];
}

std::vector<Vertex *>* Graph::getAdjList()
{
	return m_adjList;
}

const int &Graph::getNumVertices()
{
	return m_numVertices;
}



