#pragma once
#include <cstddef>
#include <span>
#include <vector>
namespace aether {
class Tensor {
 public:
  explicit Tensor(std::vector<std::size_t> shape);
  const std::vector<std::size_t>& shape() const noexcept { return shape_; }
  std::size_t size() const noexcept { return data_.size(); }
  float& operator[](std::size_t i){return data_.at(i);}
  const float& operator[](std::size_t i)const{return data_.at(i);}
  std::span<float> values() noexcept{return data_;}
 private:
  std::vector<std::size_t> shape_;
  std::vector<float> data_;
};
Tensor matmul(const Tensor&,const Tensor&);
}
