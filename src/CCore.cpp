#include "CCore.h"

CCore CCore::Control;
std::vector<PhysData> CCore::insol;
std::vector<AtmosData> CCore::atmos;
std::vector< std::vector<RadiData> > CCore::optic;

CCore::CCore() {
  //
}

bool CCore::init() {
  T_star      = sun::T;
  D_star      = sun::D;
  R_star      = sun::R;
  dlambda     = 5;

  p_sfc       = earth::p_standard; // FOR SOME REASON THIS MUST BE >= 2500 Pa.
  T_sfc       = earth::T_standard;
  g           = earth::g;

  if (!initPhys()) return false;
  if (!initAtmos()) return false;
  if (!initOptic()) return false;

  calcSolarFlux();
  return true;
}

bool CCore::calculate() {
  if (!calcPhys()) return false;
  if (!calcAtmos()) return false;
  if (!calcOptic()) return false;
  return true;
}

bool CCore::initPhys() {
  return calcPhys();
}

bool CCore::initAtmos() {
  using namespace earth;
  atmos.clear();

  for (int i = 0; i < NUM_LAYERS_HI; i++) {
    AtmosData tmp;
    tmp.z = z_hi[i];
    tmp.T = T_hi[i];

    if (i > 0) {
      double ave_T = (T_hi[i-1] + T_hi[i]) / 2.0;
      int dz = z_hi[i] - z_hi[i-1];
      tmp.p = hypsoPress(atmos[i-1].p, ave_T, dz);
    }
    else tmp.p = hypsoPress(p_sfc, T_sfc, z_hi[i]);

    tmp.vol_N = constants::v_N;
    tmp.vol_O = constants::v_O;
    tmp.vol_Ar = constants::v_Ar;
    tmp.num_N = calcNumConcen(constants::v_N, tmp.p, tmp.T);
    tmp.num_O = calcNumConcen(constants::v_O, tmp.p, tmp.T);
    tmp.num_Ar = calcNumConcen(constants::v_Ar, tmp.p, tmp.T);

    atmos.push_back(tmp);
  }
  return true;
}

bool CCore::initOptic() {
  return calcOptic();
}

bool CCore::calcPhys() {
  using namespace constants;
  insol.clear();

  for (int i = MIN_LAMBDA; i <= MAX_LAMBDA; i += dlambda) {
    PhysData tmp;
    tmp.lambda = i;
    tmp.B = calcSpectralRad(i, T_star);

    if (tmp.B <= 0.0) return false;
    tmp.F = tmp.B * ((double)(dlambda) * pow(10.0, -9.0)) * pi * pow((R_star / D_star) * pow(10.0, -6.0), 2.0);
    if (tmp.F <= 0.0) return false;

    tmp.s_N = calcScatCross(i, calcNumConcen(v_N + v_O + v_Ar, earth::p_standard, earth::T_standard), n_N);
    tmp.s_O = calcScatCross(i, calcNumConcen(v_N + v_O + v_Ar, earth::p_standard, earth::T_standard), n_O);
    tmp.s_Ar = calcScatCross(i, calcNumConcen(v_N + v_O + v_Ar, earth::p_standard, earth::T_standard), n_Ar);

    insol.push_back(tmp);
  }
  return true;
}

bool CCore::calcAtmos() {
  for (int i = 0; i < NUM_LAYERS_HI; i++) {
    if (i > 0) {
      double ave_T = (atmos[i-1].T + atmos[i].T) / 2.0;
      int dz = atmos[i].z - atmos[i-1].z;
      atmos[i].p = hypsoPress(atmos[i-1].p, ave_T, dz);
    }
    else atmos[i].p = hypsoPress(p_sfc, T_sfc, atmos[i].z);

    atmos[i].num_N = calcNumConcen(atmos[i].vol_N, atmos[i].p, atmos[i].T);
    atmos[i].num_O = calcNumConcen(atmos[i].vol_O, atmos[i].p, atmos[i].T);
    atmos[i].num_Ar = calcNumConcen(atmos[i].vol_Ar, atmos[i].p, atmos[i].T);
  }
  return true;
}

