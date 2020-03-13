#include "Trends/Trendalyzer/interface/Histo1dMD.h"

Histo1dMD::Histo1dMD(string subdet, int type, int nbins, float left, float right){
  Add1d(subdet, type, nbins, left, right);
};

map<map41D,TH1F*> Histo1dMD::histo1dMD;

void Histo1dMD::Add1d(string s, int t, int nb, float left, float right){
    string name;
    TH1F *tmph;
    map41D temp;
    if (t == 1){
        name = s + " means max diff";
        tmph = new TH1F(name.c_str(), name.c_str(), nb, left, right);
        temp.sub = s;
        temp.type = "mean";
        histo1dMD.insert(std::pair<map41D,TH1F*>(temp,tmph));
    };
    if (t == 2){
        name = s + " rms max diff";
        tmph = new TH1F(name.c_str(), name.c_str(), nb, left, right);
        temp.sub = s;
        temp.type = "rms";
        histo1dMD.insert(std::pair<map41D,TH1F*>(temp,tmph));
    };
    if (t == 3){
        name = s + " gains max diff";
        tmph = new TH1F(name.c_str(), name.c_str(), nb, left, right);
        temp.sub = s;
        temp.type = "gain";
        histo1dMD.insert(pair<map41D,TH1F*>(temp,tmph));
    };
}
