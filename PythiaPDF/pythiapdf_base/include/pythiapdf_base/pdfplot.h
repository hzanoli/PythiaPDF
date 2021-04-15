#ifndef PYTHIAPDF_BASE_PDFPLOT_H_
#define PYTHIAPDF_BASE_PDFPLOT_H_

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "Pythia8/Pythia.h"
#include "TH1.h"
#include "pythiapdf_base/particle.h"

namespace pythiapdf {
namespace base {

template <typename T>
std::vector<T> LogSpace(T pow_start, T pow_end, int num, T base = T(10.)) {
  const T exp_scale = (pow_end - pow_start) / (num - 1);
  std::vector<T> log_spaced;
  log_spaced.reserve(num);

  for (int i = 0; i < num; i++) {
    log_spaced.push_back(pow_start + i * exp_scale);
  }
  std::for_each(log_spaced.begin(), log_spaced.end(),
                [&base](T& x) { x = pow(base, x); });
  return log_spaced;

}

class PDFPlot {
 private:
  const std::string pdf_name_;
  const double momentum_transfer_;  // Also called Q2
  const bool extrapolate_;
  const pdg::PDGCode pdg_;
  const std::vector<double> bins_;
  TH1D histogram_;
  std::unique_ptr<Pythia8::PDF> pdf_;

  std::string HistogramRootName() const;
  std::string HistogramTitle() const;

 public:
  PDFPlot(const std::string& pdf_name, double momentum_transfer,
          pdg::PDGCode pdg, bool extrapolate = true, std::vector<double> bins = 
          LogSpace<double>(-10, 0, 1000));

  const std::string& PDFName() const { return pdf_name_; };

  double MomentumTrasfer() const { return momentum_transfer_; };

  bool Extrapolate() const { return extrapolate_; };

  double Q2() const { return MomentumTrasfer(); };

  pdg::PDGCode PDGCode() const { return pdg_; };
  std::string ParticleName() const {
    return pdg::particle_names.at(PDGCode());
  };

  TH1D& Histogram() { return histogram_; };
};

double ColorFactor(pdg::PDGCode pdg);

std::vector<PDFPlot> MakePDFPlots(const std::string& pdf_name,
                                  double momentum_transfer,
                                  const std::vector<pdg::PDGCode> pdg_codes);

void SavePlots(const std::string& pdf_name, double momentum_transfer,
               std::vector<PDFPlot>& plots);

void RunPDFPlots(const std::string& pdf_name, double momentum_transfer,
                 const std::vector<pdg::PDGCode>& pdg_codes);
// std::vector<pdg::PDGCode>(
//         {pdg::PDGCode::kDown, pdg::PDGCode::kUp, pdg::PDGCode::kStrange,
//          pdg::PDGCode::kCharm, pdg::PDGCode::kBeauty, pdg::PDGCode::kTop,
//          pdg::PDGCode::kGluon, pdg::PDGCode::kPhoton}
}  // namespace base
}  // namespace pythiapdf

#endif  // PYTHIAPDF_BASE_PDFPLOT_H_