bool CCore::calcOptic() {
  optic.clear();

  for (int i = 0; i < insol.size(); i++) {
    std::vector<RadiData> profile;
    for (int j = atmos.size() - 1; j >= 0; j--) {
      RadiData tmp;
      unsigned int dz = j < NUM_HIRES ? HIRES_DZ : LORES_DZ;

      tmp.b = calcScatCoeff(insol[i].s_N, atmos[j].num_N)
            + calcScatCoeff(insol[i].s_O, atmos[j].num_O)
            + calcScatCoeff(insol[i].s_Ar, atmos[j].num_Ar);

      tmp.t = calcTrans(tmp.b, dz);

      long double total_t = 1.0;
      for (int k = 0; k < profile.size(); k++) {
        total_t *= profile[k].t;
      }
      total_t *= calcTrans(tmp.b, dz / 2);
      tmp.I = insol[i].F * total_t;

      long double total_sigma = atmos[j].vol_N * insol[i].s_N
                              + atmos[j].vol_O * insol[i].s_O
                              + atmos[j].vol_Ar * insol[i].s_Ar;

      tmp.P = calcScatPower(tmp.I, total_sigma);

      tmp.I_sca_N = calcScatInten(tmp.I, atmos[j].num_N, insol[i].s_N, dz);
      tmp.I_sca_O = calcScatInten(tmp.I, atmos[j].num_O, insol[i].s_O, dz);
      tmp.I_sca_Ar = calcScatInten(tmp.I, atmos[j].num_Ar, insol[i].s_Ar, dz);
      tmp.I_sca_tot = calcScatInten(tmp.I, tmp.b, dz);

      profile.push_back(tmp);
    }
    optic.push_back(profile);
  }
  return true;
}

void CCore::calcSolarFlux() {
  using namespace constants;
  long double val = 0.0;

  val = calcBoltzLaw(T_star) * pow ((R_star / D_star) * pow(10.0, -6.0), 2.0);
  S = val;
}

long double CCore::calcNumConcen(const double& v, const double& p, const double& T) {
  if (v <= 0.0 || p <= 0.0 || T <= 0.0) return 0.0;

  long double val = pow(10.0, 23.0) * v * p * constants::Na / (constants::R_uni * T);
  return val;
}

long double CCore::calcSpectralRad(const unsigned int& lambda, const double& T) {
  if (T <= 0.0) return 0.0;
  using namespace constants;

  long double exp_val = Pc_B / (pow(10.0, -9.0) * (double)(lambda) * T);
  long double denom = pow((double)(lambda), 5.0) * (exp(exp_val) - 1.0);
  long double B = pow(10.0, 29.0) * Pc_A / denom;
  return B;
}

long double CCore::calcScatCross(const unsigned int& lambda, const long double& N_density, const double& n) {
  if (N_density <= 0.0 || n < 1.0) return 0.0;
  using namespace constants;

  double refr = pow((pow(n, 2.0) - 1.0) / (pow(n, 2.0) + 2.0), 2.0);
  long double denom = pow(10.0, -36.0) * N_density * N_density * pow(lambda, 4.0);

  return Sc_A * refr / denom;
}

long double CCore::calcScatCoeff(const long double& sigma, const long double& N) {
  if (sigma <= 0.0 || N <= 0.0) return 0.0;
  return sigma * N;
}

long double CCore::calcOpticalPath(const long double& sigma, const long double& N, const unsigned int ds) {
  if (sigma <= 0.0 || N <= 0.0 || ds == 0) return 0.0;
  return sigma * N * ds;
}

long double CCore::calcTrans(const long double& tau) {
  if (tau <= 0.0) return 1.0;
  return exp(-tau);
}

long double CCore::calcTrans(const long double& b, const unsigned int ds) {
  if (b <= 0.0 || ds == 0) return 1.0;
  return exp(-b * ds);
}

long double CCore::calcScatPower(const long double& Io, const long double& sigma) {
  // this function assumes light is scattered in a 90 degree angle
  if (Io <= 0.0 || sigma <= 0.0) return 0.0;
  return constants::I_A * Io * sigma;
}

long double CCore::calcScatInten( const long double& Io,
/*******************************/ const long double& N,
/*******************************/ const long double& sigma,
/*******************************/ const unsigned int dz) {
  if (Io <= 0.0 || N <= 0.0 || sigma <= 0.0 || dz == 0) return 0.0;
  return constants::I_A * Io * N * sigma * dz;
}

