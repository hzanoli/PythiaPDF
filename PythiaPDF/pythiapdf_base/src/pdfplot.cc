#include "pythiapdf_base/pdfplot.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

#include "TFile.h"

namespace ppb = pythiapdf::base;

std::string ppb::PDFPlot::HistogramRootName() const {
  std::stringstream hist_name;
  hist_name << pdf_name_ << "_" << ParticleName() << "_F_Q2_"
            << std::setprecision(1) << momentum_transfer_;
  return hist_name.str();
}

std::string ppb::PDFPlot::HistogramTitle() const {
  std::stringstream hist_title;
  hist_title << "F^{" << ParticleName() << "} (x, Q2=" << std::setprecision(1)
             << momentum_transfer_;
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
    Histogram().Fill(x, parton_density);
  }
}

double ppb::ColorFactor(ppb::pdg::PDGCode pdg) {
  if (pdg == ppb::pdg::PDGCode::kGluon) {
    return 9. / 4.;
  }
  return 1.;
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

void ppb::SavePlots(const std::string& pdf_name, double momentum_transfer,
                    std::vector<ppb::PDFPlot>& plots) {
  std::stringstream file_name;
  std::string pdf_name_for_file{pdf_name};

  std::replace(pdf_name_for_file.begin(), pdf_name_for_file.end(), '/', '_');

  file_name << "PDF_" << pdf_name_for_file << "_Q2_" << std::setprecision(3)
                 << momentum_transfer << ".root";
  TFile plots_root_file(file_name.str().c_str(), "RECREATE");

  for (ppb::PDFPlot& plot : plots) {
    plot.Histogram().Write();
  }
  plots_root_file.Close();
}

void ppb::RunPDFPlots(const std::string& pdf_name, double momentum_transfer,
                      const std::vector<ppb::pdg::PDGCode>& pdg_codes) {
  std::vector<ppb::PDFPlot> plots =
      MakePDFPlots(pdf_name, momentum_transfer, pdg_codes);
  SavePlots(pdf_name, momentum_transfer, plots);
}