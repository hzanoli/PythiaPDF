#include "pythiapdf_base/pdfplot.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

#include "TFile.h"

namespace ppb = pythiapdf::base;

std::string ppb::PDFPlot::HistogramRootName() const {
  std::stringstream hist_name;
  hist_name << PDFName() << "_" << ParticleName() << "_F_Q2_"
            << MomentumTrasfer();
  return  ScapeSpecialChars(hist_name.str());
}

std::string ppb::PDFPlot::HistogramTitle() const {
  std::stringstream hist_title;
  hist_title << "F^{" << ParticleName() << "} (x, Q2=" << MomentumTrasfer();
  hist_title << " GeV/c)";
  return hist_title.str();
}

ppb::PDFPlot::PDFPlot(const std::string& name, double momentum_transfer,
                      ppb::pdg::PDGCode pdg, bool extrapolate,
                      std::vector<double> bins)
    : pdf_name_(name),
      momentum_transfer_(momentum_transfer),
      extrapolate_(extrapolate),
      pdg_(pdg),
      bins_(bins),
      histogram_(HistogramRootName().c_str(), HistogramTitle().c_str(),
                 bins_.size() - 1, &bins_[0]) {
  Pythia8::Info pythia_info;

  if (PDFName() == "Default") {
    pdf_ = std::make_unique<Pythia8::LHAGrid1>(
        2212, "20", "/usr/share/Pythia8/pdfdata/", &pythia_info);
  } else {
    pdf_ = std::make_unique<Pythia8::LHAPDF>(2212, "LHAPDF6:" + PDFName(),
                                             &pythia_info);
  }
  pdf_->setExtrapolate(Extrapolate());

  const double color_factor{ppb::ColorFactor(PDGCode())};
  const int pdg_int = static_cast<int>(PDGCode());

  // Loop over x values, in a logarithmic scale.
  for (auto x : bins_) {
    const double parton_density = color_factor * pdf_->xf(pdg_int, x, Q2());
    const double parton_density_error = 0;
    
    Histogram().Fill(x, parton_density);
    Histogram().SetBinError(Histogram().GetXaxis()->FindBin(x), parton_density_error);
  }
}

double ppb::ColorFactor(ppb::pdg::PDGCode pdg) {
  if (pdg == ppb::pdg::PDGCode::kGluon) {
    return 9. / 4.;
  }
  return 1.;
}

std::string ppb::ScapeSpecialChars(const std::string& str) {
  std::string scaped{str};

  std::replace(scaped.begin(), scaped.end(), '/', '-');
  std::replace(scaped.begin(), scaped.end(), '\\', '-');

  return scaped;
}

std::vector<ppb::PDFPlot> ppb::MakePDFPlots(
    const std::string& pdf_name, double momentum_transfer,
    const std::vector<ppb::pdg::PDGCode> pdg_codes) {
  std::vector<ppb::PDFPlot> plots;
  plots.reserve(pdg_codes.size());

  for (const ppb::pdg::PDGCode pdg : pdg_codes) {
    plots.emplace_back(pdf_name, momentum_transfer, pdg);
  }

  return plots;
}

void ppb::SavePlots(std::vector<ppb::PDFPlot>& plots) {
  if (plots.empty()) {
    return;
  }

  const auto pdf_name = (*plots.begin()).PDFName();
  const auto momentum_transfer = (*plots.begin()).MomentumTrasfer();

  std::stringstream file_name;

  file_name << "PDF_" << pdf_name << "_Q2_" << momentum_transfer
            << ".root";

  TFile plots_root_file(ScapeSpecialChars(file_name.str()).c_str(), "RECREATE");

  for (ppb::PDFPlot& plot : plots) {
    plot.Histogram().Write();
  }

  plots_root_file.Close();
}

void ppb::RunPDFPlots(const std::string& pdf_name, double momentum_transfer,
                      const std::vector<ppb::pdg::PDGCode>& pdg_codes) {
  std::vector<ppb::PDFPlot> plots =
      MakePDFPlots(pdf_name, momentum_transfer, pdg_codes);

  SavePlots(plots);
}