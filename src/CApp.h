#ifndef _C_APP_H_
#define _C_APP_H_

#include <SDL.h>
#include <vector>

#include "CInterrupt.h"
#include "CSurface.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CFont.h"
#include "CInform.h"
#include "CCore.h"
#include "CProfile.h"
#include "Define.h"

class CApp : public CEvent {
private:
	SDL_Window* Map_Display;    // Window

	bool Running;

  SDL_Point mouse;
	int mouseX;
	int mouseY;

public:
	int intrpt;

public:
	CApp();

	int OnExecute();

	void OnEvent(SDL_Event* Event);
  bool handleInterr(SDL_Event* Event);

	bool OnInit();

	void OnExit();

	// Handles looping calculations
	void OnLoop();

	// Renders graphics
	void OnRender();

	// Destroys all windows, textures, surfaces, renderers...
	void OnTerminate();

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	void OnLButtonDown(int mX, int mY);

	void OnRButtonDown(int mX, int mY);
};

#endif
