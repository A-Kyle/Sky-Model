#include "CProfile.h"

CProfile CProfile::Control;
std::vector<SDL_Color> CProfile::ColorList;

CProfile::CProfile() {
  is_drag    = false;
  adj_T_star = false;
  adj_D_star = false;
  adj_R_star = false;
  adj_p_sfc  = false;
  val_string  = "";
  use_gamma = true;
  sys = &CColor::CIEsystem;
  active_sounding = T_PROF;
}

bool CProfile::init() {
  T_star = CCore::Control.getT_star();
  D_star = CCore::Control.getD_star();
  R_star = CCore::Control.getR_star();
  p_sfc = CCore::Control.getp_sfc();
  T_sfc = CCore::Control.getT_sfc();
  T = CCore::Control.get_T();
  vol_N = CCore::Control.get_vol_N();
  vol_O = CCore::Control.get_vol_O();
  vol_Ar = CCore::Control.get_vol_Ar();

  return calcColors();
}

bool CProfile::calcColors() {
  // calculate initial colors
  ColorList.clear();

  std::string msg = "yello";
  std::vector<long double> I;

  // layer 0 = top of atmosphere
  // i 0 = shortest wavelength (380 nm)
  for (int i = 0; i < NUM_LAYERS_HI; i++) {
    I.clear();
    SDL_Color tmp;

    I = CCore::Control.getSpectrum(i);
    tmp = CColor::spectrum_to_rgb(sys, I);

    // int tmp = I.size();
    // if (i == 28) {
    //   msg += "\n" + Font::doubleToStr(I[0], 10);
    // }
    // msg += "\n" + Font::intToStr(tmp.r) + Font::intToStr(tmp.g) + Font::intToStr(tmp.b);
    ColorList.push_back(tmp);

    double Y = CColor::get_luminance(I);
    msg += "\n" + Font::doubleToStr(Y, 10);
  }

  // CInform::InfoControl.pushInform(msg.c_str());
  return true;
}

void CProfile::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CProfile::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  if (adj_T_star || adj_D_star || adj_R_star || adj_p_sfc) {
    enterVal(sym);
  }
}

void CProfile::enterVal(SDL_Keycode sym) {
  switch (sym) {
    case SDLK_0:	        addToVal('0');	      break;
    case SDLK_1:	        addToVal('1');	      break;
    case SDLK_2:	        addToVal('2');	      break;
    case SDLK_3:	        addToVal('3');	      break;
    case SDLK_4:	        addToVal('4');	      break;
    case SDLK_5:	        addToVal('5');	      break;
    case SDLK_6:	        addToVal('6');	      break;
    case SDLK_7:	        addToVal('7');	      break;
    case SDLK_8:	        addToVal('8');	      break;
    case SDLK_9:	        addToVal('9');	      break;
    case SDLK_PERIOD:     addToVal('.');        break;
    case SDLK_BACKSPACE:  delFromVal();         break;
    case SDLK_ESCAPE:  {
      adj_T_star = adj_D_star = adj_R_star = adj_p_sfc = false;
      val_string.clear();
      break;
    }
    case SDLK_RETURN:  {
      if (!val_string.empty()) {
        // Ensure that the string represents a non-zero value
        // If any character in the string is not a '0' or floating point,
        // the string is valid for making a new layer
        int i = 0;
        while (true) {
          if (val_string[i] != '0' && val_string[i] != '.') break;
          if (val_string.size() <= ++i) {     // invalid string
            adj_T_star = adj_D_star = adj_R_star = adj_p_sfc = false;
            val_string.clear();
            return;
          }
        }
        double val = CAsset::strToDouble(val_string);
        if (adj_T_star) T_star = val;
        if (adj_D_star) D_star = val;
        if (adj_R_star) R_star = val;
        if (adj_p_sfc)  p_sfc = (val < MIN_P) ? MIN_P : val;
        adj_T_star = adj_D_star = adj_R_star = adj_p_sfc = false;
        val_string.clear();
      }
      break;
    }
    default:              break;
  }
}

void CProfile::addToVal(const char& sym) {
  // don't add a zero if the string is empty
  if (val_string.empty() && sym == '0') return;
  int z_precision = 9;
  // if the requested add is a period,
  // it can only be added if no other periods are in the string.
  // Also, if the period is added when the string is empty, a leading
  // zero must be added.
  if (sym == '.') {
    if (val_string.empty()) val_string.push_back('0');
    else {
      for (int i = 0; i < val_string.size(); i++) {
        if (val_string[i] == sym) return;
      }
    }
  }
  // if the requested add is anything other than a period,
  // it cannot be added to the string if there are already 4 digits on either
  // side of the floating point (z_precision = 4).
  else {
    bool fract = false;
    short fract_i = 0;
    for (int i = 0; i < val_string.size(); i++) {
      if (val_string[i] == '.') {
        fract = true;
        fract_i = i;
        break;
      }
    }
    if (!fract && val_string.size() >= z_precision) return;
    if (val_string.size() - fract_i  > z_precision) return;
  }
  // if the program flow makes it to this point in this function,
  // then we are able to push back the requested symbol.
  val_string.push_back(sym);
}

