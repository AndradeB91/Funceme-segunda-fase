#include "LiberationLane.h"

LiberationLane::LiberationLane(int priority, double upperLimit)
	:m_priority(priority), m_upperLimit(upperLimit)
{}

LiberationLane::~LiberationLane()
{
}

const int LiberationLane::getPriority()
{
	return m_priority;
}

const double LiberationLane::getUpperLimit()
{
	return m_upperLimit;
}