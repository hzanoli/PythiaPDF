#include "pythiapdf_base/pdfplot.h"
#include "boost/program_options.hpp"

namespace po = boost::program_options;
namespace ppb = pythiapdf::base;
namespace pdg = pythiapdf::base::pdg;

int main(int argc, char **argv);

int main(int argc, char **argv) {
  po::options_description options("PythiaPDF options");

  std::string pdf_name;
  double momentum_transfer;

  std::vector<pdg::PDGCode> pdg_codes{
      {pdg::PDGCode::kDown, pdg::PDGCode::kUp, pdg::PDGCode::kStrange,
       pdg::PDGCode::kCharm, pdg::PDGCode::kBeauty, pdg::PDGCode::kTop,
       pdg::PDGCode::kGluon, pdg::PDGCode::kPhoton}};

  options.add_options()("help", "Produce help message.");

  options.add_options()(
      "pdf_name", po::value(&pdf_name)->default_value("Default"),
      "Set the name of the PDF. If none set, uses the default in PYTHIA8.");

  options.add_options()(
      "momentum_transfer", po::value(&momentum_transfer)->default_value(4.),
      "Set the momentum transfer (Q2) used to calculate the PDF plot");

  po::variables_map variables_map;
  po::store(po::parse_command_line(argc, argv, options), variables_map);
  po::notify(variables_map);

  if (variables_map.count("help")) {
    std::cout << options << "\n";
    return 2;
  }
  ppb::RunPDFPlots(pdf_name, momentum_transfer, pdg_codes);

  return 0;
}