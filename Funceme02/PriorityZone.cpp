#include "PriorityZone.h"

PriorityZone::PriorityZone(double availableVolume,
	int priority) : m_availableVolume(availableVolume),
	m_priority(priority)
{
}

double PriorityZone::getAvailableVolume()
{
	return m_availableVolume;
}

int PriorityZone::getPriority()
{
	return m_priority;
}