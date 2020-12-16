#ifndef _C_INFORM_H_
#define _C_INFORM_H_

#include <string>
#include "CAsset.h"
#include "CFont.h"

class CInform {
public:
  static CInform InfoControl;

private:

  CInform();

  std::string info;
  SDL_Rect texBox;
  SDL_Rect frame;

private:
  int lastTime;
  int timeLeft;

public:
  void pushInform(const char* info);

  void OnLoop();

  bool OnRender();
};

#endif
