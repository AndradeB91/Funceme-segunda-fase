#include "edge.h"

Edge::Edge(Vertex* src, Vertex* dest)
	:m_src{ src }, m_dest{ dest }
{
}

Edge::~Edge()
{
}

Vertex* Edge::getSrc()
{
	return m_src;
}

Vertex *Edge::getDest()
{
	return m_dest;
}
