#include <iostream>

#include "priorityutils.h"

int main(int argc, char *argv[])
{
	auto pArray        = { 3,1,2 };
	auto vArray        = {8000.0, 1000.0, 2500.0};
	auto minimumVolume = 500.0;
	auto maximumVolume = 8000.0;
	auto currentVolume = 2650.0;

	PriorityUtils pUtil{};
	VectorOfPriorityZones vectorOfPriorityZones = pUtil.zonesAvailableSupply(pArray,
		vArray,
		minimumVolume,
		maximumVolume,
		currentVolume);
	pUtil.printVector(vectorOfPriorityZones);

	getchar();
	return 0;
}
