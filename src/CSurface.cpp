#include "CSurface.h"

SDL_Renderer* CSurface::Win_Renderer = NULL;

CSurface::CSurface()
{
	//
}

bool CSurface::OnInit(SDL_Window* window)
{
	if ((Win_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		return false;
	}
	return true;
}

void CSurface::Clear()
{
	if (SDL_RenderClear(Win_Renderer) != 0) SDL_Delay(5000);
}

void CSurface::Present()
{
	SDL_RenderPresent(Win_Renderer);
}

void CSurface::OnCleanup()
{
	SDL_DestroyRenderer(Win_Renderer);
}

///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////

/* Loads an image using a specified renderer.
* param File     : character string of the file name
* param renderer : renderer in use
*/
SDL_Texture* CSurface::OnLoad(char const* File)
{
	// Initialize texture and surface pointers to null
	SDL_Texture* Surf_Text = NULL;
	SDL_Surface* Surf_Return = NULL;

	// Try loading image
	if ((Surf_Return = IMG_Load(File)) == NULL)	return NULL;

	// Load the image onto a SDL_Texture
	if ((Surf_Text = SDL_CreateTextureFromSurface(Win_Renderer, Surf_Return)) == 0)
	{
		return NULL;
	}

	// Get rid of our SDL_Surface
	SDL_FreeSurface(Surf_Return);
	return Surf_Text;
}

/* Draw a loaded texture onto a renderer.
* param Surf_Dest : a renderer; where the texture is drawn
* param Surf_Src : the texture used
* param X : horizontal position (Q-II) to draw texture
* param Y : vertical position (Q-II) to draw texture
*/
bool CSurface::OnDraw(SDL_Texture* Surf_Src, int X, int Y)
{
	if (Surf_Src == NULL) return false;

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;
	SDL_QueryTexture(Surf_Src, NULL, NULL, &DestR.w, &DestR.h);

	SDL_RenderCopy(Win_Renderer, Surf_Src, NULL, &DestR);
	return true;
}

bool CSurface::OnDraw(SDL_Texture* Surf_Src, int X, int Y, int Xo, int Yo, int W, int H)
{
	if (Surf_Src == NULL) return false;

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;
//	SDL_QueryTexture(Surf_Src, NULL, NULL, &DestR.w, &DestR.h);

	SDL_Rect SrcR;

	SrcR.x = Xo;
	SrcR.y = Yo;
	SrcR.w = W;
	SrcR.h = H;
	DestR.w = W;  // This will make the drawn image have the same
	DestR.h = H;  // resolution as the source image

	SDL_RenderCopy(Win_Renderer, Surf_Src, &SrcR, &DestR);
	return true;
}

bool CSurface::OnDraw(SDL_Texture* Surf_Src, int X, int Y, int Xo, int Yo, int Wo, int Ho, int W, int H)
{
	if (Surf_Src == NULL)
		return false;

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;
	DestR.w = W;
	DestR.h = H;

	SDL_Rect SrcR;

	SrcR.x = Xo;
	SrcR.y = Yo;
	SrcR.w = Wo;
	SrcR.h = Ho;

	SDL_RenderCopy(Win_Renderer, Surf_Src, &SrcR, &DestR);
	return true;
}

bool CSurface::OnDraw(SDL_Texture* Surf_Src, const SDL_Rect* srcrect, const SDL_Rect* dstrect)
{
	if (Surf_Src == NULL || srcrect == NULL || dstrect == NULL)
		return false;

	SDL_RenderCopy(Win_Renderer, Surf_Src, srcrect, dstrect);
	return true;
}

bool CSurface::OnDraw(SDL_Texture* Surf_Src, const SDL_Rect* srcrect, const SDL_Point* dstpos)
{
	if (Surf_Src == NULL || srcrect == NULL || dstpos == NULL)
		return false;

	SDL_Rect DestR = {dstpos->x, dstpos->y, srcrect->w, srcrect->h};

	SDL_RenderCopy(Win_Renderer, Surf_Src, srcrect, &DestR);
	return true;
}
