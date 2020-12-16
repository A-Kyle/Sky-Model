#include "CProfile.h"

namespace Interface {
  const short w_page = WWIDTH / 3;
  namespace Sounding {
    const short w = 200;
    const short h = 500;
    const short h_lo = (h * LORES_DZ) / Z_TOP;
    const short h_hi = (h * HIRES_DZ) / Z_TOP;
    const short x_page = 1 * w_page;
    const short x_profile = x_page + ((w_page - w) / 2);
    const short y_profile = (WHEIGHT - h) / 2;
    const SDL_Rect r_profile = {x_profile, y_profile, w, h};
    const short w_but = w / 4;
    const short h_but = 26;
    const SDL_Rect T_button = {x_profile, y_profile - h_but, w_but, h_but};
    const SDL_Rect v_N_button = {T_button.x + w_but, y_profile - h_but, w_but, h_but};
    const SDL_Rect v_O_button = {v_N_button.x + w_but, y_profile - h_but, w_but, h_but};
    const SDL_Rect v_Ar_button = {v_O_button.x + w_but, y_profile - h_but, w_but, h_but};
    const SDL_Point* off_col = &palette::dark_gray;
    const SDL_Point* on_col  = &palette::dark_green;
    const SDL_Point* hov_col = &palette::dark_cyan;

    const short title_y = y_profile - h_but - 11;
    const short title_x = x_profile + (w / 2);
    const short axis_y = y_profile + h + 15;
    const short axis_x_l = x_profile;
    const short axis_x_r = x_profile + w;

    const short b_sz = 2;
    const short min_v = 0;
    const short max_v = 1;
    const short min_T = 50;
    const short max_T = 750;

  }
  namespace Options {
    const short num_fields = 4;
    const short sect_h = WHEIGHT / (num_fields + 1);
    const short w = 200;
    const short h = 35;
    const short x_page = 0 * w_page;
    const short x_field = x_page + ((w_page - w) / 2);
    const char* const c_calc    = "Calculate";
    const char* const c_reset   = "Reset to Earth";
    // const char* const c_sfc_T   = "Surface Temperature $LK$R";
    const SDL_Point* label_col  = &palette::gray;
    const SDL_Point* field_col  = &palette::light_gray;
    const SDL_Point* calc_col   = &palette::silver;
    const SDL_Point* reset_col  = &palette::red;
    const short b_sz = 2;
    const char* const labels[] = {
      "Star Temperature $LK$R",
      "Star Distance $LGm$R",
      "Star Radius $Lkm$R",
      "Surface Pressure $LPa$R"
    };
    const SDL_Rect fields[] = {
      {x_field, (sect_h - (h * 2)) / 2, w, h},
      {x_field, h + (sect_h - (h * 2)) / 2, w, h},
      {x_field, sect_h + (sect_h - (h * 2)) / 2, w, h},
      {x_field, h + sect_h + (sect_h - (h * 2)) / 2, w, h},
      {x_field, (sect_h * 2) + (sect_h - (h * 2)) / 2, w, h},
      {x_field, h + (sect_h * 2) + (sect_h - (h * 2)) / 2, w, h},
      {x_field, (sect_h * 3) + (sect_h - (h * 2)) / 2, w, h},
      {x_field, h + (sect_h * 3) + (sect_h - (h * 2)) / 2, w, h}
    };
    const SDL_Rect r_calc = {x_field, (sect_h * 4) + (sect_h - (h * 2)) / 2, w, h};
    const SDL_Rect r_reset = {x_field, h + (sect_h * 4) + (sect_h - (h * 2)) / 2, w, h};
  };

