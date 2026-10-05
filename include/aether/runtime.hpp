#pragma once
#include "aether/tensor.hpp"
#include <cstdint>
#include <random>
#include <vector>
namespace aether {
struct RuntimeConfig{std::uint32_t seed=42;float temperature=0.8F;};
class Runtime{
 public:
  explicit Runtime(RuntimeConfig={});
  std::uint32_t sample(const std::vector<float>&);
  Tensor linear(const Tensor&,const Tensor&)const;
 private:
  RuntimeConfig config_;std::mt19937 rng_;
};
}
