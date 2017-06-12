#pragma once
#include "vertex.h"

class Edge
{
public:
	Edge() = default;
	Edge(Vertex* src, Vertex* dest);
	~Edge();

	Vertex* getSrc();
	Vertex* getDest();

private:
	Vertex* m_src;
	Vertex* m_dest;
};

