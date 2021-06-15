#pragma once
#include "PDFCanvas.hh"
#include <TString.h>
#include <ROOT/RDataFrame.hxx>
#include <tuple>
#include <vector>

/** Utility class to make plots where signal and background events are
 * overlayed.
 */
class SigBkgPlotter {
 public:
  typedef ROOT::RDF::RInterface<ROOT::Detail::RDF::RJittedFilter,void> FilterDF;
  typedef ROOT::RDF::RInterface<ROOT::Detail::RDF::RLoopManager,void> DefineDF;
  typedef ROOT::RDF::RResultPtr<TH1D> RRes1D;
  typedef std::tuple<RRes1D,RRes1D> TRRes1D;
  typedef ROOT::RDF::RResultPtr<TH2D> RRes2D;
  typedef std::tuple<RRes2D,RRes2D> TRRes2D;

  SigBkgPlotter() = delete;
  SigBkgPlotter(const SigBkgPlotter&) = delete;
  SigBkgPlotter(SigBkgPlotter&&) = delete;
  SigBkgPlotter& operator=(const SigBkgPlotter&) = delete;
  SigBkgPlotter& operator=(SigBkgPlotter&&) = delete;

  /** Constructor for a SigBkgPlotter that takes data from df, uses sigCond to
   * tell signal from background and prints plots to c.
   */
  SigBkgPlotter(DefineDF& df, TString sigCond, PDFCanvas& c,
                TString namePrefix = "undefined", TString titlePrefix = "Undefined",
                bool normalizeHistos = false)
  : m_sig(df.Filter((const char*)sigCond, "Signal")),
    m_bkg(df.Filter((const char*)("!(" + sigCond + ")"), "Background")),
    m_c(c), m_namePrefix(namePrefix), m_titlePrefix(titlePrefix),
    m_normalizeHistos(normalizeHistos) {}

  /** Constructor for a SigBkgPlotter that takes data from df, uses sigCond to
   * tell signal from background and prints plots to c.
   */
  SigBkgPlotter(FilterDF& df, TString sigCond, PDFCanvas& c,
                TString namePrefix = "undefined", TString titlePrefix = "Undefined",
                bool normalizeHistos = false)
  : m_sig(df.Filter((const char*)sigCond, "Signal")),
    m_bkg(df.Filter((const char*)("!(" + sigCond + ")"), "Background")),
    m_c(c), m_namePrefix(namePrefix), m_titlePrefix(titlePrefix),
    m_normalizeHistos(normalizeHistos) {}

  /** Makes a tuple {sig,bkg} of histograms of the given variable.
   * The tuple is returned and saved to the interal list of plots.
   */
  TRRes1D Histo1D(const char* variable, TString title, int nBins, double xLow, double xUp);

  /** Makes a tuple {sig,bkg} of histograms of the given variable for
   * each of the given particles. In title, $p is replaced with the
   * "title" of the particle (see ParticlesTitles in Constants.hh).
   */
  void Histo1D(std::initializer_list<TString> particles, const char *variable,
               TString title, int nBins, double xLow, double xUp);

  /** Makes a tuple {sig,bkg} of 2D histograms of the given variables.
   * The tuple is returned and saved to the interal list of plots.
   */
  TRRes2D Histo2D(const char* vx, const char* vy, TString title,
                  int xBins, double xLow, double xUp,
                  int yBins, double yLow, double yUp);

  /** Makes a tuple {sig,bkg} of 2D histograms of the given variables
   * for each of the given particles. In title, $p is replaced with the
   * "title" of the particle (see ParticlesTitles in Constants.hh).
   */
  void Histo2D(std::initializer_list<TString> particles,
               const char* vx, const char* vy, TString title,
               int xBins, double xLow, double xUp,
               int yBins, double yLow, double yUp);

  /** Prints all the plots made up to now to the PDF (via the PDFCanvas).
   * The interal list of plots is then cleared unless otherwise specfied.
   */
  void PrintAll(bool clearInteralList = true);

  TString GetNamePrefix() const { return m_namePrefix; }
  void SetNamePrefix(TString namePrefix) { m_namePrefix = namePrefix; }

  TString GetTitlePrefix() const { return m_titlePrefix; }
  void SetTitlePrefix(TString titlePrefix) { m_titlePrefix = titlePrefix; }

  bool GetNormalizeHistos() const { return m_normalizeHistos; }
  void SetNormalizeHistos(bool value) { m_normalizeHistos = value; }

  bool HasVTX() { return m_sig.HasColumn("nVTXHits"); }

 private:
  /** Prints a signal and a background histograms to PDF. */
  void DrawSigBkg(TH1* sig, TH1* bkg);

  /** Prints a signal and a background histograms to PDF. */
  inline void DrawSigBkg(RRes1D sig, RRes1D bkg) { DrawSigBkg(sig.GetPtr(), bkg.GetPtr()); }

  /** Print a {sig,bkg} histograms tuple to PDF. */
  inline void DrawSigBkg(TRRes1D tuple) { DrawSigBkg(std::get<0>(tuple), std::get<1>(tuple)); }

  /** Prints a signal and a background histograms to PDF. */
  inline void DrawSigBkg(RRes2D sig, RRes2D bkg) { DrawSigBkg(sig.GetPtr(), bkg.GetPtr()); }

  /** Print a {sig,bkg} histograms tuple to PDF. */
  inline void DrawSigBkg(TRRes2D tuple) { DrawSigBkg(std::get<0>(tuple), std::get<1>(tuple)); }

  FilterDF m_sig; /**< Signal dataframe. */
  FilterDF m_bkg; /**< Background dataframe. */
  PDFCanvas& m_c; /**< The output canvas. */
  std::vector<TRRes1D> m_h1s; /**< 1D histograms go here. */
  std::vector<TRRes2D> m_h2s; /**< 1D histograms go here. */
  TString m_namePrefix; /**< Prefix for the name of the histograms. */
  TString m_titlePrefix; /**< Prefix for the title of the histograms. */
  bool m_normalizeHistos; /**< Used by DrawSigBkg to decide wether to normalize histograms. */
};
