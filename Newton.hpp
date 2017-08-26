Newton::Newton(){

}
Newton::Newton(double prec1, double prec2, double dx_){
  precision1=prec1;
  precision2=prec2;
  dx=dx_;
}
int Newton::getIterations(){
    return k;
}

template<typename OBJFUNC> //one dimension
void Newton::zeros(OBJFUNC&& objective, double &guesses){ //guess is modified and used as the "result"
    double prec2=1;
    AutoDiff guess(guesses, 1);
    int j=0;
    while(std::abs(prec2)>precision2 && j<maxNum){
        prec2=guesses;
        AutoDiff p=objective(guess);
        guesses=guesses-p.getStandard()/p.getDual();
        prec2=(guesses-prec2)/guesses;
        guess.setStandard(guesses);
        guess.setDual(1);
        j++;
    }
}
