#include "aether/runtime.hpp"
#include <iostream>
int main(){aether::Runtime r({42,0.8F});std::cout<<"Aether CPU runtime MVP\n";std::cout<<"sampled token: "<<r.sample({0.1F,1.8F,0.4F,0.2F})<<"\n";}
