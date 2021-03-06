#include "Constants.hh" // Own include

// B0_isSignalAcceptMissingNeutrino is 1.0 only if the whole decay tree is
// correctly reconstructed. It can be 0.0 or NaN (!!!) otherwise.
const TString SignalCondition = "B0_isSignalAcceptMissingNeutrino == 1.0";

// From PDG (2021) and in GeV
// M_D* = 2.01026
// M_D0 = 1.86484
// ΔM   = 0.145426

const TString CommonCuts =
  "TMath::Abs(Dst_M_preFit-2.01026) < 0.1"
  "&& TMath::Abs(D0_M_preFit-1.86484) < 0.1"
  "&& TMath::Abs(massDiffPreFit-0.145426) < 0.005" // Lower cut is not in steering file (for now)
  "&& mu_dr < 2 && TMath::Abs(mu_dz) < 2"
  "&& K_dr < 2 && TMath::Abs(K_dz) < 2"
  "&& pisoft_dr < 2 && TMath::Abs(pisoft_dz) < 2"
  "&& mu_nVXDHits > 0 && K_nVXDHits > 0 && pisoft_nVXDHits > 0" // VXD = PXD+SVD+VTX
  "&& Dst_p_CMS < 2.5"; // From momentum conservation

const TString KpiCuts =
  "pi_dr < 2 && TMath::Abs(pi_dz) < 2"
  "&& pi_nVXDHits > 0";

const TString K3piCuts =
  "pi1_dr < 2 && TMath::Abs(pi1_dz) < 2 && pi1_nVXDHits > 0"
  "&& pi2_dr < 2 && TMath::Abs(pi2_dz) < 2 && pi2_nVXDHits > 0"
  "&& pi3_dr < 2 && TMath::Abs(pi3_dz) < 2 && pi3_nVXDHits > 0";
