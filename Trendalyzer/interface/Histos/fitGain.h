#ifndef __fitfuncs_h
#define __fitfuncs_h

#include "TH1D.h"
#include "TF1.h"
#include "TSpectrum.h"

class GenPoisson{
 public:
  GenPoisson();
  static const int np = 12;
  static double Value(double *y, double *p){
	   double x = y[0];
	   double u0 = p[0];
	   double s0 = p[1];
	   double g = p[2];
	   double sG = p[3];
	   double u = p[4];
	   double lambda = p[5];
     double N = p[6];
	   double value = 0;
	   for (int k=0; k<np+1; k++) {
	      double uk = u + k*lambda;
	      double G = u * pow(uk, k-1) * exp(-uk) / TMath::Factorial(k);
	      double sk2 = s0*s0 + k*sG*sG;
	      double dx = x - u0 - k*g;
	      value += N * G * exp(-0.5*dx*dx/sk2) / sqrt(2*TMath::Pi()) / sqrt(sk2);
	    };
	    return value;
    };
};

struct GenPoisParams{
    static const int np=6;
    static const TString name[np];
    GenPoisParams():gain(0),u0(0),s0(0),sG(0),lambda(0),navg(0){}
    double gain;
    double u0;
    double s0;
    double sG;
    double lambda;
    double navg;
};

const TString GenPoisParams::name[GenPoisParams::np] = {"Gain", "u0", "s0", "sG", "lambda", "navg"};


void fitSPE(TH1D *hin, GenPoisParams &gpp){

    TSpectrum sp(GenPoisson::np);
    int np = sp.Search(hin, 2.0, "goff", 0.02);
    if(np<2) return;

    const double *ax = sp.GetPositionX();
    std::vector<double> vx;
    for(int i=0; i<np; ++i) vx.push_back(ax[i]);
    std::sort(vx.begin(), vx.end());

    double xmin = vx[0] - 20;
    double xmax = vx[0] + GenPoisson::np*(vx[1]-vx[0]);

    TF1 ff("fit", GenPoisson::Value, xmin, xmax, 7);
    ff.SetNpx(1000);

    auto set = [&ff](int i, double v, double e, const char* n){
	    ff.SetParameter(i, v);
	    ff.SetParError(i, e);
	    ff.SetParName(i, n);
    };

    set(0, vx[0], 0.2, "#mu_{0} [fC]");
    set(1, 3.5, 0.2, "#sigma_{0} [fC]");
    set(2, vx[1]-vx[0], 0.1, "g [fC]");
    set(3, 2.5, 0.1, "#sigma_{g} [fC]");
    set(4, (hin->GetMean()-vx[0])/(vx[1]-vx[0]), 0.05, "<n>");
    set(5, 0.2, 0.03, "#lambda");
    set(6, hin->GetEntries()*(hin->GetBinWidth(1)), 100, "NxW [fC]");

    hin->Fit(&ff, "Q0RL");

    TF1 *tf = hin->GetFunction("fit");
    tf->ResetBit(1<<9);
    tf->SetLineWidth(1);

    gpp.u0 = tf->GetParameter(0);
    gpp.s0 = tf->GetParameter(1);
    gpp.gain = tf->GetParameter(2);
    gpp.sG = tf->GetParameter(3);
    gpp.navg = tf->GetParameter(4);
    gpp.lambda = tf->GetParameter(5);
}


#endif
