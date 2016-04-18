#ifndef __SIMULUNIF_H_INCLUDED__
#define __SIMULUNIF_H_INCLUDED__
#include <random>
#include <chrono>
class RUnif{
private:
    std::mt19937_64 generator;
    int seed;
    std::uniform_real_distribution<double> unif;//(0.0,1.0);

public:
  RUnif(){
    seed=std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
    //n=n_;
    unif=std::uniform_real_distribution<double>(0.0, 1.0);
  }
  RUnif(int seed){
    generator.seed(seed);
    //n=n_;
    unif=std::uniform_real_distribution<double>(0.0, 1.0);
  }  
  double getUnif(){
    return unif(generator); 
  }

};
#endif