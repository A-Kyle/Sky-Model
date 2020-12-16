#include "CApp.h"

void CApp::OnRender()
{
	static const bool debug = true;

	CSurface::Clear();

	CProfile::Control.OnRender(&mouse);

	//	DEBUGGING
	if (debug)
	{
	}

	CInform::InfoControl.OnRender();
	CSurface::Present();
}