void CProfile::delFromVal() {
  if (val_string == "0.") val_string.clear();
  else if (val_string.size() > 0) val_string.erase(val_string.end() - 1);
}

void CProfile::OnLButtonDown(int mX, int mY) {
  if (adj_T_star || adj_D_star || adj_R_star || adj_p_sfc) return;

  const SDL_Point m = {mX, mY};

  if (SDL_PointInRect(&m, &Interface::Sounding::r_profile)) {
    is_drag = true;
  }

  if (SDL_PointInRect(&m, &Interface::Sounding::T_button)) {
    active_sounding = T_PROF; return;
  }
  if (SDL_PointInRect(&m, &Interface::Sounding::v_N_button)) {
    active_sounding = V_N_PROF; return;
  }
  if (SDL_PointInRect(&m, &Interface::Sounding::v_O_button)) {
    active_sounding = V_O_PROF; return;
  }
  if (SDL_PointInRect(&m, &Interface::Sounding::v_Ar_button)) {
    active_sounding = V_AR_PROF; return;
  }

  if (SDL_PointInRect(&m, &Interface::Options::fields[1])) adj_T_star = true;
  if (SDL_PointInRect(&m, &Interface::Options::fields[3])) adj_D_star = true;
  if (SDL_PointInRect(&m, &Interface::Options::fields[5])) adj_R_star = true;
  if (SDL_PointInRect(&m, &Interface::Options::fields[7])) adj_p_sfc  = true;

  if (SDL_PointInRect(&m, &Interface::Options::r_calc)) {
    CCore::Control.set_T_star(T_star);
    CCore::Control.set_D_star(D_star);
    CCore::Control.set_R_star(R_star);
    CCore::Control.set_p_sfc(p_sfc);
    CCore::Control.set_T_profile(T);
    CCore::Control.set_v_profile(vol_N, vol_O, vol_Ar);
    CCore::Control.calculate();
    calcColors();
  }

  if (SDL_PointInRect(&m, &Interface::Options::r_reset)) {
    CCore::Control.init();
    init();
  }
}

void CProfile::OnLButtonUp(int mX, int mY) {
  if (is_drag) is_drag = false;
}

void CProfile::OnLoop(const SDL_Point* m) {
  if (is_drag) {
    using namespace Interface::Sounding;
    if (SDL_PointInRect(m, &r_profile)) {
      int y_rel = r_profile.y + r_profile.h - m->y;
      int x_rel = m->x - r_profile.x;
      int z = y_rel / h_hi;
      double x_weight = (double)(x_rel) / (double)(r_profile.w);
      switch (active_sounding) {
        case T_PROF: {
          double new_T = x_weight * (max_T - min_T) + min_T;
          T[z] = new_T;
          break;
        }
        case V_N_PROF: {
          double v = x_weight * (max_v - min_v) + min_v;
          vol_N[z] = v;
          break;
        }
        case V_O_PROF: {
          double v = x_weight * (max_v - min_v) + min_v;
          vol_O[z] = v;
          break;
        }
        case V_AR_PROF: {
          double v = x_weight * (max_v - min_v) + min_v;
          vol_Ar[z] = v;
          break;
        }
        default: break;
      }
    } else {
      is_drag = false;
    }
  }
}

bool CProfile::OnRender(const SDL_Point* m) {
  if (!drawSkyColor()) return false;
  if (!drawOptions(m)) return false;
  if (!drawSounding(m)) return false;
  return true;
}

bool CProfile::drawSkyColor() {
  using namespace Interface::SkyColor;

  for (int i = 0; i < NUM_LAYERS_HI; i++) {
    if (!CAsset::drawBoxFill(&column[i], &ColorList[i])) return false;
  }

  Font::FontControl.SetFont(FONT_DEFAULT);
  SDL_Point c_pos = {x_profile + w / 2, title_y};
  Font::NewCenterWrite(title, &c_pos, &rgb::white);
  c_pos.x = axis_x;
  c_pos.y = y_profile + h / 2;
  Font::NewCenterWrite(axis, &c_pos, &rgb::white);
  c_pos.x = mark_x;
  c_pos.y -= 0;                 Font::NewCenterWrite(FONT_DEFAULT, mark_half, &c_pos, &rgb::white);
  c_pos.y = y_profile + h;  Font::NewCenterWrite(FONT_DEFAULT, mark_sfc, &c_pos, &rgb::white);
  c_pos.y = y_profile;      Font::NewCenterWrite(FONT_DEFAULT, mark_top, &c_pos, &rgb::white);

  return true;
}

