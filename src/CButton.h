#ifndef _C_BUTTON_H_
#define _C_BUTTON_H_

#include "CAsset.h"
#include "CSurface.h"

namespace button_defaults {
  extern const short bsiz;
  extern const SDL_Point* defCol;
  extern const SDL_Point* hovCol;
  extern const SDL_Point* onCol;
}

class CButton {
public:
  CButton();
  CButton(const int& x, const int& y, const unsigned int& w, const unsigned int& h);
  CButton(const SDL_Rect& dstR);
  CButton(const SDL_Rect& dstR, const SDL_Point* defCol, const SDL_Point* onCol);
  CButton(const SDL_Rect& dstR, const SDL_Point* defCol, const SDL_Point* hovCol, const SDL_Point* onCol);

  bool OnRender(const SDL_Point* m, const bool& useHov, const bool& on);
  bool OnRender(const SDL_Point* m, const bool& useHov);
  bool OnRender(const SDL_Point* m);
  bool OnRender(const bool& on);

public:
  SDL_Rect dstR;
  short bsiz;
  const SDL_Point* defCol;
  const SDL_Point* hovCol;
  const SDL_Point* onCol;
};

#endif
