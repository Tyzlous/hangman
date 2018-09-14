#include "Victory.h"



Victory::Victory()
{
}


Victory::~Victory()
{
}

void Victory::InitializeState()
{
	window = HWindow::GetWindow();
	gamestate = Gamestate::Get();
	UpdateChosenLanguage();
}