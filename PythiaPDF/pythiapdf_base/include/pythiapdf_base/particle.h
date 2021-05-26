#ifndef PYTHIAPDF_BASE_PARTICLE_H_
#define PYTHIAPDF_BASE_PARTICLE_H_

#include <map>
#include <string>

namespace pythiapdf {
namespace base {
namespace pdg {
enum class PDGCode {
  kDown = 1,
  kUp = 2,
  kStrange = 3,
  kCharm = 4,
  kBeauty = 5,
  kTop = 6,
  kGluon = 21,
  kPhoton = 22,
  kDownBar = -1,
  kUpBar = -2,
  kStrangeBar = -3,
  kCharmBar = -4,
  kBeautyBar = -5,
  kTopBar = -6
};

const std::map<PDGCode, std::string> particle_names = {
    {PDGCode::kDown, "d"},
    {PDGCode::kUp, "u"},
    {PDGCode::kStrange, "s"},
    {PDGCode::kCharm, "c"},
    {PDGCode::kBeauty, "b"},
    {PDGCode::kTop, "t"},
    {PDGCode::kGluon, "g"},
    {PDGCode::kPhoton, "\\gamma"},
    {PDGCode::kDownBar, "dbar"},
    {PDGCode::kUpBar, "ubar"},
    {PDGCode::kStrangeBar, "sbar"},
    {PDGCode::kCharmBar, "cbar"},
    {PDGCode::kBeautyBar, "bbar"},
    {PDGCode::kTopBar, "tbar"},
};

}
}  // namespace base
}  // namespace pythiapdf

#endif //PYTHIAPDF_BASE_PARTICLE_H_