#ifndef GLOBALDEFS_H
#define GLOBALDEFS_H

#include "GlobalLibs.hh"

std::map<TString, TString> motherMap = {
  {"B0", "300553"},
  {"pisoft", "413"},
  {"K", "421"},
  {"mu", "511"},
  {"pi", "421"},
  {"pi1", "421"}
};

std::vector<TString> channelList = {"Kpi", "K3pi"};
// std::vector<TString> channelList = {"Kpi"};

std::map<TString, TString> parList =
  {{"mcPT","c_double"},
   {"mcTheta","c_double"},
   {"mcP","c_double"},
   {"mcPhi","c_double"},
   {"pt","c_double"},
   {"p","c_double"},
   {"theta","c_double"},
   {"phi","c_double"},
   {"d0Pull","c_double"},
   {"d0Err","c_double"},
   {"z0Pull","c_double"},
   {"z0Err","c_double"},
   {"mdstIndex","c_double"},
   {"particleSource","c_double"},
   {"dr","c_double"},
   {"dz","c_double"},
   {"nVXDHits","c_double"}
  };

std::map<TString, TString> extraBranches =
  {{"Dst_M_preFit","c_double"},
   {"D0_M_preFit","c_double"},
   {"Dst_p_CMS","c_double"}
  };

std::vector<std::vector<TString>> particleList =
  {{"pisoft", "mu", "K", "pi"},
   {"pisoft", "mu", "K", "pi1","pi2","pi3"}};

std::vector<TString> histoList = {"mcPT", "pt", "mcTheta", "theta"};
std::vector<std::vector<std::vector<Double_t>>> histoBn =
  {{{20,0.,0.25},{20,0.,0.25},{20,0.,TMath::Pi()},{20,0.,TMath::Pi()}}, // pisoft
   {{20,0.,2.5},{20,0.,2.5},{20,0.,TMath::Pi()},{20,0.,TMath::Pi()}}, // mu
   {{20,0.,2.5},{20,0.,2.5},{20,0.,TMath::Pi()},{20,0.,TMath::Pi()}}, // K
   {{20,0.,2.5},{20,0.,2.5},{20,0.,TMath::Pi()},{20,0.,TMath::Pi()}}, // pi/pi1
   {{20,0.,2.5},{20,0.,2.5},{20,0.,TMath::Pi()},{20,0.,TMath::Pi()}}, // pi2
   {{20,0.,2.5},{20,0.,2.5},{20,0.,TMath::Pi()},{20,0.,TMath::Pi()}}}; // pi3

std::vector<std::vector<TString>> particleResoList =
  {{"pisoft", "mu", "K", "pi"},
   {"pisoft", "mu", "K", "pi1"}};
std::vector<std::vector<TString>> histoResoList =
  {{"mcPT","pt"}, {"mcP","p"}, {"mcTheta","theta"}, {"mcPhi","phi"}};
std::vector<std::vector<std::vector<Double_t>>> histoResoBn =
  {{{20,0.,0.25,50,-0.025,0.025},{20,0.,0.25,50,-0.025,0.025},
    {20,0.,TMath::Pi(),50,-0.01,0.01},{20,-TMath::Pi(),TMath::Pi(),50,-0.01,0.01}}, // pisoft
   {{20,0.,2.5,50,-0.025,0.025},{20,0.,2.5,50,-0.025,0.025},
    {20,0.,TMath::Pi(),50,-0.01,0.01},{20,-TMath::Pi(),TMath::Pi(),50,-0.01,0.01}}, // mu
   {{20,0.,2.5,50,-0.025,0.025},{20,0.,2.5,50,-0.025,0.025},
    {20,0.,TMath::Pi(),50,-0.01,0.01},{20,-TMath::Pi(),TMath::Pi(),50,-0.01,0.01}}, // K
   {{20,0.,2.5,50,-0.025,0.025},{20,0.,2.5,50,-0.025,0.025},
    {20,0.,TMath::Pi(),50,-0.01,0.01},{20,-TMath::Pi(),TMath::Pi(),50,-0.01,0.01}}}; // pi

std::vector<std::vector<TString>> particleResoFromPullList =
  {{"pisoft", "mu", "K", "pi"},
   {"pisoft", "mu", "K", "pi1"}};
std::vector<std::vector<TString>> histoResoFromPullList =
  {{"d0Pull","d0Err"}, {"z0Pull","z0Err"}};
std::vector<std::vector<std::vector<Double_t>>> histoResoFromPullBn =
  {{{100,-0.25,0.25},{100,-0.25,0.25}}, // pisoft
   {{100,-0.01,0.01},{100,-0.01,0.01}}, // mu
   {{100,-0.01,0.01},{100,-0.01,0.01}}, // K
   {{100,-0.01,0.01},{100,-0.01,0.01}}}; // pi

const TString CommonCuts =
  "TMath::Abs(Dst_M_preFit-2.01026) < 0.1"
  "&& TMath::Abs(D0_M_preFit-1.86484) < 0.1"
  "&& TMath::Abs(Dst_M_preFit-D0_M_preFit-0.145426) < 0.005" // Lower cut is not in steering file (for now)
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

// namespace selection {
  
//   template <typename T>  
//   int applyCut(TString channel, T getDataVal)// std::function<double(TString)> getDataVal)
//   {
//     // auto getDataVal = std::function{t};
//     int outputVal = 0;
//     if(TMath::Abs(this->*getDataVal("Dst_M_preFit")-2.01026) < 0.1 &&
//        TMath::Abs(getDataVal("D0_M_preFit")-1.86484) < 0.1 &&
//        TMath::Abs(getDataVal("Dst_M_preFit")-getDataVal("D0_M_preFit")-0.145426) < 0.005 && // Lower cut is not in steering file (for now)
//        getDataVal("mu_dr") < 2 &&
//        TMath::Abs(getDataVal("mu_dz")) < 2 &&
//        getDataVal("K_dr") < 2 &&
//        TMath::Abs(getDataVal("K_dz")) < 2 && 
//        getDataVal("pisoft_dr") < 2 && 
//        TMath::Abs(getDataVal("pisoft_dz")) < 2 && 
//        getDataVal("mu_nVXDHits") > 0 &&
//        getDataVal("K_nVXDHits") > 0 &&
//        getDataVal("pisoft_nVXDHits") > 0 && // VXD = PXD+SVD+VTX 
//        getDataVal("Dst_p_CMS") < 2.5) { // From momentum conservation
//       outputVal++;}
    
//     if(channel=="Kpi") {
//       if(getDataVal("pi_dr") < 2 &&
// 	 TMath::Abs(getDataVal("pi_dz")) < 2 &&
// 	 getDataVal("pi_nVXDHits") > 0)  {
// 	outputVal++;}
//     } else if(channel=="K3pi") {
//       if(getDataVal("pi1_dr") < 2 &&
// 	 TMath::Abs(getDataVal("pi1_dz")) < 2 &&
// 	 getDataVal("pi1_nVXDHits") > 0 &&
// 	 getDataVal("pi2_dr") < 2 &&
// 	 TMath::Abs(getDataVal("pi2_dz")) < 2 &&
// 	 getDataVal("pi2_nVXDHits") > 0 &&
// 	 getDataVal("pi3_dr") < 2 &&
// 	 TMath::Abs(getDataVal("pi3_dz")) < 2 && 
// 	 getDataVal("pi3_nVXDHits") > 0)  {
// 	outputVal++;}
//     } else {outputVal = 10;}
    
//     if(outputVal==2) {return 1;}
//     else {return 0;}
//   }; 
// }

#endif