  namespace SkyColor {
    const short w = 200;
    const short h = 500;
    const short h_lo = (h * LORES_DZ) / Z_TOP;
    const short h_hi = (h * HIRES_DZ) / Z_TOP;
    const short x_page = 2 * w_page;
    const short x_profile = x_page + ((w_page - w) / 2);
    const short y_profile = (WHEIGHT - h) / 2;
    const char* const title = "Sky Color";
    const short title_y = y_profile - 20;
    const char* const axis = "Z";
    const short mark_x = x_profile - 20;
    const char* const mark_sfc = "0";
    const char* const mark_half = "25";
    const char* const mark_top = "50";
    const short axis_x = x_profile + w + 10;
    const SDL_Rect column[] = {
      {x_profile, y_profile, w, h_lo},
      {x_profile, y_profile + (h_hi * 1), w, h_lo},
      {x_profile, y_profile + (h_hi * 2), w, h_lo},
      {x_profile, y_profile + (h_hi * 3), w, h_lo},
      {x_profile, y_profile + (h_hi * 4), w, h_lo},
      {x_profile, y_profile + (h_hi * 5), w, h_lo},
      {x_profile, y_profile + (h_hi * 6), w, h_lo},
      {x_profile, y_profile + (h_hi * 7), w, h_lo},
      {x_profile, y_profile + (h_hi * 8), w, h_lo},
      {x_profile, y_profile + (h_hi * 9), w, h_lo},
      {x_profile, y_profile + (h_hi * 10), w, h_hi},
      {x_profile, y_profile + (h_hi * 11), w, h_hi},
      {x_profile, y_profile + (h_hi * 12), w, h_hi},
      {x_profile, y_profile + (h_hi * 13), w, h_hi},
      {x_profile, y_profile + (h_hi * 14), w, h_hi},
      {x_profile, y_profile + (h_hi * 15), w, h_hi},
      {x_profile, y_profile + (h_hi * 16), w, h_hi},
      {x_profile, y_profile + (h_hi * 17), w, h_hi},
      {x_profile, y_profile + (h_hi * 18), w, h_hi},
      {x_profile, y_profile + (h_hi * 19), w, h_hi},
      {x_profile, y_profile + (h_hi * 20), w, h_hi},
      {x_profile, y_profile + (h_hi * 21), w, h_hi},
      {x_profile, y_profile + (h_hi * 22), w, h_hi},
      {x_profile, y_profile + (h_hi * 23), w, h_hi},
      {x_profile, y_profile + (h_hi * 24), w, h_hi},
      {x_profile, y_profile + (h_hi * 25), w, h_hi},
      {x_profile, y_profile + (h_hi * 26), w, h_hi},
      {x_profile, y_profile + (h_hi * 27), w, h_hi},
      {x_profile, y_profile + (h_hi * 28), w, h_hi},
      {x_profile, y_profile + (h_hi * 29), w, h_hi},
      {x_profile, y_profile + (h_hi * 30), w, h_hi},
      {x_profile, y_profile + (h_hi * 31), w, h_hi},
      {x_profile, y_profile + (h_hi * 32), w, h_hi},
      {x_profile, y_profile + (h_hi * 33), w, h_hi},
      {x_profile, y_profile + (h_hi * 34), w, h_hi},
      {x_profile, y_profile + (h_hi * 35), w, h_hi},
      {x_profile, y_profile + (h_hi * 36), w, h_hi},
      {x_profile, y_profile + (h_hi * 37), w, h_hi},
      {x_profile, y_profile + (h_hi * 38), w, h_hi},
      {x_profile, y_profile + (h_hi * 39), w, h_hi},
      {x_profile, y_profile + (h_hi * 40), w, h_hi},
      {x_profile, y_profile + (h_hi * 41), w, h_hi},
      {x_profile, y_profile + (h_hi * 42), w, h_hi},
      {x_profile, y_profile + (h_hi * 43), w, h_hi},
      {x_profile, y_profile + (h_hi * 44), w, h_hi},
      {x_profile, y_profile + (h_hi * 45), w, h_hi},
      {x_profile, y_profile + (h_hi * 46), w, h_hi},
      {x_profile, y_profile + (h_hi * 47), w, h_hi},
      {x_profile, y_profile + (h_hi * 48), w, h_hi},
      {x_profile, y_profile + (h_hi * 49), w, h_hi},
    };
  }
}