bool CProfile::drawOptions(const SDL_Point* m) {
  using namespace Interface::Options;
  std::string str[] = {
    labels[0],
    adj_T_star ? val_string : Font::doubleToStr(T_star, 2),
    labels[1],
    adj_D_star ? val_string : Font::doubleToStr(D_star, 2),
    labels[2],
    adj_R_star ? val_string : Font::doubleToStr(R_star, 2),
    labels[3],
    adj_p_sfc ? val_string : Font::intToStr(p_sfc)
  };

  bool active[] = {
    false,
    adj_T_star,
    false,
    adj_D_star,
    false,
    adj_R_star,
    false,
    adj_p_sfc
  };

  for (int i = 0; i < num_fields * 2; i++) {
    // Font::FontControl.SetFont(FONT_MINI);
    if (!CAsset::drawBoxFill(&fields[i], (i % 2) ? (active[i] ? &palette::blue : field_col) : label_col)) return false;
    if (active[i]) Font::FontControl.setDynamic();
    Font::NewCenterWrite(FONT_DEFAULT, str[i].c_str(), &fields[i], &rgb::black);
  }
  if (!CAsset::drawStrBox(&r_calc, b_sz, SDL_PointInRect(m, &r_calc) ? calc_col : &palette::black, &palette::gray)) return false;
  if (!CAsset::drawStrBox(&r_reset, b_sz, SDL_PointInRect(m, &r_reset) ? reset_col : &palette::black, &palette::gray)) return false;
  Font::NewCenterWrite(c_calc, &r_calc, SDL_PointInRect(m, &r_calc) ? &rgb::black : &rgb::light_green);
  Font::NewCenterWrite(c_reset, &r_reset, SDL_PointInRect(m, &r_reset) ? &rgb::black : &rgb::red);
  return true;
}

bool CProfile::drawSounding(const SDL_Point* m) {
  using namespace Interface::Sounding;

  Font::FontControl.SetFont(FONT_DEFAULT);

  bool active = (active_sounding == T_PROF);
  if (!CAsset::drawStrBox(&T_button, b_sz, active ? on_col : (SDL_PointInRect(m, &T_button) ? hov_col : off_col))) return false;
  Font::NewCenterWrite("T", &T_button, &rgb::white);
  active = (active_sounding == V_N_PROF);
  if (!CAsset::drawStrBox(&v_N_button, b_sz, active ? on_col : (SDL_PointInRect(m, &v_N_button) ? hov_col : off_col))) return false;
  Font::NewCenterWrite("N2", &v_N_button, &rgb::white);
  active = (active_sounding == V_O_PROF);
  if (!CAsset::drawStrBox(&v_O_button, b_sz, active ? on_col : (SDL_PointInRect(m, &v_O_button) ? hov_col : off_col))) return false;
  Font::NewCenterWrite("O2", &v_O_button, &rgb::white);
  active = (active_sounding == V_AR_PROF);
  if (!CAsset::drawStrBox(&v_Ar_button, b_sz, active ? on_col : (SDL_PointInRect(m, &v_Ar_button) ? hov_col : off_col))) return false;
  Font::NewCenterWrite("AR", &v_Ar_button, &rgb::white);

  switch (active_sounding) {
    case T_PROF:  draw_T(); break;
    case V_N_PROF:  draw_v_N(); break;
    case V_O_PROF:  draw_v_O(); break;
    case V_AR_PROF:  draw_v_Ar(); break;
    default: break;
  }

  return true;
}

