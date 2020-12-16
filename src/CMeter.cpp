#include "CMeter.h"

namespace meter_defaults {
  const short lab_y_offset  = -10;
  const short bsiz          = 1;
  const SDL_Point* fillCol  = &palette::light_green;
  const SDL_Point* emptyCol = &palette::black;
}

CMeter::CMeter() {
  dstR.x = dstR.y = dstR.w = dstR.h = 0;
  setDefaults();
}

CMeter::CMeter(const int& x, const int& y, const unsigned int& w, const unsigned int& h) {
  dstR.x = x;
  dstR.y = y;
  dstR.w = w;
  dstR.h = h;
  setDefaults();
}

CMeter::CMeter(const SDL_Rect& dstR) {
  this->dstR = dstR;
  setDefaults();
}

void CMeter::setDefaults() {
  lab_y_offset  = meter_defaults::lab_y_offset;
  bsiz          = meter_defaults::bsiz;
  fillCol       = meter_defaults::fillCol;
  emptyCol      = meter_defaults::emptyCol;
}

bool CMeter::clickPos(const SDL_Point* m, double& fraction) {
  if (m == NULL || !SDL_PointInRect(m, &dstR)) return false;

  int xRel = m->x - (dstR.x + bsiz);  // x position on bar fill (0 is first pixel)
  if (xRel < 0) {
    fraction = 0.0;
    return true;
  }

  int fill_w = dstR.w - (bsiz * 2);
  if (fill_w <= 0) return false;

  fraction = (double)(xRel + 1) / (double)(fill_w);
  return true;
}

bool CMeter::OnRender(const double& fractFill, const char* label) {
  if (!OnRender(fractFill)) return false;

  const SDL_Point labelPos = {dstR.x + (dstR.w / 2), dstR.y + lab_y_offset};
  Font::NewCenterWrite(label, &labelPos);

  return true;
}

bool CMeter::OnRender(const double& fractFill) {
  if (fractFill < 0.0) return false;

  int fill_w = (dstR.w - (bsiz * 2)) * fractFill;
  if (fill_w < 0) return false;

  SDL_Rect fill = {dstR.x + bsiz, dstR.y, fill_w, dstR.h};

  CAsset::drawBoxFill(&dstR, emptyCol);
  CAsset::drawBoxFill(&fill, fillCol);
  CAsset::drawBox(&dstR, emptyCol);

  return true;
}
