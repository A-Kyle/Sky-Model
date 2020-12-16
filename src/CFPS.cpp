#include "CFPS.h"

CFPS CFPS::FPSControl;

CFPS::CFPS()
{
	OldTime = 0;
	LastTime = 0;
	SpeedFactor = 0;
	Frames = 0;
	NumFrames = 0;
	TargetFPS = 32.0f;
}

void CFPS::OnLoop()
{
	// This statement checks if a second (1000 ms) has passed
	// since the last FPS tally. If a second has passed, we give
	// our frame-per-second counter (Frames) to NumFrames for
	// our use elsewhere. NumFrames is essentially our "FPS on
	// record", while Frames is a running total of frames passed
	// in the immediate 1000 ms.
	if (SDL_GetTicks() > OldTime + 1000)
	{
		OldTime = SDL_GetTicks();
		NumFrames = Frames;
		Frames = 0;
	}
	// The term in parentheses is our "seconds per loop"
	// term. I.e., how long it took for the last loop to complete
	// in seconds. We multiply that by a target FPS value.
	// Ideally, the first term will be 1/32 or less, meaning the
	// computer is running at a rate faster than our targeted FPS.
	SpeedFactor = ((SDL_GetTicks() - LastTime) / 1000.0f) * TargetFPS;

	// It's possible that with very bad performance, a glitch,
	// or "freezing" the program loop, the SpeedFactor will
	// be excessively high. This is because the time interval between
	// successive frames in such a case would be high, perhaps
	// exceeding 1000 ms (a full second, or 1 FPS). Anything greater,
	// and the physics (gravity in particular) begin to break. In the
	// unlikely event that FPS is 1 or less, we force the SpeedFactor
	// to a smaller number to prevent serious glitches in gameplay.
	// Glitches can involve entities translating through walls and floors.
	if (SpeedFactor > TargetFPS) SpeedFactor = TargetFPS;

	// We get a new "LastTime" to set up for calc'ing SF next
	// loop, and add one to our running total of frames in the
	// immmediate 1000 ms.
	LastTime = SDL_GetTicks();
	Frames++;
}

int CFPS::GetFPS()
{
	return NumFrames;
}

float CFPS::GetSpeedFactor()
{
	return SpeedFactor;
}

float CFPS::GetTargetFPS()
{
	return TargetFPS;
}
