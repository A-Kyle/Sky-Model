#include "CColor.h"
                                  /* Name                  xRed    yRed    xGreen  yGreen  xBlue   yBlue   White point        Gamma   */
ColorSystem CColor::NTSCsystem  =  { "NTSC",               0.67,   0.33,   0.21,   0.71,   0.14,   0.08,   ILLUMINANT_C,    GAMMA_REC709 };
ColorSystem CColor::EBUsystem   =  { "EBU",                0.64,   0.33,   0.29,   0.60,   0.15,   0.06,   ILLUMINANT_D65,  GAMMA_REC709 };
ColorSystem CColor::SMPTEsystem =  { "SMPTE",              0.630,  0.340,  0.310,  0.595,  0.155,  0.070,  ILLUMINANT_D65,  GAMMA_REC709 };
ColorSystem CColor::HDTVsystem  =  { "HDTV",               0.670,  0.330,  0.210,  0.710,  0.150,  0.060,  ILLUMINANT_D65,  GAMMA_REC709 };
ColorSystem CColor::CIEsystem   =  { "CIE",                0.7355, 0.2645, 0.2658, 0.7243, 0.1669, 0.0085, ILLUMINANT_E,    GAMMA_REC709 };
ColorSystem CColor::Rec709system = { "CIE REC 709",        0.64,   0.33,   0.30,   0.60,   0.15,   0.06,   ILLUMINANT_D65,  GAMMA_REC709 };

CColor::CColor() {
  //
}

void CColor::get_xyz(std::vector<long double> const& I, double& x, double& y, double& z) {
  using namespace CIE_xyz;

  double X = 0.0, Y = 0.0, Z = 0.0;

  for (int i = 0; i < I.size(); i++) {
    X += I[i] * xyz[i][0];
    Y += I[i] * xyz[i][1];
    Z += I[i] * xyz[i][2];
  }

  // x = X / (X + Y + Z);
  // y = Y / (X + Y + Z);
  // z = Z / (X + Y + Z);
  x = X;
  y = Y;
  z = Z;
}

void CColor::get_rgb(const ColorSystem* sys, const double& x, const double& y, const double& z, double& r, double& g, double& b) {
  // ColorSystem* sys = &CIEsystem;

  double xr, yr, zr;
  double xg, yg, zg;
  double xb, yb, zb;
  double xw, yw, zw;

  xr = sys->xRed;  yr = sys->yRed;  zr = 1 - (xr + yr);
  xg = sys->xGre;  yg = sys->yGre;  zg = 1 - (xg + yg);
  xb = sys->xBlu;  yb = sys->yBlu;  zb = 1 - (xb + yb);
  xw = sys->xWhi;  yw = sys->yWhi;  zw = 1 - (xw + yw);

  double rx, ry, rz;
  double gx, gy, gz;
  double bx, by, bz;
  double rw, gw, bw;

  rx = (yg * zb) - (yb * zg);  ry = (xb * zg) - (xg * zb);  rz = (xg * yb) - (xb * yg);
  gx = (yb * zr) - (yr * zb);  gy = (xr * zb) - (xb * zr);  gz = (xb * yr) - (xr * yb);
  bx = (yr * zg) - (yg * zr);  by = (xg * zr) - (xr * zg);  bz = (xr * yg) - (xg * yr);

  rw = ((rx * xw) + (ry * yw) + (rz * zw)) / yw;
  gw = ((gx * xw) + (gy * yw) + (gz * zw)) / yw;
  bw = ((bx * xw) + (by * yw) + (bz * zw)) / yw;

  rx = rx / rw;  ry = ry / rw;  rz = rz / rw;
  gx = gx / gw;  gy = gy / gw;  gz = gz / gw;
  bx = bx / bw;  by = by / bw;  bz = bz / bw;

  r = (rx * x) + (ry * y) + (rz * z);
  g = (gx * x) + (gy * y) + (gz * z);
  b = (bx * x) + (by * y) + (bz * z);
}

