#include "Reservoir.h"

Reservoir::Reservoir(double currentVolume, double minimumVolume, double maximumVolume)
	:	m_currentVolume(currentVolume), 
		m_minimumVolume(minimumVolume),
		m_maximumVolume(maximumVolume)
{
}

Reservoir::~Reservoir()
{
}

const double Reservoir::getCurrentVolume()
{
	return m_currentVolume;
}

const double Reservoir::getMinimumVolume()
{
	return m_minimumVolume;
}

const double Reservoir::getMaximumVolume()
{
	return m_maximumVolume;
}