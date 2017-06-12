#pragma once
#include <wx/wx.h>

#include "CreateForm.h"
#include "LiberationLanesForm.h"

#include "ReservoirDriver.h"

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	~MyFrame();

	void addReservoir(ReservoirContainer reservoirContainer);

private:

	wxGridSizer* m_applicationGrid;
	ReservoirDriver *m_reservoirDriver;

	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnHow(wxCommandEvent& event);

	void OnNew(wxCommandEvent& event);

	void OnLeftClick(wxMouseEvent& event);
	void OnRightClick(wxMouseEvent& event);

	void onMouseEnter(wxMouseEvent& event);


	DECLARE_EVENT_TABLE()

	enum
	{
		ID_Hello  = wxID_HIGHEST + 1,
		ID_About  = wxID_HIGHEST + 2,
		ID_New    = wxID_HIGHEST + 3,
		ID_How    = wxID_HIGHEST + 4
	};
};


