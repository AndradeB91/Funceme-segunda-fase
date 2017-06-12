#include "MyFrame.h"

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	this->SetMinSize(size);
	this->SetMaxSize(size);

	wxMenu *menuOptions = new wxMenu;
	menuOptions->Append(ID_New,"&Novo reservatório\tCtrl-N");
	menuOptions->AppendSeparator();
	menuOptions->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(ID_About, "&Sobre");
	menuHelp->Append(ID_How, "&Funcionamento");

	wxMenuBar *menuBar = new wxMenuBar;
	menuBar->Append(menuOptions, "&Opções");
	menuBar->Append(menuHelp, "&Ajuda");
	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Bem vindo(a) ao SIGA"); 
	Centre();

	m_applicationGrid = new wxGridSizer(0, 2, 0, 0);

	m_reservoirDriver = new ReservoirDriver(this,
											wxT("Images/reservoir3.png"),
									        wxBITMAP_TYPE_PNG,
									        wxPoint(0, 0),
									        wxDefaultSize,
									        m_applicationGrid);		

}

MyFrame::~MyFrame()
{	
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("Aplicação SIGA versão 1.0",
		"Sobre", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}

void MyFrame::OnHow(wxCommandEvent& event)
{
	wxString help{};
	help << " Funcionamento do programa:\n\n"
		 << " - Clique em Opções -> Novo reservatório (Ctrl + n) para adicionar um reservatório.\n\n"
		 << " - Clique com o botão esquerdo do mouse em um reservatório criado\n"
		 << " para adicionar informações de faixas de liberação.\n\n"
		 << " - Clique com o botão direito do mouse em um reservatório para removê-lo.";

	wxMessageBox(help,
		"Ajuda", wxOK | wxICON_QUESTION);
}

void MyFrame::OnNew(wxCommandEvent& event) 
{
	CreateForm* createForm = new CreateForm(this);
	createForm->Show();
}

//To check reservoirs informations
void MyFrame::OnLeftClick(wxMouseEvent& event)
{
	LiberationLanesForm* liberationLanesForm = new LiberationLanesForm(this);
	liberationLanesForm->setReservoirDriver(m_reservoirDriver);
	liberationLanesForm->setReservoirId(event.GetId() - 1);
	liberationLanesForm->initForm();
	liberationLanesForm->Show();
}

//To remove reservoirs by clicking
void MyFrame::OnRightClick(wxMouseEvent& event)
{
	wxString msg{};
	auto id = event.GetId();

	msg << "Deseja remover o reservatório " << id << "?\n";
	auto answer = wxMessageBox(msg, "Remover reservatório", wxYES_NO, this);
	if (wxYES == answer)
	{
		m_reservoirDriver->removeReservoir(id - 1);
	}
}

void MyFrame::onMouseEnter(wxMouseEvent& event)
{
	wxString msg{};
	auto id = event.GetId();

	auto reservoirContainerVector = m_reservoirDriver->getReservoirContainerVector();
	auto reservoirContainer = reservoirContainerVector.at(id - 1);
	wxBitmapButton* reservoirBitmap = reservoirContainer.getReservoirBitmap();
	auto reservoir = reservoirContainer.getReservoir();

	msg << "ID Reservatório: " << id << "\n\n";
	msg << "Volume atual: " << reservoir.getCurrentVolume() << " (hm^3)\n";
	msg << "Volume mínimo: " << reservoir.getMinimumVolume() << " (hm^3)\n";
	msg << "Volume máximo: " << reservoir.getMaximumVolume() << " (hm^3)\n";

	wxToolTip * tooltip = new wxToolTip(msg);
	tooltip->Enable(true);
	tooltip->SetDelay(1);
	reservoirBitmap->SetToolTip(tooltip);
}

void MyFrame::addReservoir(ReservoirContainer reservoirContainer)
{
	wxBitmapButton* reservoirBitmap = m_reservoirDriver->addReservoir(reservoirContainer);

	reservoirBitmap->Connect(wxEVT_RIGHT_DOWN,
						     wxMouseEventHandler(MyFrame::OnRightClick),
							 NULL,
							 this);

	reservoirBitmap->Connect(wxEVT_LEFT_DOWN,
							 wxMouseEventHandler(MyFrame::OnLeftClick),
							 NULL,
							 this);

	reservoirBitmap->Connect(wxEVT_ENTER_WINDOW, 
							 wxMouseEventHandler(MyFrame::onMouseEnter),
							 NULL, 
							 this);
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_MENU(ID_Hello,  MyFrame::OnHello)
	EVT_MENU(wxID_EXIT, MyFrame::OnExit)
	EVT_MENU(ID_About,  MyFrame::OnAbout)
	EVT_MENU(ID_New,    MyFrame::OnNew)
	EVT_MENU(ID_How,	MyFrame::OnHow)
END_EVENT_TABLE()