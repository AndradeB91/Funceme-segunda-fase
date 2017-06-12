#include "CreateForm.h"

CreateForm::CreateForm (wxWindow* parent, wxWindowID id, 
						const wxString& title, 
						const wxPoint& pos, 
						const wxSize& size, 
						long style ) 
						: wxFrame(parent, id, title, pos, size, style)
{

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetSize(300, 260);
	this->SetMaxSize(wxSize(300,260));
	this->SetMinSize(wxSize(300, 260));

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Características")), wxVERTICAL);

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer(new wxStaticBox(sbSizer1->GetStaticBox(), wxID_ANY, wxT("Volumes")), wxVERTICAL);

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer(0, 2, 0, 100);

	m_currentVolumeLabel = new wxStaticText(sbSizer2->GetStaticBox(), wxID_ANY, wxT("Inicial (hm³)"), wxDefaultPosition, wxDefaultSize, 0);
	m_currentVolumeLabel->Wrap(-1);
	gSizer1->Add(m_currentVolumeLabel, 0, wxALL, 5);

	m_currentVolumeEntry = new wxTextCtrl(sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1, -1), 0);
	gSizer1->Add(m_currentVolumeEntry, 0, wxALL | wxEXPAND, 5);

	m_minimumVolumeLabel = new wxStaticText(sbSizer2->GetStaticBox(), wxID_ANY, wxT("Mínimo (hm³)"), wxDefaultPosition, wxDefaultSize, 0);
	m_minimumVolumeLabel->Wrap(-1);
	gSizer1->Add(m_minimumVolumeLabel, 0, wxALL, 5);

	m_minimumVolumeEntry = new wxTextCtrl(sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	gSizer1->Add(m_minimumVolumeEntry, 0, wxALL | wxEXPAND, 5);

	m_maximumVolumeLabel = new wxStaticText(sbSizer2->GetStaticBox(), wxID_ANY, wxT("Máximo (hm³)"), wxDefaultPosition, wxDefaultSize, 0);
	m_maximumVolumeLabel->Wrap(-1);
	gSizer1->Add(m_maximumVolumeLabel, 0, wxALL, 5);

	m_maximumVolumeEntry = new wxTextCtrl(sbSizer2->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	gSizer1->Add(m_maximumVolumeEntry, 0, wxALL | wxEXPAND, 5);


	gSizer1->Add(0, 10, 0, 0, 5);


	sbSizer2->Add(gSizer1, 1, wxEXPAND, 5);


	sbSizer1->Add(sbSizer2, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxHORIZONTAL);


	bSizer7->Add(40, 0, 1, wxEXPAND, 5);

	m_cancelButton = new wxButton(sbSizer1->GetStaticBox(), wxID_EXIT, wxT("Cancelar"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(m_cancelButton, 0, wxALL, 5);

	m_createButton = new wxButton(sbSizer1->GetStaticBox(), ID_Create, wxT("Criar"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer7->Add(m_createButton, 0, wxALL, 5);


	sbSizer1->Add(bSizer7, 1, wxALIGN_RIGHT | wxRIGHT | wxTOP, 5);


	this->SetSizer(sbSizer1);
	this->Layout();

	this->Centre(wxBOTH);

	this->SetBackgroundColour(wxColour(*wxWHITE));
}

CreateForm::~CreateForm()
{
}

void CreateForm::OnCancel(wxCommandEvent & event)
{
	Close(true);
}

void CreateForm::OnCreate(wxCommandEvent & event)
{
	auto currentValue = m_currentVolumeEntry->GetValue();
	auto minimumValue = m_minimumVolumeEntry->GetValue();
	auto maximumValue = m_maximumVolumeEntry->GetValue();

	double curV, minV, maxV;

	if (currentValue.empty() || 
		minimumValue.empty() || 
		maximumValue.empty())
	{
		wxMessageBox(wxT("Nenhum valor pode ser vazio"), wxT("Alerta!"), wxICON_WARNING);
		return;
	}

	if(!currentValue.ToDouble(&curV) ||
	   !minimumValue.ToDouble(&minV) || 
	   !maximumValue.ToDouble(&maxV))
	{
		wxMessageBox(wxT("Os valores dos campos devem ser numéricos"), wxT("Alerta!"), wxICON_WARNING);
		return;
	}

	if (maxV <= minV)
	{
		wxMessageBox(wxT("O volume máximo deve ser superior ao volume mínimo"), wxT("Alerta!"), wxICON_WARNING);
		return;
	}

	if (curV <= minV || curV >= maxV)
	{
		wxMessageBox(wxT("O volume inicial deve estar entre volume mínimo e volume máximo"), wxT("Alerta!"), wxICON_WARNING);
		return;
	}

	auto answer = wxMessageBox("Deseja criar este reservatório?", "Confirmar reservatório",
	                           wxYES_NO, this);
	if (wxYES == answer)
	{
		Reservoir reservoir{ curV, minV, maxV };
		ReservoirContainer reservoirContainer{};
		reservoirContainer.setReservoir(reservoir);

		MyFrame *frame = (MyFrame *)GetParent();
		frame->addReservoir(reservoirContainer);
		Close(true);
	}
}

BEGIN_EVENT_TABLE(CreateForm, wxFrame)
	EVT_BUTTON(ID_Create, CreateForm::OnCreate)
	EVT_BUTTON(wxID_EXIT, CreateForm::OnCancel)
END_EVENT_TABLE()