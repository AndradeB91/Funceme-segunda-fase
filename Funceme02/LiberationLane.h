#pragma once
class LiberationLane
{
public:
	LiberationLane() = default;
	LiberationLane(int priority, double upperLimit);
	~LiberationLane();

	const int getPriority();
	const double getUpperLimit();

private:
	int m_priority;
	double m_upperLimit;
};