long double CCore::calcScatInten(const long double& Io, const long double& b, const unsigned int dz) {
  if (Io <= 0.0 || b <= 0.0 || dz == 0) return 0.0;
  return constants::I_A * Io * b * dz;
}

unsigned long CCore::getSolarFlux() {
  return S;
}

long double CCore::calcBoltzLaw(const double& T) {
  if (T < 0.0) return 0.0;

  long double I = constants::SB * pow (10, -8) * pow(T, 4);
  return I;
}

long double CCore::hypsoPress(const unsigned long long& p_o, const double& T, const int& dz) {
  if (T <= 0) return 0;
  long double val = p_o * exp(-g * dz / (earth::R_d * T));

  return val;
}

void CCore::setEarthT() {
  for (int i = 0; i < NUM_LAYERS_HI; i++) atmos[i].T = earth::T_hi[i];
}

void CCore::setLevs() {
  for (int i = 0; i < NUM_LAYERS_HI; i++) atmos[i].z = earth::z_hi[i];
}

int CCore::getP(const int& i) {
  if (i < 0 || i >= NUM_LAYERS_HI) return 0;
  return atmos[i].p;
}

double CCore::getT_star() {
  return T_star;
}

double CCore::getD_star() {
  return D_star;
}

double CCore::getR_star() {
  return R_star;
}

long CCore::getp_sfc() {
  return p_sfc;
}

long CCore::getT_sfc() {
  return T_sfc;
}

long double CCore::getIntegratedFlux() {
  if (insol.size() <= 0) return 0.0;
  long double F = 0.0;
  for (int i = 0; i < insol.size(); i++) {
    F += insol[i].F;
  }
  return F;
}

std::vector<long double> CCore::getSpectrum(const unsigned int& i_layer) {
  std::vector<long double> I;
  if (i_layer >= NUM_LAYERS_HI) return I;

  for (int i = 0; i < optic.size(); i++) {
    I.push_back(optic[i][i_layer].I_sca_tot);
  }
  return I;
}

std::vector<int> CCore::get_T() {
  std::vector<int> tmp;
  for (int i = 0; i < atmos.size(); i++) {
    tmp.push_back(atmos[i].T);
  }
  return tmp;
}

std::vector<double> CCore::get_vol_N() {
  std::vector<double> tmp;
  for (int i = 0; i < atmos.size(); i++) {
    tmp.push_back(atmos[i].vol_N);
  }
  return tmp;
}

std::vector<double> CCore::get_vol_O() {
  std::vector<double> tmp;
  for (int i = 0; i < atmos.size(); i++) {
    tmp.push_back(atmos[i].vol_O);
  }
  return tmp;
}

std::vector<double> CCore::get_vol_Ar() {
  std::vector<double> tmp;
  for (int i = 0; i < atmos.size(); i++) {
    tmp.push_back(atmos[i].vol_Ar);
  }
  return tmp;
}

void CCore::set_T_star(const double& T) {
  T_star = T;
}

void CCore::set_D_star(const double& D) {
  D_star = D;
}

void CCore::set_R_star(const double& R) {
  R_star = R;
}

void CCore::set_p_sfc(const double& p) {
  p_sfc = p;
}

void CCore::set_T_profile(std::vector<int> const& T) {
  T_sfc = T[0];
  for (int i = 0; i < atmos.size(); i++) {
    atmos[i].T = T[i];
  }
}

void CCore::set_v_profile(std::vector<double> const& N, std::vector<double> const& O, std::vector<double> const& Ar) {
  for (int i = 0; i < atmos.size(); i++) {
    atmos[i].vol_N = N[i];
    atmos[i].vol_O = O[i];
    atmos[i].vol_Ar = Ar[i];
  }
}

// long double CCore::calcCrossCoeff(const unsigned int& lambda, const double& n) {
//   if (n <= 0.0) return 0.0;
//
//   double refr = pow((pow(n, 2.0) - 1.0) / (pow(n, 2.0) + 2.0), 2.0);
//   long double denom = pow(lambda * pow(10.0, -9.0), 4.0) ;
//
//   return constants::Sc_A * refr / denom;
// }
//
