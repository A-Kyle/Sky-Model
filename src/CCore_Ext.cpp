#include "CCore.h"

namespace constants {
  const float R_uni             = 8.31446;
  const long double pi          = 3.141592653589793238462643383279502884197169399;
  const long double Na          = 6.0221409;
  const long double SB          = 5.67;
  const long double Pc_A        = 1.19268;
  const long double Pc_B        = 0.014388;
  const long double Sc_A        = 24.0 * pow(pi, 3.0);
  const long double I_A         = 3.0 / (4.0 * pi); // multiplied orig. by 4; I think the volume is actually dz*4R^2, NOT dz*R^2
  const double r_N              = 0.16447;
  const double r_O              = 0.15627;
  const double r_Ar             = 0.1880;
  const double v_N              = 0.7808;
  const double v_O              = 0.2095;
  const double v_Ar             = 0.00934;
  const double n_N              = 1.00028282; // Peck and Khanna 1966
  const double n_O              = 1.00025206; // Zhang et al. 2008
  const double n_Ar             = 1.00026705; // Peck and Fisher 1964
};

namespace sun {
  const unsigned int T          = 5770;
  const long D                  = 149;
  const long R                  = 695700;
};

namespace earth {
  const float g                 = 9.81;
  const short R_d               = 287;
  const int p_standard          = 101325;
  const int T_standard          = 288;
  const unsigned int T[] = {
    285, 278, 272, 266, 259,
    252, 246, 239, 233, 227,
    220, 217, 217, 217, 217,
    217, 217, 217, 217, 217,

    218, 221, 224, 227, 232,
    240, 247, 255, 263, 270,
  };
  const unsigned int z[] = {
    500, 1500, 2500, 3500, 4500,
    5500, 6500, 7500, 8500, 9500,
    10500, 11500, 12500, 13500, 14500,
    15500, 16500, 17500, 18500, 19500,

    21500, 24500, 27500, 30500, 33500,
    36500, 39500, 42500, 45500, 48500,
  };
  const unsigned int T_hi[] = {
    285, 278, 272, 266, 259,
    252, 246, 239, 233, 227,
    220, 217, 217, 217, 217,
    217, 217, 217, 217, 217,

    218, 218, 218, 221, 221,
    221, 224, 224, 224, 227,
    227, 227, 232, 232, 232,
    240, 240, 240, 247, 247,
    247, 255, 255, 255, 263,
    263, 263, 270, 270, 270,
  };
  const unsigned int z_hi[] = {
    500, 1500, 2500, 3500, 4500,
    5500, 6500, 7500, 8500, 9500,
    10500, 11500, 12500, 13500, 14500,
    15500, 16500, 17500, 18500, 19500,

    20500, 21500, 22500, 23500, 24500,
    25500, 26500, 27500, 28500, 29500,
    30500, 31500, 32500, 33500, 34500,
    35500, 36500, 37500, 38500, 39500,
    40500, 41500, 42500, 43500, 44500,
    45500, 46500, 47500, 48500, 49500,
  };
};
