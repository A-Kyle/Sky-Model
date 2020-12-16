#include "CApp.h"

bool CApp::OnInit()
{
	if ((Map_Display = SDL_CreateWindow("Sky Color Model",
																			SDL_WINDOWPOS_CENTERED,
																			SDL_WINDOWPOS_CENTERED,
																			WWIDTH,
																			WHEIGHT,
																			SDL_WINDOW_SHOWN)) == NULL)
	{
		return false;
	}

	if (!CSurface::OnInit(Map_Display)) {
		return false;
	}

	if (!CAsset::OnInit()) {
		return false;
	}

	if (!Font::FontControl.OnInit()) {
		return false;
	}

	if (!CCore::Control.init()) {
		return false;
	}

	if (!CProfile::Control.init()) {
		return false;
	}

	///////////////////////
	// Debugging section //
	///////////////////////
	// long tmp_S = CCore::Control.getSolarFlux();
	// std::string msg = Font::intToStr(tmp_S);
	// std::string msg;
	// for (int i = 0; i < NUM_LAYERS; i++) {
	// 	int tmp_p = CCore::Control.getP(i);
	// 	msg += Font::intToStr(tmp_p);
	// 	if (i != NUM_LAYERS - 1) msg += "\n";
	// }
	// CInform::InfoControl.pushInform(msg.c_str());
  //
	// long double tmp_F = CCore::Control.getIntegratedFlux();
	// std::string msg = Font::intToStr(tmp_F);
	// CInform::InfoControl.pushInform(msg.c_str());

	return true;
}
