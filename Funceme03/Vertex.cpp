#include "vertex.h"

Vertex::Vertex(Type type, int id, double value)
	:m_type{ type }, m_id{ id }, m_value{ value }
{
}

Vertex::Vertex(Type type, int id)
	: m_type{ type }, m_id{ id }
{
}

Vertex::~Vertex()
{
}

const int &Vertex::getId()
{
	return m_id;
}

const Type &Vertex::getType()
{
	return m_type;
}

const double &Vertex::getValue()
{
	return m_value;
}

void Vertex::setValue(double value)
{
	m_value = value;
}
