#include "aether/runtime.hpp"
#include "aether/tensor.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
int main(){
 aether::Tensor a({2,3}),b({3,2});
 a[0]=1;a[1]=2;a[2]=3;a[3]=4;a[4]=5;a[5]=6;
 b[0]=7;b[1]=8;b[2]=9;b[3]=10;b[4]=11;b[5]=12;
 auto c=aether::matmul(a,b);
 assert(c.shape()==std::vector<std::size_t>({2,2}));
 assert(std::fabs(c[0]-58)<1e-5);assert(std::fabs(c[1]-64)<1e-5);
 assert(std::fabs(c[2]-139)<1e-5);assert(std::fabs(c[3]-154)<1e-5);
 std::cout<<"Aether tests passed\n";
}
