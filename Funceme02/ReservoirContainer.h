#pragma once
#include <wx/wx.h>

#include "Reservoir.h"
#include "LiberationLane.h"

class ReservoirContainer
{
public:
	ReservoirContainer() = default;
	ReservoirContainer(Reservoir reservoir, wxBitmapButton* reservoirBitmap);
	~ReservoirContainer();

	Reservoir& getReservoir();
	wxBitmapButton* getReservoirBitmap();
	std::vector<LiberationLane>& getLiberationLaneVector();
	std::vector<LiberationLane>* getPointerToLiberationLaneVector();


	void setReservoir(Reservoir reservoir);
	void setReservoirBitmap(wxBitmapButton* reservoirBitmap);

	std::vector<LiberationLane> m_liberationLaneVector{};

protected:
	Reservoir m_reservoir;
	wxBitmapButton *m_reservoirBitmap;
};

