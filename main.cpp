#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <stdexcept>
#include <memory>
#include <string>

using namespace std;

#ifdef WIN32
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
#else
#define GNUPLOT_NAME "gnuplot -persist"
#endif
int main() {
#ifdef WIN32
    FILE* pipe = _popen(GNUPLOT_NAME, "w");
#else
    FILE* pipe = popen(GNUPLOT_NAME, "w");
#endif
    double vZero,kZero,alphaOne,betaOne,alphaTwo,betaTwo,Timing,N;
    vZero=100;
    kZero=40;
    alphaOne=0.4;
    betaOne=0.01;
    alphaTwo=0.6;
    betaTwo=0.008;
    Timing=60;
    N=360;
    double repetition=0;
    vector<double> tt,kk,vv;
    for(int i=0;i<=N;i++){
        tt.push_back(repetition);
        repetition=Timing/N+repetition;
    }
    repetition=0;
    double Nowviv;
    vv.push_back(vZero);
    double kZeromodif= kZero-alphaOne/betaOne;
    vZero=vZero-alphaTwo/betaTwo;
    for(int i=1;i<=N;i++){
        repetition=Timing/N+repetition;
        Nowviv=  vZero * cos(sqrt(alphaOne * alphaTwo)*repetition) - (kZeromodif * sqrt(alphaTwo) * betaOne * sin(sqrt(alphaTwo * alphaOne)* repetition))/(betaTwo*sqrt(alphaOne)) + alphaTwo/betaTwo;
        vv.push_back(Nowviv);
    }
    double nowkik;
    repetition=0;
    for(int i=0; i<=N;i++){
        if(i==0){
            kk.push_back(kZero);
        }else{
            repetition=Timing/N+repetition;
            nowkik=((vZero * sqrt(alphaOne) * betaTwo * sin(sqrt(alphaTwo*alphaOne)*repetition))/(betaOne * sqrt(alphaTwo))) + kZeromodif * cos(sqrt(alphaOne*alphaTwo)*repetition)+ alphaOne/betaOne;
            kk.push_back(nowkik);
        }
    }
    fprintf(pipe, "plot '-' using 1:2 title 'v'");

    for(int i = 0; i <= N; i++){
        double x =kk[i];
        double y =vv[i];
        fprintf(pipe, "%f\t%f\n", x, y);
    }

#ifdef WIN32
    _pclose(pipe);
#else
    pclose(pipe);
#endif
    return 0;
}