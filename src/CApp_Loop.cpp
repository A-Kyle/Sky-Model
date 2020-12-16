#include "CApp.h"

void CApp::OnLoop()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	mouse.x = mouseX;
	mouse.y = mouseY;

	CProfile::Control.OnLoop(&mouse);

	CInform::InfoControl.OnLoop();
	if (SDL_GetWindowFlags(Map_Display) & SDL_WINDOW_MINIMIZED)
	{
		SDL_RestoreWindow(Map_Display);
	}
	CFPS::FPSControl.OnLoop();
	return;
}
