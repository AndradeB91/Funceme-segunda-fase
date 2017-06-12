#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/gdicmn.h>
#include <wx/toolbar.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/statline.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/frame.h>

#include <fstream>
#include <sstream>
#include <string>

#include "ReservoirDriver.h"
#include "PriorityUtils.h"

class LiberationLanesForm : public wxFrame
{
public:

	LiberationLanesForm(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~LiberationLanesForm();
	void setReservoirDriver(ReservoirDriver* reservoirDriver);
	void initForm();
	void setReservoirId(int reservoirId);

private:

	ReservoirDriver* m_reservoirDriver;
	int m_reservoirId;

	void resetGrid();

	void plusOnClick(wxCommandEvent& event);
	void minusOnClick(wxCommandEvent& event);
	void eraseOnClick(wxCommandEvent& event);
	void writeOnClick(wxCommandEvent& event);
	void saveOnClick(wxCommandEvent& event);
	void loadOnClick(wxCommandEvent& event);
	void showAvailableWaterOnClick(wxCommandEvent& event);
	void gridOnChange(wxGridEvent& event);

protected:
	wxToolBar* m_fileToolBar;
	wxStaticLine* m_staticline;
	wxToolBar* m_addRemoveToolBar;
	wxGrid* m_reservoirGrid;

	wxToolBarToolBase* m_save;
	wxToolBarToolBase* m_load;
	wxToolBarToolBase* m_write;
	wxToolBarToolBase* m_erase;
	wxToolBarToolBase* m_plus;
	wxToolBarToolBase* m_minus;
	wxToolBarToolBase* m_water;
};
