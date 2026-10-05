#include "aether/tensor.hpp"
#include <functional>
#include <numeric>
#include <stdexcept>
namespace aether {
Tensor::Tensor(std::vector<std::size_t> shape):shape_(std::move(shape)){
 if(shape_.empty())throw std::invalid_argument("empty tensor shape");
 data_.resize(std::accumulate(shape_.begin(),shape_.end(),std::size_t{1},std::multiplies<std::size_t>{}));
}
Tensor matmul(const Tensor&a,const Tensor&b){
 if(a.shape().size()!=2||b.shape().size()!=2)throw std::invalid_argument("matmul requires rank 2");
 auto m=a.shape()[0],k=a.shape()[1];
 if(k!=b.shape()[0])throw std::invalid_argument("matmul dimension mismatch");
 auto n=b.shape()[1]; Tensor out({m,n});
 for(std::size_t i=0;i<m;++i)for(std::size_t p=0;p<k;++p){float x=a[i*k+p];for(std::size_t j=0;j<n;++j)out[i*n+j]+=x*b[p*n+j];}
 return out;
}
}
