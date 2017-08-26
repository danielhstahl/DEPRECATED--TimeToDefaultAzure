#ifndef __SIMULGAMMA_H_INCLUDED__
#define __SIMULGAMMA_H_INCLUDED__
#include <random>
#include <chrono>
class RGamma{
private:
    std::mt19937_64 generator;
    int seed;
    std::gamma_distribution<double> gamma;//(0.0,1.0);

public:
  RGamma(double alpha, double beta){
    seed=std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
    //n=n_;
    gamma=std::gamma_distribution<double>(alpha, beta);
  }
  RGamma(double alpha, double beta, int seed){
    generator.seed(seed);
    //n=n_;
    gamma=std::gamma_distribution<double>(alpha, beta);
  }  
  double getGamma(){
    return gamma(generator); 
  }

};
#endif