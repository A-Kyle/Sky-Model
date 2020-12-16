#ifndef _C_CORE_H_
#define _C_CORE_H_

#include <vector>
#include <math.h>
#include "CInform.h"
#include "CFont.h"
#include "Define.h"

namespace constants {
  extern const float R_uni;
  extern const long double pi;   
  extern const long double Na;   // Avogadro's constant (10^23 mol^-1)
  extern const long double SB;   // stefan-boltzmann constant (W/m^2 * 10^-8)
  extern const long double Pc_A; // Planck's Law constant (c_1 in W/m^2 * 10^-16, numerator)
  extern const long double Pc_B; // Planck's Law constant (c_2 in m K, denominator)
  extern const long double Sc_A; // Rayleigh scattering cross section constant (128 pi^5 / 3)
  extern const long double I_A;  // directional scattering constant
  extern const double r_N;       // "radius" of diatomic N (nm, or 10^-9 m)
  extern const double r_O;       // "radius" of diatomic O (nm)
  extern const double r_Ar;      // "radius" of atomic Ar (nm)
  extern const double v_N;       // volume fraction of diatomic N
  extern const double v_O;       // volume fraction of diatomic O
  extern const double v_Ar;      // volume fraction of atomic Ar
  extern const double n_N;       // refractive index of diatomic N
  extern const double n_O;       // refractive index of diatomic O
  extern const double n_Ar;      // refractive index of atomic Ar
};

namespace sun {
  extern const unsigned int T;        // Sun surface temperature (K)
  extern const long         D;        // distance to Sun (m * 10^9)
  extern const long         R;        // radius of the Sun (m * 10^3)
};

namespace earth {
  extern const float        g;
  extern const short        R_d;
  extern const int          p_standard;        // earth mean atmospheric surface pressure (Pa)
  extern const int          T_standard;
  extern const unsigned int T[];          // estimated average earth temperature profile (K)
  extern const unsigned int z[];          // heights of temperatures in the T array (m)
  extern const unsigned int T_hi[];          // estimated average earth temperature profile (K)
  extern const unsigned int z_hi[];          // heights of temperatures in the T array (m)
};

struct PhysData {
  unsigned int lambda;  // radiation wavelength (m * 10^-9)
  long double B;        // monochromatic radiance (W / m^2 sr)
  long double F;        // irradiance at top of atmosphere (W / m^2)
  long double s_N;      // N2 scattering cross section as a function of wavelength (m^2)
  long double s_O;      // O2 scattering cross section as a function of wavelength (m^2)
  long double s_Ar;     // Ar scattering cross section as a function of wavelength (m^2)
};

struct AtmosData {
  unsigned int z;   // m
  unsigned int T;   // K
  long double p;    // pa
  double vol_N;
  double vol_O;
  double vol_Ar;
  long double num_N;    // number density of N2 as a function of z (m^-3)
  long double num_O;
  long double num_Ar;
};

// profile of radiation data for a given wavelength
// NOTE: first index is at top of atmosphere
struct RadiData {
  long double b;          // volume scattering coefficient of entire layer (m^-1)
  long double t;          // transmissivity of entire layer (unitless)
  long double I;          // intensity incident at center of layer (W/m^2)
  long double P;          // power scattered into the horizontal by one particle (one direction) (W)
  long double I_sca_N;    // intensity scattered toward the viewer looking at horizon by N2 particles (W/m^2)
  long double I_sca_O;    // intensity scattered toward the viewer looking at horizon by O2 particles (W/m^2)
  long double I_sca_Ar;   // intensity scattered toward the viewer looking at horizon by Ar molecules (W/m^2)
  long double I_sca_tot;  // intensity scattered toward the viewer looking at horizon by all (W/m^2)
};

class CCore {
  CCore();

public:
  static CCore Control;

private:
  static std::vector<PhysData> insol;
  static std::vector<AtmosData> atmos;
  static std::vector< std::vector<RadiData> > optic;

private:
  double T_star;              // star surface temperature (K)
  double D_star;              // distance to star (m * 10^9)
  double R_star;              // radius of star (m * 10^3)
  unsigned short dlambda;     // wavelength interval for integrating Planck's Law (m * 10^-9)

private:
  long p_sfc;                 // surface pressure (Pa)
  long T_sfc;                 // surface temperature (K)
  double g;                   // gravity (m/s^2)
  unsigned long S;            // solar flux incident at TOA (integer W/m^2)

public:
  bool init();
  bool initPhys();
  bool initAtmos();
  bool initOptic();

  bool calculate();
  bool calcPhys();
  bool calcAtmos();
  bool calcOptic();

  void calcSolarFlux();
  long double calcNumConcen(const double& v, const double& p, const double& T);

  // lambda in nanometers
  long double calcSpectralRad(const unsigned int& lambda, const double& T);
  // long double calcCrossCoeff(const unsigned int& lambda, const double& n);
  // calculates volume scattering coefficient, b
  long double calcScatCoeff(const long double& sigma, const long double& N);
  long double calcScatCross(const unsigned int& lambda, const long double& N_density, const double& n);
  long double calcOpticalPath(const long double& sigma, const long double& N, const unsigned int ds);
  long double calcTrans(const long double& tau);
  long double calcTrans(const long double& b, const unsigned int ds);
  long double calcScatPower(const long double& Io, const long double& sigma);
  long double calcScatInten(const long double& Io, const long double& N, const long double& sigma, const unsigned int dz);
  long double calcScatInten(const long double& Io, const long double& b, const unsigned int dz);

  unsigned long getSolarFlux();

  long double hypsoPress(const unsigned long long& p_o, const double& T, const int& dz);

  void setEarthT();
  void setLevs();

  int getP(const int& i);
  double getT_star();
  double getD_star();
  double getR_star();
  long getp_sfc();
  long getT_sfc();
  long double getIntegratedFlux();

  void set_T_star(const double& T);
  void set_D_star(const double& D);
  void set_R_star(const double& R);
  void set_p_sfc(const double& p);
  void set_T_profile(std::vector<int> const& T);
  void set_v_profile(std::vector<double> const& N, std::vector<double> const& O, std::vector<double> const& Ar);

  static long double calcBoltzLaw(const double& T);

  std::vector<long double> getSpectrum(const unsigned int& i_layer);
  std::vector<int> get_T();
  std::vector<double> get_vol_N();
  std::vector<double> get_vol_O();
  std::vector<double> get_vol_Ar();
};

#endif