bool CColor::constrain_rgb(double& r, double& g, double& b) {
  if (r >= 0.0 && g >= 0.0 && b >= 0.0) return false;

  double w;

  // Amount of white needed is w = - min(0, r, g, b)

  w = (0 < r) ? 0 : r;
  w = (w < g) ? w : g;
  w = (w < b) ? w : b;
  w = -w;

  /* Add just enough white to make r, g, b all positive. */

  r += w;
  g += w;
  b += w;

  return true;
}

SDL_Color CColor::spectrum_to_rgb(const ColorSystem* sys, std::vector<long double> const& I) {
  SDL_Color retval;
  double x = 0.0, y = 0.0, z = 0.0;
  double r = 0.0, g = 0.0, b = 0.0;
  get_xyz(I, x, y, z);
  get_rgb(sys, x, y, z, r, g, b);
  std::string msg = "rgb";
  if (constrain_rgb(r, g, b)) {
    // CInform::InfoControl.pushInform("Warning\nColor has been approximated");
  }
  {
    msg += "\n" + Font::doubleToStr(r * MAX_RGBA, 5) + " "
        + Font::doubleToStr(g * MAX_RGBA, 5) + " "
        + Font::doubleToStr(b * MAX_RGBA, 5) + " ";
  }

  gamma_correct_rgb(sys, r, g, b);

  msg += "\n" + Font::doubleToStr(r * MAX_RGBA, 5) + " "
      + Font::doubleToStr(g * MAX_RGBA, 5) + " "
      + Font::doubleToStr(b * MAX_RGBA, 5) + " ";

  r *= MAX_RGBA;
  g *= MAX_RGBA;
  b *= MAX_RGBA;

  if (normalize_rgb(r, g, b)) {
    // CInform::InfoControl.pushInform("Warning\nColor has been approximated");
  }

  retval.r = r;
  retval.g = g;
  retval.b = b;

  msg += "\n" + Font::intToStr(retval.r) + " "
      + Font::intToStr(retval.g) + " "
      + Font::intToStr(retval.b) + " ";
  CInform::InfoControl.pushInform(msg.c_str());

  return retval;
}

double CColor::get_luminance(std::vector<long double> const& I) {
  using namespace CIE_xyz;

  double Y = 0.0;

  for (int i = 0; i < I.size(); i++) {
    Y += I[i] * xyz[i][1];
  }
  return Y;
}

void CColor::gamma_correct(const ColorSystem* sys, double& c) {
  double gamma;

  gamma = sys->gamma;
  // gamma = 2.2;
  if (gamma == GAMMA_REC709) {
      /* Rec. 709 gamma correction. */
      double cc = 0.018;

      if (c < cc) {
          c *= ((1.099 * pow(cc, 0.45)) - 0.099) / cc;
      } else {
          c = (1.099 * pow(c, 0.45)) - 0.099;
      }
  } else {
      /* Nonlinear colour = (Linear colour)^(1/gamma) */
      c = pow(c, 1.0 / gamma);
  }
}

void CColor::gamma_correct_rgb(const ColorSystem* sys, double& r, double& g, double& b) {
  gamma_correct(sys, r);
  gamma_correct(sys, g);
  gamma_correct(sys, b);
}

bool CColor::normalize_rgb(double& r, double& g, double& b) {
  if (r > MAX_RGBA || g > MAX_RGBA || b > MAX_RGBA) {
    double r_norm, g_norm, b_norm;
    double max_val = (r > 0.0) ? r : 0.0;
    max_val = (g > max_val) ? g : max_val;
    max_val = (b > max_val) ? b : max_val;

    r_norm = r / max_val;
    g_norm = g / max_val;
    b_norm = b / max_val;

    r = r_norm * MAX_RGBA;
    g = g_norm * MAX_RGBA;
    b = b_norm * MAX_RGBA;

    return true;
  }
  return false;
}
