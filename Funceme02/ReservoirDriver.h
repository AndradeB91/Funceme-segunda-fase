#pragma once

#include <wx/wx.h>
#include <wx/grid.h>

#include "ReservoirContainer.h"

class ReservoirDriver
{
public:
	ReservoirDriver() = default;

	ReservoirDriver(
		wxWindow* window,
		const wxString path,
		wxBitmapType type,
		const wxPoint startingPoint,
		const wxSize size,
		wxSizer *sizer);

	~ReservoirDriver();

	wxBitmapButton* addReservoir(ReservoirContainer reservoirContainer);
	void            removeReservoir(int i);
	void			updateGridReservoir(wxGrid* grid);

	std::vector<ReservoirContainer>& getReservoirContainerVector();

	std::vector<ReservoirContainer>* getPointerToReservoirContainerVector();


private:
	std::vector<ReservoirContainer> m_reservoirContainerVector;

protected:

	wxWindow* m_window;
	const wxString m_path;
	wxBitmapType m_type;
	const wxPoint m_startingPoint;
	const wxSize m_size;
	wxSizer *m_sizer;


	int m_x{ 0 };
	int m_y{ 0 };
	int m_id{ 0 };
};

