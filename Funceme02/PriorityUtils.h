#pragma once

#include "priorityZone.h"

#include <iostream>
#include <vector>
#include <algorithm>

using VectorOfPriorityZones = std::vector<PriorityZone>;

class PriorityUtils
{
public:

	PriorityUtils() = default;
	~PriorityUtils();

	/** @brief
	* Retorna o volume de água disponível em cada zona de prioridade
	* @param pArray é um vetor contendo as prioridades de cada zona
	* @param vArray é o limite superior de cada zona
	* @param minimumVolume é o volume mínimo do reservatório
	* @param maximumVolume é o volume máximo do reservatório
	* @param currentVolume é o volume atual do reservatório
	*/
	/** Crie aqui o método zonesAvailableSupply segundo as especificações logo acima **/
	VectorOfPriorityZones zonesAvailableSupply(std::vector<int> pArray,
											   std::vector<double> vArray,
											   const double minimumVolume,
											   double maximumVolume,
											   double currentVolume);

	auto printVector(VectorOfPriorityZones &vec) -> void;
};

