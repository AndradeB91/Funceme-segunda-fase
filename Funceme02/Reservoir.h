#pragma once

class Reservoir
{
public:
	Reservoir() = default;
	Reservoir(double currentVolume, double minimumVolume, double maximumVolume);
	~Reservoir();

	const double getCurrentVolume();
	const double getMinimumVolume();
	const double getMaximumVolume();

protected:
	double m_currentVolume;
	double m_minimumVolume;
	double m_maximumVolume;
};

