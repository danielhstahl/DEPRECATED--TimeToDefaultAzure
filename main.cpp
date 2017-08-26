#include <cmath>
#include <vector>
#include <iostream>
<<<<<<< HEAD
#include <cfloat>
#include "Newton.h"
#include "RUnif.h"
#include "RNorm.h"
#include "RGamma.h"
=======
#include "Newton.h"
#include "RUnif.h"
#include "RNorm.h"
>>>>>>> de01e4110c8f7db6d2a14471596b93464cf1f880
#include "MC.h"
#include "Histogram.h"

auto pTau=[](double a, double b, double sigma, auto& tau, double lambda){
    auto A=(1-exp(-a*tau))/a;
    auto C=(b-.5*sigma*sigma/(a*a))*(A-tau)-.25*sigma*sigma/a*A*A;
    return exp(-A*lambda+C);
};
<<<<<<< HEAD

auto mgfGamma=[](double a, double b, double u){
    return pow(1+b*u, -a);  
};

=======
auto pCorrelated=[](double intLambda, auto& tau){ //intLambda=\int_0 ^t \lambda(t) dt where \lambda(t) is the solution of an SDE
    return exp(-intLambda*tau);
};
>>>>>>> de01e4110c8f7db6d2a14471596b93464cf1f880
auto lgd=[](double t, double exposure){
    return (1-exp(-t))*exposure;
};
auto revenue=[](double t, double balance, double rate){
    return balance*(exp(rate*t)-1.0);
};
<<<<<<< HEAD

class Generate_Archimedes{
private:
    RUnif rnd;
public:
    template<typename generator, typename simulator, typename callback, typename... args>
    void generate(int m, generator& MGF, simulator& sim, callback& call, args&... arg){
        double simResult=sim();
        double copulaResult=0;
        double u=0;
        for(int i=0; i<m; ++i){
            copulaResult=-log(rnd.getUnif())/simResult;
            u=MGF(copulaResult);
            call(u, arg...);
        }
    }
    template<typename generator, typename simulator, typename callback>
    void generate(int m, generator& MGF, simulator& sim, callback& call){
        double simResult=sim();
        double copulaResult=0;
        double u=0;
        for(int i=0; i<m; ++i){
            copulaResult=-log(rnd.getUnif())/simResult;
            u=MGF(copulaResult);
            call(u);
        }
    }
};
int main(){
    /*Loan specific parameters (can be idiosyncratic) */
    double a=.1;//loan speciif
    double b=.06; //loan specific
    double lambda=.05; //starting point for latent variable
    double sigma=.02;
    double rate=.2;//itnerest rate
    double balance=10000;
    
    /*frailty parameters*/
    double aFrailty=2;
    double bFrailty=2;
   
    /*MC parameters*/
    int n=10000;//number of MC simulations of a portfolio
    RUnif rnd;
    RGamma gmRnd(aFrailty, bFrailty);
    Newton nt;
    Generate_Archimedes copula;
    
    /*Portfolio parameters*/
    int m=10000;//size of portfolio
    double timeHorizon=5;//years
    MC<double> sim(n);
    
    auto simulator=[&](){
        return gmRnd.getGamma();
    };
    auto generator=[&](double cResult){
        return mgfGamma(aFrailty, bFrailty, cResult);
    };
    auto callback=[&](double result, double& pnl){
        double gs=2;
        nt.zeros([&](auto& t){return pTau(a, b, sigma, t, lambda)-result;}, gs); //this can exhibit idiosyncratic a, b, sigma according to http://www.scaillet.ch/risk_mngt/D_SURVIVAL.pdf.  In fact, this can be anything I want it to be.  Doesnt have to have relationship to the frailty variable
        double bal=rnd.getUnif()*balance;
        if(gs<timeHorizon){
            pnl+=revenue(gs, bal, rate)-lgd(gs, bal);
        }
        else{
            pnl+=revenue(timeHorizon, bal, rate);
        }
    };
    auto getT=[&](){
        double pnl=0;
        copula.generate(m, generator, simulator, callback, pnl);
        return pnl;
    };
    sim.simulateDistribution(getT);//runs in parallel
=======
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
>>>>>>> de01e4110c8f7db6d2a14471596b93464cf1f880
    std::vector<double> distribution=sim.getDistribution();
    double min=DBL_MAX; //purposely out of order because actual min and max are found within the function
    double max=DBL_MIN;
    binAndSend(
<<<<<<< HEAD
        [](const auto& res){
=======
        [](auto& res){
>>>>>>> de01e4110c8f7db6d2a14471596b93464cf1f880
            std::cout<<res<<std::endl;
        },
        min,
        max,
        distribution
    );
<<<<<<< HEAD
}


/*auto mgfExp=[](double lambda, auto& t){
    return lambda/(lambda+t);
};
auto simulateExp=[](double lambda, double u){
    return -log(u)/lambda;
};*/

/*auto mgfCIR=[](double a, double b, double sigma, double lambda0, double rho0, auto& t) {
    double alpha=-a;
    double beta=a*b;
    double P=sqrt(alpha*alpha+2*sigma*sigma*rho0);
    double coshP=exp(P*t*.5);
    double sinhP=(coshP-1.0/coshP)*.5*(alpha/P);
    coshP=(coshP+1.0/coshP)*.5;
    return pow(exp(-alpha*t*.5)/(coshP-sinhP), (2*beta)/(sigma*sigma))*exp(-(rho0*lambda0*alpha*sinhP)/(coshP-sinhP));
};

template<typename sim>
double simulateLambda(double a, double b, double sigma, double lambda0, double U, sim* nrm){ 
    double dt=.01;
    int i=0;
    double cumLambda=0;
    while(cumLambda<U){
        cumLambda+=lambda0*dt;
        lambda0=lambda0+a*(b-lambda0)*dt+sigma*sqrt(dt)*nrm->getNorm();
        i++;
    }
    return i*dt;
};*/
=======
}
>>>>>>> de01e4110c8f7db6d2a14471596b93464cf1f880
