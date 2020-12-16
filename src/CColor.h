#ifndef _C_COLOR_H_
#define _C_COLOR_H_

#include <vector>
#include "CInform.h"
#include "Define.h"

#define ILLUMINANT_C    0.3101, 0.3162          // NTSC TV //
#define ILLUMINANT_D65  0.3127, 0.3291          // EBU & SMPTE //
#define ILLUMINANT_E    0.33333333, 0.33333333  // CIE equal-energy illuminant //
#define GAMMA_REC709    0

namespace CIE_xyz {
  extern const double xyz[81][3];
};

struct ColorSystem {
  std::string name;
  double xRed, yRed;    // Red x, y chromaticity coordinates //
  double xGre, yGre;    // Green "                         " //
  double xBlu, yBlu;    // Blue "                          " //
  double xWhi, yWhi;    // White point x, y //
  double gamma;         // Gamma correction //
};

class CColor {
public:
  static ColorSystem    NTSCsystem,
                        EBUsystem,
                        SMPTEsystem,
                        HDTVsystem,
                        CIEsystem,
                        Rec709system;

public:
  CColor();

  static void get_xyz(std::vector<long double> const& I, double& x, double& y, double& z);
  static void get_rgb(const ColorSystem* sys, const double& x, const double& y, const double& z, double& r, double& g, double& b);
  static bool constrain_rgb(double& r, double& g, double& b);

  static SDL_Color spectrum_to_rgb(const ColorSystem* sys, std::vector<long double> const& I);
  static double get_luminance(std::vector<long double> const& I);
  static void gamma_correct(const ColorSystem* sys, double& c);
  static void gamma_correct_rgb(const ColorSystem* sys, double& r, double& g, double& b);
  static bool normalize_rgb(double& r, double& g, double& b);
};

#endif
