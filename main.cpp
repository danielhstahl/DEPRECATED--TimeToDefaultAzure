#include <cmath>
#include <vector>
#include <iostream>
#include "Newton.h"
#include "RUnif.h"
#include "RNorm.h"
#include "MC.h"
#include "Histogram.h"

auto pTau=[](double a, double b, double sigma, auto& tau, double lambda){
    auto A=(1-exp(-a*tau))/a;
    auto C=(b-.5*sigma*sigma/(a*a))*(A-tau)-.25*sigma*sigma/a*A*A;
    return exp(-A*lambda+C);
};
auto pCorrelated=[](double intLambda, auto& tau){ //intLambda=\int_0 ^t \lambda(t) dt where \lambda(t) is the solution of an SDE
    return exp(-intLambda*tau);
};
auto lgd=[](double t, double exposure){
    return (1-exp(-t))*exposure;
};
auto revenue=[](double t, double balance, double rate){
    return balance*(exp(rate*t)-1.0);
};
/*auto simVas=[](double a, double b, double sigma, double lambda){
    double expect=-((lambda-b)/a)*(1-exp(-a*)) 
};*/

int main(){
    double a=.1;
    double b=.06;
    double lambda=.05; //starting point for latent variable
    double sigma=.03;
    int n=10000;//number of MC simulations of a portfolio
    int m=10000;//size of portfolio
    int k=100;//number of steps for simulating 
    double timeHorizon=1;//years
    double rate=.2;//itnerest rate
    MC<double> sim(n);
    RUnif rnd;
    Newton nt;
    //int numDefaults=0;
    auto getT=[&](){
        double pnl=0;
        for(int i=0;i<m;++i){
            double guess=2;
            double simResult=rnd.getUnif();
            nt.zeros([&](auto& t){return pTau(a, b, sigma, t, lambda)-simResult;}, guess); //solves for the "t" that satisifies F(t)=U where U is the uniform random variable and F is the CDF.  Guess is modified and is the "t" after the solution converges
            double bal=rnd.getUnif()*10000;
            if(guess<timeHorizon){
                pnl+=revenue(guess, bal, rate)-lgd(guess, bal);
                //numDefaults++;
            }
            else{
                pnl+=revenue(timeHorizon, bal, rate);
            }
        }
        return pnl;
    };
    sim.simulateDistribution(getT);//runs in parallel
    //std::cout<<"Number of defaults: "<<numDefaults<<std::endl;
    std::vector<double> distribution=sim.getDistribution();
    double min=DBL_MAX; //purposely out of order because actual min and max are found within the function
    double max=DBL_MIN;
    binAndSend(
        [](auto& res){
            std::cout<<res<<std::endl;
        },
        min,
        max,
        distribution
    );
}