#pragma once
#include "MyFrame.h"

class Application : public wxApp
{
public:
	Application() = default;
	~Application();

	bool OnInit();
};

