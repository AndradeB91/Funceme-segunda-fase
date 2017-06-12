#pragma once
enum class Type { PROVIDER, JOINT, CLIENT };

class Vertex
{
public:

	Vertex() = default;
	Vertex(Type type, int id, double value);
	Vertex(Type type, int id);

	~Vertex();

	const int &getId();
	const Type &getType();
	const double &getValue();

	void setValue(double value);

private:

	int m_id;
	Type m_type;
	double m_value{};

};