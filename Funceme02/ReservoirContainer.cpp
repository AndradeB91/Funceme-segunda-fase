#include "ReservoirContainer.h"

ReservoirContainer::ReservoirContainer(Reservoir reservoir, wxBitmapButton* reservoirBitmap)
	:m_reservoir(reservoir), m_reservoirBitmap(reservoirBitmap)
{

}

ReservoirContainer::~ReservoirContainer()
{
}

Reservoir& ReservoirContainer::getReservoir()
{
	return m_reservoir;
}

wxBitmapButton* ReservoirContainer::getReservoirBitmap()
{
	return m_reservoirBitmap;
}

std::vector<LiberationLane>& ReservoirContainer::getLiberationLaneVector()
{
	return m_liberationLaneVector;
}

std::vector<LiberationLane>* ReservoirContainer::getPointerToLiberationLaneVector()
{
	return &m_liberationLaneVector;
}

void ReservoirContainer::setReservoir(Reservoir reservoir)
{
	m_reservoir = reservoir;
}

void ReservoirContainer::setReservoirBitmap(wxBitmapButton* reservoirBitmap)
{
	m_reservoirBitmap = reservoirBitmap;
}