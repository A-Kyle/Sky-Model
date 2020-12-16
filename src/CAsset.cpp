#include "CAsset.h"

SDL_Texture* CAsset::paltex = NULL;
SDL_Texture* CAsset::arrtex = NULL;
SDL_Texture* CAsset::boxtex = NULL;

namespace symbols
{
  // arrow fills
  const SDL_Rect f_AL = {15, 15, 15, 15};
  const SDL_Rect f_AR = {0,  15, 15, 15};
  const SDL_Rect f_AU = {15, 0,  15, 15};
  const SDL_Rect f_AD = {0,  0,  15, 15};
  // arrow strokes
  const SDL_Rect s_AL = {45, 15, 15, 15};
  const SDL_Rect s_AR = {30, 15, 15, 15};
  const SDL_Rect s_AU = {45, 0,  15, 15};
  const SDL_Rect s_AD = {30, 0,  15, 15};
}

CAsset::CAsset()
{
  //
}

bool CAsset::OnInit()
{
  if ((paltex = CSurface::OnLoad("../res/palette.png")) == NULL)
	{
		return false;
	}
  if ((arrtex = CSurface::OnLoad("../res/arrow.png")) == NULL)
	{
		return false;
	}
  if ((boxtex = CSurface::OnLoad("../res/boxtex.png")) == NULL)
  {
    return false;
  }
  SDL_SetTextureBlendMode(paltex, SDL_BLENDMODE_BLEND);
	return true;
}


void CAsset::paletteAlpha(const short& a)
{
  if (a >= 0 && a <= MAX_RGBA) {
    SDL_SetTextureAlphaMod(paltex, a);
  }
}

SDL_Rect CAsset::getRect(unsigned int X, unsigned int Y, unsigned int W, unsigned int H)
{
	SDL_Rect rect;
	rect.x = X;
	rect.y = Y;
	rect.w = W;
	rect.h = H;
	return rect;
}

SDL_Rect CAsset::getRect(const SDL_Point* A, const SDL_Point* B)
{
  int xmin = (A->x <  B->x) ? A->x : B->x;
  int xmax = (A->x >= B->x) ? A->x : B->x;
  int ymin = (A->y <  B->y) ? A->y : B->y;
  int ymax = (A->y >= B->y) ? A->y : B->y;
  int w = xmax - xmin + 1;
  int h = ymax - ymin + 1;

  SDL_Rect rect = {xmin, ymin, w, h};
  return rect;
}

SDL_Rect CAsset::getWinCentRect(const unsigned int& w, const unsigned int& h) {
  int X = (WWIDTH - w) / 2;
  int Y = (WHEIGHT - h) / 2;
  if (X < 0 || Y < 0) {
    return CAsset::getRect(0,0,0,0);
  }
  return CAsset::getRect(X, Y, w, h);
}

SDL_Point CAsset::getPos(int X, int Y)
{
  SDL_Point pos;
  pos.x = X;
  pos.y = Y;
  return pos;
}

SDL_Rect CAsset::getPixel(const SDL_Point* pix)
{
	SDL_Rect rect;

	rect.x = pix->x;
	rect.y = pix->y;
	rect.w = 1;
	rect.h = 1;

	return rect;
}

bool CAsset::inWorkspace(const SDL_Point* pos)
{
  return (pos->x >= 0 && pos->x < WWIDTH && pos->y >= 0 && pos->y < WHEIGHT);
}

bool CAsset::inWorkspace(const int& x, const int& y)
{
  return (x >= 0 && x < WWIDTH && y >= 0 && y < WHEIGHT);
}

bool CAsset::compRect(const SDL_Rect& A, const SDL_Rect& B) {
  return (A.x == B.x && A.y == B.y && A.w == B.w && A.h == B.h);
}

bool CAsset::drawLine(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color, const int& thick)
{
  return true;
}

bool CAsset::drawBox(const SDL_Rect* box, const SDL_Point* color)
{
  const int defThick = 1;
  return drawBox(box, color, defThick);
}

bool CAsset::drawBox(const SDL_Rect* box, const SDL_Point* color, const int& thick)
{
  if (box == NULL || color == NULL || thick < 0) return false;
  if (thick == 0) return true;

  SDL_Rect srcR = getPixel(color);
  SDL_Rect dstR;

  // top side
  dstR = getRect(box->x, box->y, box->w, thick);
  CSurface::OnDraw(paltex, &srcR, &dstR);

  // bottom side
  dstR = getRect(box->x, box->y + box->h - thick, box->w, thick);
  CSurface::OnDraw(paltex, &srcR, &dstR);

  // left side
  dstR = getRect(box->x, box->y, thick, box->h);
  CSurface::OnDraw(paltex, &srcR, &dstR);

  // right side
  dstR = getRect(box->x + box->w - thick, box->y, thick, box->h);
  CSurface::OnDraw(paltex, &srcR, &dstR);

  return true;
}

bool CAsset::drawBox(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color, const int& thick)
{
  SDL_Rect box = getRect(A, B);
  return drawBox(&box, color, thick);
}

bool CAsset::drawBoxFill(const SDL_Rect* box, const SDL_Point* color)
{
  if (box == NULL || color == NULL) return false;

  SDL_Rect srcR = getPixel(color);
  if (!CSurface::OnDraw(paltex, &srcR, box)) return false;

  return true;
}

bool CAsset::drawBoxFill(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color)
{
  SDL_Rect dstR = getRect(A, B);
  return drawBoxFill(&dstR, color);
}

