#ifndef _C_METER_H_
#define _C_METER_H_

#include "CAsset.h"
#include "CFont.h"
#include "CSurface.h"

namespace meter_defaults {
  extern const short lab_y_offset;
  extern const short bsiz;
  extern const SDL_Point* fillCol;
  extern const SDL_Point* emptyCol;
}

class CMeter {
public:
  CMeter();
  CMeter(const int& x, const int& y, const unsigned int& w, const unsigned int& h);
  CMeter(const SDL_Rect& dstR);

private:
  void setDefaults();

public:
  bool clickPos(const SDL_Point* m, double& fraction);

  bool OnRender(const double& fractFill, const char* label);
  bool OnRender(const double& fractFill);

public:
  short lab_y_offset;

  SDL_Rect dstR;
  short bsiz;
  const SDL_Point* fillCol;
  const SDL_Point* emptyCol;
};

#endif
