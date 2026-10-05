#include "aether/runtime.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace aether {
Runtime::Runtime(RuntimeConfig c):config_(c),rng_(c.seed){if(c.temperature<=0)throw std::invalid_argument("temperature must be > 0");}
std::uint32_t Runtime::sample(const std::vector<float>&l){
 if(l.empty())throw std::invalid_argument("empty logits");
 float mx=*std::max_element(l.begin(),l.end()),sum=0;std::vector<float>p(l.size());
 for(std::size_t i=0;i<l.size();++i){p[i]=std::exp((l[i]-mx)/config_.temperature);sum+=p[i];}
 std::uniform_real_distribution<float>d(0,sum);float x=d(rng_);
 for(std::size_t i=0;i<p.size();++i){x-=p[i];if(x<=0)return static_cast<std::uint32_t>(i);}
 return static_cast<std::uint32_t>(p.size()-1);
}
Tensor Runtime::linear(const Tensor&a,const Tensor&w)const{return matmul(a,w);}
}