bool CAsset::drawBoxFill(const SDL_Rect* box, const SDL_Color* rgb) {
  bool retval = false;

  static SDL_Rect srcR = {0,0,1,1};

  SDL_SetTextureColorMod(boxtex, rgb->r, rgb->g, rgb->b);

  return CSurface::OnDraw(boxtex, &srcR, box);
}

bool CAsset::drawStrBox(const SDL_Rect* box, const int& str_w, const SDL_Point* color)
{
  if (!drawBoxFill(box, color)) return false;
  if (!drawBox(box, &palette::black, str_w)) return false;

  return true;
}

bool CAsset::drawStrBox(const SDL_Rect* box, const int& str_w, const SDL_Point* color, const SDL_Point* str_col)
{
  if (!drawBoxFill(box, color)) return false;
  if (!drawBox(box, str_col, str_w)) return false;

  return true;
}

bool CAsset::drawArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb)
{
  using namespace symbols;

  bool retval = false;

  SDL_SetTextureColorMod(arrtex, rgb->r, rgb->g, rgb->b);

  switch (dir)
  {
    case 'L': retval = CSurface::OnDraw(arrtex, &s_AL, dstR); break;
    case 'R': retval = CSurface::OnDraw(arrtex, &s_AR, dstR); break;
    case 'U': retval = CSurface::OnDraw(arrtex, &s_AU, dstR); break;
    case 'D': retval = CSurface::OnDraw(arrtex, &s_AD, dstR); break;
    default: break;
  }

  return retval;
}

bool CAsset::drawArrowFill(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb)
{
  using namespace symbols;

  bool retval = false;

  SDL_SetTextureColorMod(arrtex, rgb->r, rgb->g, rgb->b);

  switch (dir)
  {
    case 'L': retval = CSurface::OnDraw(arrtex, &f_AL, dstR); break;
    case 'R': retval = CSurface::OnDraw(arrtex, &f_AR, dstR); break;
    case 'U': retval = CSurface::OnDraw(arrtex, &f_AU, dstR); break;
    case 'D': retval = CSurface::OnDraw(arrtex, &f_AD, dstR); break;
    default: break;
  }

  return retval;
}

bool CAsset::drawStrArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb)
{
  if (!drawArrowFill(dstR, dir, rgb))       return false;
  if (!drawArrow(dstR, dir, &rgb::black))   return false;

  return true;
}

bool CAsset::drawStrArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb, const SDL_Color* str_rgb)
{
  if (!drawArrowFill(dstR, dir, rgb))   return false;
  if (!drawArrow(dstR, dir, str_rgb))   return false;

  return true;
}

bool CAsset::drawArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, 15, 15};
  return drawArrow(&dstR, dir, rgb);
}

bool CAsset::drawArrowFill(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, 15, 15};
  return drawArrowFill(&dstR, dir, rgb);
}

bool CAsset::drawStrArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, 15, 15};
  return drawStrArrow(&dstR, dir, rgb);
}

bool CAsset::drawStrArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb, const SDL_Color* str_rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, 15, 15};
  return drawStrArrow(&dstR, dir, rgb, str_rgb);
}

bool CAsset::isInt(const char& c) {
  bool retval = false;
  switch (c) {
    case '0': retval = true; break;
    case '1': retval = true; break;
    case '2': retval = true; break;
    case '3': retval = true; break;
    case '4': retval = true; break;
    case '5': retval = true; break;
    case '6': retval = true; break;
    case '7': retval = true; break;
    case '8': retval = true; break;
    case '9': retval = true; break;
    default:  break;
  }
  return retval;
}

int CAsset::charToInt(const char& c) {
  int retval = -1;
  switch (c) {
    case '0': retval = 0; break;
    case '1': retval = 1; break;
    case '2': retval = 2; break;
    case '3': retval = 3; break;
    case '4': retval = 4; break;
    case '5': retval = 5; break;
    case '6': retval = 6; break;
    case '7': retval = 7; break;
    case '8': retval = 8; break;
    case '9': retval = 9; break;
    default:  break;
  }
  return retval;
}

double CAsset::strToDouble(const std::string& str) {
  if (str.empty()) return 0.0;

  double val = 0.0;

  bool neg = (str[0] == '-');
  bool isNum = false;
  bool frac = false;
  int int_digits = 0;
  int i = neg;    // start at index 1 (true) if there's a leading minus sign
  // how many integer digits are there in the string? (int_digits)
  // does the string represent a floating point value? (frac)
  while (i < str.size()) {
    if (str[i] == '.') {
      if (!frac) frac = true;
      else return val;    // invalid string (more than 1 decimal point)
    }
    else if (!isInt(str[i])) return 0.0;  // invalid string (non-numeric characters)
    else {
      if (!isNum) isNum = true;
      if (!frac) int_digits++;
    }
    i++;
  }
  if (!isNum) return 0.0;

  i = neg;
  while (int_digits) {
    int O = 1;
    for (int j = 1; j < int_digits; j++) O *= 10;
    val += (O * charToInt(str[i]));
    i++;
    int_digits--;
  }
  if (frac) {
    i++;
    int O = 1;
    while (i < str.size()) {
      O *= 10;
      val += (double)(charToInt(str[i])) / O;
      i++;
    }
  }
  return neg ? -val : val;
}

void CAsset::OnCleanup() {
  SDL_DestroyTexture(paltex);
  SDL_DestroyTexture(arrtex);
}
