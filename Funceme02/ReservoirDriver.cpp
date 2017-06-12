#include "ReservoirDriver.h"

ReservoirDriver::ReservoirDriver(
	wxWindow* window,
	const wxString path,
	wxBitmapType type,
	const wxPoint startingPoint,
	const wxSize size,
	wxSizer *sizer)
	:m_window(window), m_path(path), m_type(type), m_startingPoint(startingPoint), m_size(size), m_sizer(sizer)
{
}

ReservoirDriver::~ReservoirDriver()
{
}

wxBitmapButton* ReservoirDriver::addReservoir(ReservoirContainer reservoirContainer)
{
	wxBitmap image(m_path, m_type);

	int frameWidth, frameHeight;
	m_window->GetClientSize(&frameWidth, &frameHeight);

	if ((m_x + 1) * image.GetWidth() > frameWidth)
	{
		m_x = 0;
		m_y++;
	}

	auto* bitmap = new wxBitmapButton(m_window, 
									  ++m_id,
									  image,
									  wxPoint(m_startingPoint.x + m_x++*(image.GetWidth()),
											  m_startingPoint.y + m_y  *(image.GetHeight())),
									  m_size, 
								      wxBORDER_NONE);

	bitmap->SetBackgroundColour(wxColour(*wxLIGHT_GREY));

	reservoirContainer.setReservoirBitmap(bitmap);
	m_reservoirContainerVector.push_back(reservoirContainer);

	m_sizer->Add(bitmap, 0, wxALL, 5);
	m_window->SetSizer(m_sizer);

	return bitmap;
}

void ReservoirDriver::removeReservoir(int i)
{
	auto* reservoirContainer = &m_reservoirContainerVector[i];
	wxBitmapButton* bitmap = reservoirContainer->getReservoirBitmap();
	bitmap->Destroy();

	m_reservoirContainerVector.erase(m_reservoirContainerVector.begin() + i);

	for (auto k = i; k < m_reservoirContainerVector.size(); k++)
	{
		auto* bitmap = m_reservoirContainerVector[k].getReservoirBitmap();
		bitmap->SetId(bitmap->GetId() - 1);
	}
	m_id--;
}

void ReservoirDriver::updateGridReservoir(wxGrid* grid)
{
	grid->AppendRows(m_reservoirContainerVector.size());

	auto i = 0;
	for (auto e : m_reservoirContainerVector)
	{
		auto r = e.getReservoir();
		grid->SetCellValue(i, 0, wxString::Format(wxT("%d"), i+1));
		grid->SetCellValue(i, 1, wxString::Format(wxT("%f"), r.getCurrentVolume()));
		grid->SetCellValue(i, 2, wxString::Format(wxT("%f"), r.getMinimumVolume()));
		grid->SetCellValue(i, 3, wxString::Format(wxT("%f"), r.getMaximumVolume()));
		i++;
	}
}

std::vector<ReservoirContainer>& ReservoirDriver::getReservoirContainerVector()
{
	return m_reservoirContainerVector;
}

std::vector<ReservoirContainer>* ReservoirDriver::getPointerToReservoirContainerVector()
{
	return &m_reservoirContainerVector;
}
