#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/valtext.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/tglbtn.h>
#include <wx/panel.h>
#include <wx/wx.h>

#include "ReservoirContainer.h"
#include "MyFrame.h"

class CreateForm : public wxFrame
{
public:

	CreateForm(wxWindow* parent,
		wxWindowID id = wxID_ANY,
		const wxString& title = wxEmptyString,
		const wxPoint& pos = wxPoint(-1, -1),
		const wxSize& size = wxSize(300, 250),
		long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~CreateForm();

protected:
	wxStaticText* m_currentVolumeLabel;
	wxTextCtrl*   m_currentVolumeEntry;
	wxStaticText* m_minimumVolumeLabel;
	wxTextCtrl*   m_minimumVolumeEntry;
	wxStaticText* m_maximumVolumeLabel;
	wxTextCtrl*   m_maximumVolumeEntry;
	wxButton*     m_cancelButton;
	wxButton*     m_createButton;

	void OnCancel(wxCommandEvent& event);
	void OnCreate(wxCommandEvent& event);

	DECLARE_EVENT_TABLE()

	enum
	{
		ID_Create = wxID_HIGHEST + 1
	};
};

