#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event)
{
	if (CInterrupt::isNone()) {
		CEvent::OnEvent(Event);
	}
	else {
		if (handleInterr(Event)) return;
	}
	CProfile::Control.OnEvent(Event);
}

bool CApp::handleInterr(SDL_Event* Event)
{
	return false;
}

// Handle key-press events
void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
	if (!CInterrupt::isNone()) return;

  switch (sym)
  {
    case SDLK_ESCAPE: OnExit(); break;
    default: break;
  }
}

// Handle left-click events
void CApp::OnLButtonDown(int mX, int mY)
{
	if (mX < 0 || mY < 0 || mX >= WWIDTH || mY >= WHEIGHT) {
		return;
	}
	const SDL_Point m = {mX, mY};
	// if (handleEngSwitch(&m)) return;
}

void CApp::OnRButtonDown(int mX, int mY)
{
	if (mX < 0 || mY < 0 || mX > WWIDTH || mY > WHEIGHT) return;
}
