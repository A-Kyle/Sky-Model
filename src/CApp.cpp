#include "CApp.h"

CApp::CApp()
{
	Running = true;
	Map_Display = NULL;
	mouseX = mouseY = 0;
	mouse.x = mouse.y = 0;

	intrpt = INTRPT_NONE;
}

/* This is the executable member that contains the editor's
* critical functions. Initialization, event handling, data manipulation,
* rendering, and house keeping are done within this member.
*/
int CApp::OnExecute()
{
	// If our initialization function fails, the program will end here.
	if (OnInit() == false) return -1;

	SDL_Event Event;
	// This loop will run endlessly until something makes the Running
	// flag false. That will happen, hopefully, by the user's decision.
	while (Running)
	{
		// Check for pending events; handle them
		while (SDL_PollEvent(&Event))	OnEvent(&Event);
		SDL_PumpEvents();
		OnLoop();      // Perform necessary manipulations
		OnRender();    // Render updated info
	}

	OnTerminate();       // Clean up the program before exiting
	return 0;
}

int main(int argc, char* argv[])
{
	CApp sim;
	return sim.OnExecute();
}
