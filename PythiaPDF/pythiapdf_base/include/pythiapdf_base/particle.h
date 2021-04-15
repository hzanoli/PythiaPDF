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
  kPhoton = 22
};

const std::map<PDGCode, std::string> particle_names = {
    {PDGCode::kDown, "d"},
    {PDGCode::kUp, "u"},
    {PDGCode::kStrange, "s"},
    {PDGCode::kCharm, "c"},
    {PDGCode::kBeauty, "b"},
    {PDGCode::kTop, "t"},
    {PDGCode::kGluon, "g"},
    {PDGCode::kPhoton, "\\gamma"}
};

}
}  // namespace base
}  // namespace pythiapdf

#endif //PYTHIAPDF_BASE_PARTICLE_H_