bool CProfile::draw_T() {
  using namespace Interface::Sounding;

  SDL_Rect dstR = {x_profile, 0, w, h_hi};
  SDL_Rect dstTick = {0, 0, 1, h_hi};

  int z = NUM_LAYERS_HI - 1;
  for (int i = 0; i < NUM_LAYERS_HI; i++) {
    dstR.y = dstTick.y = y_profile + (i * h_hi);
    double dx = (double)(w) * ((double)(T[z--] - min_T) / (double)(max_T - min_T));
    dstTick.x = x_profile + dx;
    if (!CAsset::drawBoxFill(&dstTick, &palette::light_red)) return false;
    if (!CAsset::drawBox(&dstR, &palette::dark_gray, 1)) return false;
  }

  std::string str_min = Font::intToStr(min_T); SDL_Point p_min = {axis_x_l, axis_y};
  std::string str_max = Font::intToStr(max_T); SDL_Point p_max = {axis_x_r, axis_y};
  Font::NewCenterWrite(str_min.c_str(), &p_min, &rgb::white);
  Font::NewCenterWrite(str_max.c_str(), &p_max, &rgb::white);

  SDL_Point p_title = {title_x, title_y};
  Font::NewCenterWrite("Temperature", &p_title, &rgb::white);
  return true;
}

bool CProfile::draw_v_N() {
  using namespace Interface::Sounding;

  SDL_Rect dstR = {x_profile, 0, w, h_hi};
  SDL_Rect dstTick = {0, 0, 1, h_hi};

  int z = NUM_LAYERS_HI - 1;
  for (int i = 0; i < NUM_LAYERS_HI; i++) {
    dstR.y = dstTick.y = y_profile + (i * h_hi);
    double dx = (double)(w) * ((double)(vol_N[z--] - min_v) / (double)(max_v - min_v));
    dstTick.x = x_profile + dx;
    if (!CAsset::drawBoxFill(&dstTick, &palette::light_red)) return false;
    if (!CAsset::drawBox(&dstR, &palette::dark_gray, 1)) return false;
  }

  std::string str_min = Font::intToStr(min_v); SDL_Point p_min = {axis_x_l, axis_y};
  std::string str_max = Font::intToStr(max_v); SDL_Point p_max = {axis_x_r, axis_y};
  Font::NewCenterWrite(str_min.c_str(), &p_min, &rgb::white);
  Font::NewCenterWrite(str_max.c_str(), &p_max, &rgb::white);

  SDL_Point p_title = {title_x, title_y};
  Font::NewCenterWrite("N2 Fraction", &p_title, &rgb::white);
  return true;
}

bool CProfile::draw_v_O() {
  using namespace Interface::Sounding;

  SDL_Rect dstR = {x_profile, 0, w, h_hi};
  SDL_Rect dstTick = {0, 0, 1, h_hi};

  int z = NUM_LAYERS_HI - 1;
  for (int i = 0; i < NUM_LAYERS_HI; i++) {
    dstR.y = dstTick.y = y_profile + (i * h_hi);
    double dx = (double)(w) * ((double)(vol_O[z--] - min_v) / (double)(max_v - min_v));
    dstTick.x = x_profile + dx;
    if (!CAsset::drawBoxFill(&dstTick, &palette::light_red)) return false;
    if (!CAsset::drawBox(&dstR, &palette::dark_gray, 1)) return false;
  }

  std::string str_min = Font::intToStr(min_v); SDL_Point p_min = {axis_x_l, axis_y};
  std::string str_max = Font::intToStr(max_v); SDL_Point p_max = {axis_x_r, axis_y};
  Font::NewCenterWrite(str_min.c_str(), &p_min, &rgb::white);
  Font::NewCenterWrite(str_max.c_str(), &p_max, &rgb::white);

  SDL_Point p_title = {title_x, title_y};
  Font::NewCenterWrite("O2 Fraction", &p_title, &rgb::white);

  return true;
}

bool CProfile::draw_v_Ar() {
  using namespace Interface::Sounding;

  SDL_Rect dstR = {x_profile, 0, w, h_hi};
  SDL_Rect dstTick = {0, 0, 1, h_hi};

  int z = NUM_LAYERS_HI - 1;
  for (int i = 0; i < NUM_LAYERS_HI; i++) {
    dstR.y = dstTick.y = y_profile + (i * h_hi);
    double dx = (double)(w) * ((double)(vol_Ar[z--] - min_v) / (double)(max_v - min_v));
    dstTick.x = x_profile + dx;
    if (!CAsset::drawBoxFill(&dstTick, &palette::light_red)) return false;
    if (!CAsset::drawBox(&dstR, &palette::dark_gray, 1)) return false;
  }

  std::string str_min = Font::intToStr(min_v); SDL_Point p_min = {axis_x_l, axis_y};
  std::string str_max = Font::intToStr(max_v); SDL_Point p_max = {axis_x_r, axis_y};
  Font::NewCenterWrite(str_min.c_str(), &p_min, &rgb::white);
  Font::NewCenterWrite(str_max.c_str(), &p_max, &rgb::white);

  SDL_Point p_title = {title_x, title_y};
  Font::NewCenterWrite("Ar Fraction", &p_title, &rgb::white);

  return true;
}
