#include "Application.h"

IMPLEMENT_APP(Application)

Application::~Application()
{
}

bool Application::OnInit() 
{
	wxInitAllImageHandlers();

	MyFrame *frame = new MyFrame("SIGA", wxPoint(50, 50), wxSize(816, 600));
	frame->SetBackgroundColour(wxColour(*wxLIGHT_GREY));
	frame->Show(true);
	return true;
}

