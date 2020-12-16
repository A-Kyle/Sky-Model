#ifndef _C_PROFILE_H_
#define _C_PROFILE_H_

#include <vector>
#include <string>
#include "CColor.h"
#include "CCore.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CInform.h"
#include "CSurface.h"
#include "CFont.h"
#include "Define.h"

enum {
  T_PROF = 0,
  V_N_PROF,
  V_O_PROF,
  V_AR_PROF,
};

namespace Interface {
  extern const short w_page;
  namespace Sounding {
    extern const short w;
    extern const short h;
    extern const short h_lo;
    extern const short h_hi;
    extern const short x_page;
    extern const short x_profile;
    extern const short y_profile;
    extern const SDL_Rect r_profile;
    extern const short w_but;
    extern const short h_but;
    extern const SDL_Rect T_button;
    extern const SDL_Rect v_N_button;
    extern const SDL_Rect v_O_button;
    extern const SDL_Rect v_Ar_button;
    extern const SDL_Point* off_col;
    extern const SDL_Point* on_col;
    extern const SDL_Point* hov_col;
    extern const short title_y;
    extern const short title_x;
    extern const short axis_y;
    extern const short axis_x_l;
    extern const short axis_x_r;
    extern const short b_sz;
    extern const short min_v;
    extern const short max_v;
    extern const short min_T;
    extern const short max_T;
  }
  namespace Options {
    extern const short num_fields;
    extern const short sect_h;
    extern const short w;
    extern const short h;
    extern const short x_page;
    extern const short x_field;
    extern const char* const c_star_T;
    extern const char* const c_star_D;
    extern const char* const c_star_R;
    extern const char* const c_sfc_P;
    extern const char* const c_calc;
    extern const char* const c_reset;
    // const char* const c_sfc_T   = "Surface Temperature $LK$R";
    extern const SDL_Point* label_col;
    extern const SDL_Point* field_col;
    extern const SDL_Point* calc_col;
    extern const SDL_Point* reset_col;
    extern const short b_sz;
    extern const char* const labels[];
    extern const SDL_Rect fields[];
    extern const SDL_Rect r_calc;
    extern const SDL_Rect r_reset;
  }
  namespace SkyColor {
    extern const short w;
    extern const short h;
    extern const short h_lo;
    extern const short h_hi;
    extern const short x_page;
    extern const short x_profile;
    extern const short y_profile;
    extern const char* const title;
    extern const short title_y;
    extern const char* const axis;
    extern const short axis_x;
    extern const char* const mark_sfc;
    extern const char* const mark_half;
    extern const char* const mark_top;
    extern const short mark_x;
    extern const SDL_Rect column[];
  }
}

class CProfile : public CEvent {
  static std::vector<SDL_Color> ColorList;
  double T_star;              // star surface temperature (K)
  double D_star;              // distance to star (m * 10^9)
  double R_star;              // radius of star (m * 10^3)
  long p_sfc;                 // surface pressure (Pa)
  long T_sfc;                 // surface temperature (K)

  std::vector<int> T;
  std::vector<double> vol_N;
  std::vector<double> vol_O;
  std::vector<double> vol_Ar;

public:
  bool use_gamma;
  const ColorSystem* sys;

private:
  bool is_drag;     // "Drag" ticks on sounding
  bool adj_T_star;
  bool adj_D_star;
  bool adj_R_star;
  bool adj_p_sfc;
  std::string val_string;
  int active_sounding;

public:
  CProfile();
  static CProfile Control;

  bool init();

  bool calcColors();

  void OnEvent(SDL_Event* Event);
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void enterVal(SDL_Keycode sym);
  void addToVal(const char& sym);
  void delFromVal();
	void OnLButtonDown(int mX, int mY);
  void OnLButtonUp(int mX, int mY);

  void OnLoop(const SDL_Point* m);

  bool OnRender(const SDL_Point* m);
  bool drawSkyColor();
  bool drawOptions(const SDL_Point* m);
  bool drawSounding(const SDL_Point* m);

  bool draw_T();
  bool draw_v_N();
  bool draw_v_O();
  bool draw_v_Ar();
};

#endif
