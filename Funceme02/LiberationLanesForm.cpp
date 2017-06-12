#include "LiberationLanesForm.h"

LiberationLanesForm::LiberationLanesForm(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetSize(430, 300);
	this->SetMinSize(wxSize(430, 300));
	this->SetMaxSize(wxSize(430, 300));

	wxStaticBoxSizer* sbSizer;
	sbSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Zonas de Liberação")), wxVERTICAL);

	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap saveToTxt(wxT("Images/icons/save.png"), wxBITMAP_TYPE_PNG);
	wxBitmap loadFromTxt(wxT("Images/icons/load.png"), wxBITMAP_TYPE_PNG);
	wxBitmap writeToVector(wxT("Images/icons/write.png"), wxBITMAP_TYPE_PNG);
	wxBitmap eraseAll(wxT("Images/icons/erase.png"), wxBITMAP_TYPE_PNG);
	wxBitmap showAvailableWater(wxT("Images/icons/water.png"), wxBITMAP_TYPE_PNG);

	m_fileToolBar = new wxToolBar(sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
	m_save = m_fileToolBar->AddTool(wxID_ANY, wxT("save"), saveToTxt, wxT("Salvar informações em um .txt"));
	m_load = m_fileToolBar->AddTool(wxID_ANY, wxT("load"), loadFromTxt, wxT("Carregar informações de um .txt"));
	m_write = m_fileToolBar->AddTool(wxID_ANY, wxT("write"), writeToVector, wxT("Persistir informações"));
	m_erase = m_fileToolBar->AddTool(wxID_ANY, wxT("erase"), eraseAll, wxT("Apagar todas as informações"));
	m_water = m_fileToolBar->AddTool(wxID_ANY, wxT("erase"), showAvailableWater, wxT("Mostrar a quantidade de água disponível em cada faixa"));

	m_fileToolBar->Realize();
	sbSizer->Add(m_fileToolBar, 0, wxEXPAND, 5);

	wxBitmap addLine(wxT("Images/icons/plus.png"), wxBITMAP_TYPE_PNG);
	wxBitmap removeLine(wxT("Images/icons/minus.png"), wxBITMAP_TYPE_PNG);

	m_addRemoveToolBar = new wxToolBar(sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL);
	m_plus = m_addRemoveToolBar->AddTool(wxID_ANY, wxT("plus"), addLine, wxT("Adicionar uma zona de liberação"));
	m_minus = m_addRemoveToolBar->AddTool(wxID_ANY, wxT("minus"), removeLine, wxT("Remover a última zona de liberação"));
	m_addRemoveToolBar->Realize();
	sbSizer->Add(m_addRemoveToolBar, 0,  wxEXPAND, 5);

	sbSizer->Add(0, 0, 0, wxALL, 5);

	m_reservoirGrid = new wxGrid(sbSizer->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

	// Grid
	m_reservoirGrid->CreateGrid(1, 3);
	m_reservoirGrid->EnableEditing(true);
	m_reservoirGrid->EnableGridLines(true);
	m_reservoirGrid->EnableDragGridSize(false);
	m_reservoirGrid->SetMargins(0, 100);

	// Columns
	m_reservoirGrid->EnableDragColMove(false);
	m_reservoirGrid->EnableDragColSize(false);
	m_reservoirGrid->SetColLabelSize(30);
	m_reservoirGrid->SetColLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

	// Rows
	m_reservoirGrid->EnableDragColMove(false);
	m_reservoirGrid->EnableDragRowSize(true);
	m_reservoirGrid->SetRowLabelSize(80);
	m_reservoirGrid->SetRowLabelAlignment(wxALIGN_CENTRE, wxALIGN_CENTRE);

	// Label Appearance

	// Cell Defaults
	m_reservoirGrid->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
	sbSizer->Add(m_reservoirGrid, 0,  wxEXPAND, 5);

	m_reservoirGrid->SetColSize(0, 100);
	m_reservoirGrid->SetColSize(1, 100);
	m_reservoirGrid->SetColSize(2, 100);
	m_reservoirGrid->SetColLabelValue(0, "Limite\nInferior (hm³)");
	m_reservoirGrid->SetColLabelValue(1, "Limite\nSuperior (hm³)");
	m_reservoirGrid->SetColLabelValue(2, "Prioridade");
	m_reservoirGrid->SetColFormatNumber(2);

	this->SetSizer(sbSizer);
	this->Layout();
	this->SetBackgroundColour(wxColour(*wxWHITE));
	this->Centre(wxBOTH);

	//m_reservoirGrid->Connect(wxEVT_GRID_CELL_CHANGING, 
		//					 wxGridEventHandler(LiberationLanesForm::gridOnChange));

	this->Connect(m_reservoirGrid->GetId(),
				  wxEVT_GRID_CELL_CHANGED,
				  wxGridEventHandler(LiberationLanesForm::gridOnChange));
	
	this->Connect(m_plus->GetId(), 
				  wxEVT_COMMAND_TOOL_CLICKED, 
				  wxCommandEventHandler(LiberationLanesForm::plusOnClick));

	this->Connect(m_minus->GetId(),
				  wxEVT_COMMAND_TOOL_CLICKED,
				  wxCommandEventHandler(LiberationLanesForm::minusOnClick));

	this->Connect(m_erase->GetId(),
				  wxEVT_COMMAND_TOOL_CLICKED,
				  wxCommandEventHandler(LiberationLanesForm::eraseOnClick));

	this->Connect(m_write->GetId(),
				  wxEVT_COMMAND_TOOL_CLICKED,
				  wxCommandEventHandler(LiberationLanesForm::writeOnClick));

	this->Connect(m_save->GetId(),
				  wxEVT_COMMAND_TOOL_CLICKED,
				  wxCommandEventHandler(LiberationLanesForm::saveOnClick));

	this->Connect(m_load->GetId(),
				  wxEVT_COMMAND_TOOL_CLICKED,
				  wxCommandEventHandler(LiberationLanesForm::loadOnClick));

	this->Connect(m_water->GetId(),
				  wxEVT_COMMAND_TOOL_CLICKED,
				  wxCommandEventHandler(LiberationLanesForm::showAvailableWaterOnClick));


}

void LiberationLanesForm::resetGrid()
{
	auto reservoirContainerVector = m_reservoirDriver->getReservoirContainerVector();
	auto reservoirContainer = reservoirContainerVector[m_reservoirId];
	auto liberationLaneVector = reservoirContainer.getLiberationLaneVector();

	m_reservoirGrid->DeleteRows(0, m_reservoirGrid->GetNumberRows());
	m_reservoirGrid->AppendRows(1);

	auto reservoir = reservoirContainer.getReservoir();
	auto value = reservoir.getMinimumVolume();
	m_reservoirGrid->SetReadOnly(0, 0);
	m_reservoirGrid->SetCellValue(0, 0, wxString::Format(wxT("%.3f"), value));
}

void LiberationLanesForm::plusOnClick(wxCommandEvent& event)
{
	auto stringUpperValue = m_reservoirGrid->GetCellValue(m_reservoirGrid->GetNumberRows() - 1, 1);
	auto priorityString = m_reservoirGrid->GetCellValue(m_reservoirGrid->GetNumberRows() - 1, 2);

	if (stringUpperValue.empty() || priorityString.empty())
	{
		wxMessageBox(wxT("Há campos vazios!"), wxT("Alerta!"), wxICON_WARNING);
		return;
	}

	double upperValue;
	stringUpperValue.ToDouble(&upperValue);
	int priority = wxAtoi(priorityString);

	m_reservoirGrid->AppendRows(1);
	m_reservoirGrid->SetReadOnly(m_reservoirGrid->GetNumberRows() - 1, 0);
	m_reservoirGrid->SetCellValue(m_reservoirGrid->GetNumberRows() - 1, 0,
								  wxString::Format(wxT("%.3f"), upperValue));
	m_reservoirGrid->SetCellAlignment(m_reservoirGrid->GetNumberRows() - 1, 2, 
									wxALIGN_LEFT, wxALIGN_CENTRE);

}

void LiberationLanesForm::minusOnClick(wxCommandEvent& event)
{
	if (m_reservoirGrid->GetNumberRows() > 1)
	{
		m_reservoirGrid->DeleteRows(m_reservoirGrid->GetNumberRows()-1);
	}

}

void LiberationLanesForm::eraseOnClick(wxCommandEvent& event)
{
	if (m_reservoirGrid->GetNumberRows() > 1)
	{
		resetGrid();
	}
}

void LiberationLanesForm::writeOnClick(wxCommandEvent& event)
{
	auto reservoirContainerVector = m_reservoirDriver->getPointerToReservoirContainerVector();
	auto reservoirContainer = &reservoirContainerVector->at(m_reservoirId);
	auto liberationLaneVector = reservoirContainer->getPointerToLiberationLaneVector();
	liberationLaneVector->clear();

	for (auto i = 0; i < m_reservoirGrid->GetNumberRows(); i++)
	{
		auto stringUpperValue = m_reservoirGrid->GetCellValue(i, 1);
		auto priorityString = m_reservoirGrid->GetCellValue(i, 2);

		if (stringUpperValue.IsEmpty() || priorityString.IsEmpty())
		{
			wxMessageBox(wxT("Grade está incompleta. Não foi possível persistir os dados!"),
					     wxT("Alerta!"), wxICON_WARNING);
			return;
		}
	}

	for (auto i = 0; i < m_reservoirGrid->GetNumberRows(); i++)
	{
		auto stringUpperValue = m_reservoirGrid->GetCellValue(i, 1);
		auto priorityString = m_reservoirGrid->GetCellValue(i, 2);

		double upperValue;
		stringUpperValue.ToDouble(&upperValue);
		int priority = wxAtoi(priorityString);

		LiberationLane liberationLane(priority, upperValue);
		liberationLaneVector->push_back(liberationLane);
	}

	wxString msg{};
	msg << "Dados persistidos no reservatório " << m_reservoirId + 1<< " com sucesso!";
	wxMessageBox(msg, wxT("Sucesso!"), wxICON_INFORMATION);
}

void LiberationLanesForm::saveOnClick(wxCommandEvent& event)
{
	auto answer = wxMessageBox("Deseja salvar reservatório?", "Salvar reservatório",
		wxYES_NO, this);
	if (wxNO == answer)
	{
		return;
	}

	std::string path = "SavedFiles/";
	std::ofstream file;
	std::string fileName = "reservoir_";
	wxString idString = wxString::Format(wxT("%i"), m_reservoirId + 1);
	fileName += idString;
	path += fileName;
	file.open(path);

	if (!file.is_open())
	{
		wxMessageBox("Não foi possível salvar o arquivo",
					 wxT("Alerta!"), wxICON_WARNING);
		return;
	}

	for (auto i = 0; i < m_reservoirGrid->GetNumberRows(); i++)
	{
		auto stringInferiorValue = m_reservoirGrid->GetCellValue(i, 0);
		auto stringUpperValue    = m_reservoirGrid->GetCellValue(i, 1);
		auto priorityString      = m_reservoirGrid->GetCellValue(i, 2);

		file << stringInferiorValue << " " << stringUpperValue << " " << priorityString << '\n';
	}
	file.close();

	wxString msg = "Arquivo " + fileName + " salvo com sucesso!";
	wxMessageBox(msg, wxT("Alerta!"), wxICON_INFORMATION);
}

void LiberationLanesForm::loadOnClick(wxCommandEvent& event)
{
	wxFileDialog * openFileDialog = new wxFileDialog(this);
	openFileDialog->Center();
	wxString fileName;

	if (openFileDialog->ShowModal() == wxID_OK) {
		 fileName = openFileDialog->GetPath();
	}

	std::string path = fileName.ToStdString();
	std::ifstream file(path);

	if (!file.is_open())
	{
		wxMessageBox("Não foi possível carregar o arquivo",
					 wxT("Alerta!"), wxICON_WARNING);
		return;
	}

	std::string inferior, upper, priority;
	std::string line;
	auto i = 0;

	auto reservoirContainerVector = m_reservoirDriver->getPointerToReservoirContainerVector();
	auto reservoirContainer = &reservoirContainerVector->at(m_reservoirId);
	auto reservoir = reservoirContainer->getReservoir();
	auto minValue = reservoir.getMinimumVolume();

	auto firstLine = true;

	while (getline(file, line))
	{
		std::stringstream ss(line);
		ss >> inferior;
		ss >> upper;
		ss >> priority;

		if (firstLine)
		{
			double value = stod(inferior);

			if (minValue != value)
			{
				wxMessageBox("Limite inferior da primeira faixa de liberação é diferente do volume mínimo",
					wxT("Alerta!"), wxICON_WARNING);
				return;
			}
			
			//If the file can be loaded we clear the grid firstly
			m_reservoirGrid->DeleteRows(0, m_reservoirGrid->GetNumberRows());
			firstLine = false;
		}

		m_reservoirGrid->AppendRows(1);
		m_reservoirGrid->SetReadOnly(i, 0);
		m_reservoirGrid->SetCellAlignment(i, 2, wxALIGN_LEFT, wxALIGN_CENTRE);

		m_reservoirGrid->SetCellValue(i  , 0, inferior);
		m_reservoirGrid->SetCellValue(i  , 1, upper);
		m_reservoirGrid->SetCellValue(i++, 2, priority);
	}

	wxMessageBox(wxT("Arquivo carregado com sucesso!"),
		wxT("Sucesso!"), wxICON_INFORMATION);
}

void LiberationLanesForm::showAvailableWaterOnClick(wxCommandEvent& event)
{
	auto reservoirContainerVector = m_reservoirDriver->getPointerToReservoirContainerVector();
	auto reservoirContainer = &reservoirContainerVector->at(m_reservoirId);
	auto reservoir = reservoirContainer->getReservoir();

	auto minimumVolume = reservoir.getMinimumVolume();
	auto maximumVolume = reservoir.getMaximumVolume();
	auto currentVolume = reservoir.getCurrentVolume();

	std::vector<int> pArray;
	std::vector<double> vArray;

	for (auto i = 0; i < m_reservoirGrid->GetNumberRows(); i++)
	{
		if (!m_reservoirGrid->GetCellValue(i, 1).IsEmpty() &&
			!m_reservoirGrid->GetCellValue(i, 2).IsEmpty())
		{
			auto supLim = m_reservoirGrid->GetCellValue(i, 1);
			auto priority = m_reservoirGrid->GetCellValue(i, 2);

			auto priorityValue = wxAtoi(priority);
			double supLimValue;
			supLim.ToDouble(&supLimValue);

			pArray.push_back(priorityValue);
			vArray.push_back(supLimValue);
		}
	}

	if (pArray.empty() || vArray.empty())
	{
		wxMessageBox(wxT("Preencha pelo menos uma linha da grade!"), wxT("Alerta!"), wxICON_INFORMATION);
		return;
	}

	PriorityUtils pUtil{};
	VectorOfPriorityZones vectorOfPriorityZones;
	vectorOfPriorityZones = pUtil.zonesAvailableSupply(pArray,
													   vArray,
													   minimumVolume,
													   maximumVolume,
													   currentVolume);
	
	wxString msg{};
	for (auto v : vectorOfPriorityZones)
	{
		msg << "Prioridade " << v.getPriority()
			<< ": " << v.getAvailableVolume() << " hm³ de água disponível\n";
	}

	wxMessageBox(msg, wxT("Volume de água disponível"), wxICON_INFORMATION);

}

void LiberationLanesForm::gridOnChange(wxGridEvent& event)
{
	auto row = event.GetRow();
	auto col = event.GetCol();

	//Handling superior limit errors
	if (1 == col)
	{
		auto supLim = m_reservoirGrid->GetCellValue(row, col);
		double supLimValue;
		supLim.ToDouble(&supLimValue);

		auto infLim = m_reservoirGrid->GetCellValue(row, col - 1);
		double infLimValue;
		infLim.ToDouble(&infLimValue);

		if (supLimValue <= infLimValue)
		{
			wxMessageBox("Limite superior não pode ser menor ou igual ao limite inferior.",
						 wxT("Alerta!"), wxICON_WARNING);
			m_reservoirGrid->SetCellValue(row, col, wxT(""));
			return;
		}
	}

	//Handling priority errors
	if (2 == col && row > 0)
	{
		auto priority = m_reservoirGrid->GetCellValue(row, col);
		auto pValue = wxAtoi(priority);

		auto priorityRowBefore = m_reservoirGrid->GetCellValue(row - 1, col);
		auto pValueRowBefore = wxAtoi(priorityRowBefore);

		if (pValue <= pValueRowBefore)
		{
			wxMessageBox("Prioridade não pode ser menor ou igual a prioridade da linha anterior.",
						 wxT("Alerta!"), wxICON_WARNING);
			m_reservoirGrid->SetCellValue(row, col, wxT(""));
			return;
		}
	}
	
}

void LiberationLanesForm::setReservoirDriver(ReservoirDriver* reservoirDriver)
{
	m_reservoirDriver = reservoirDriver;
}

void LiberationLanesForm::setReservoirId(int reservoirId)
{
	m_reservoirId = reservoirId;
}

void LiberationLanesForm::initForm()
{
	auto reservoirContainerVector = m_reservoirDriver->getPointerToReservoirContainerVector();
	auto reservoirContainer = &reservoirContainerVector->at(m_reservoirId);
	auto liberationLaneVector = reservoirContainer->getPointerToLiberationLaneVector();

	if (liberationLaneVector->empty())
	{
		auto reservoir = reservoirContainer->getReservoir();
		auto value = reservoir.getMinimumVolume();
		m_reservoirGrid->SetReadOnly(0, 0);
		m_reservoirGrid->SetCellValue(0, 0, wxString::Format(wxT("%.3f"), value));
		m_reservoirGrid->SetCellAlignment(0, 2, wxALIGN_LEFT, wxALIGN_CENTRE);

	}
	else
	{
		m_reservoirGrid->AppendRows(liberationLaneVector->size()-1);

		for (auto i = 0; i < liberationLaneVector->size(); i++)
		{

			double inferiorValue;
			if (0 == i)
			{
				inferiorValue = reservoirContainer->getReservoir().getMinimumVolume();
			}
			else
			{
				inferiorValue = liberationLaneVector->at(i - 1).getUpperLimit();
			}

			LiberationLane* ll = &liberationLaneVector->at(i);

			m_reservoirGrid->SetReadOnly(i, 0);
		
			m_reservoirGrid->SetCellValue(i, 0, wxString::Format(wxT("%.3f"), inferiorValue));
			m_reservoirGrid->SetCellValue(i, 1, wxString::Format(wxT("%.3f"), ll->getUpperLimit()));
			m_reservoirGrid->SetCellValue(i, 2, wxString::Format(wxT("%d"), ll->getPriority()));
			m_reservoirGrid->SetCellAlignment(i, 2, wxALIGN_LEFT, wxALIGN_CENTRE);

		}
	}
}

LiberationLanesForm::~LiberationLanesForm()
{
}
