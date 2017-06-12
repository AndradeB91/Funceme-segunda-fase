#pragma once
/** priorityZone.h **/

class PriorityZone
{
protected:
	double m_availableVolume;
	int m_priority;
public:
	PriorityZone(double availableVolume, int priority);
	double getAvailableVolume();
	int getPriority();
};