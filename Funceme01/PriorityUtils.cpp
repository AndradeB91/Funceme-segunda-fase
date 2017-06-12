///** priorityUtils.cpp **/
#include "priorityUtils.h"

PriorityUtils::~PriorityUtils()
{}

VectorOfPriorityZones PriorityUtils::zonesAvailableSupply(std::vector<int> pArray,
														  std::vector<double> vArray,
														  double minimumVolume,
														  double maximumVolume,
														  double currentVolume)
{
	if (pArray.size() != vArray.size())
	{
		return{};
	}

	//The resulting vector of priority zones itself
	VectorOfPriorityZones result{};

	//How many zones there are
	const auto zonesAmount = vArray.size();

	auto trackVolume = minimumVolume;

	sort(begin(pArray), end(pArray));
	sort(begin(vArray), end(vArray));

	for (auto i = 0; i < zonesAmount; i++)
	{
		if (vArray.at(i) <= trackVolume)
		{
			result.push_back(PriorityZone(0, pArray.at(i)));
		}
		else if (vArray.at(i) >= currentVolume)
		{
			result.push_back(PriorityZone(currentVolume - trackVolume, pArray.at(i)));
			trackVolume = currentVolume;
		}
		else
		{
			result.push_back(PriorityZone(vArray.at(i) - trackVolume, pArray.at(i)));
			trackVolume = vArray.at(i);
		}
	}

	return result;
}

auto PriorityUtils::printVector(VectorOfPriorityZones &vec) -> void
{
	std::cout << "[\n";
	for (auto& e : vec)
	{
		std::cout << "  {" << e.getPriority() << ", " << e.getAvailableVolume() << "},\n";
	}
	std::cout << "]\n";
}

