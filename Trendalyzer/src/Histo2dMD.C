#include "Trends/Trendalyzer/interface/Histo2dMD.h"

Histo2dMD::Histo2dMD(string subdet, int type){
  Add2d(subdet, type);
};

map<map42D,TH2F*> Histo2dMD::histo2dMD;

void Histo2dMD::Add2d(string s, int t){
  string name;
  TH2F *tmph;
  map42D temp;
  if (t == 1){
    for (int i=1;i<depths["All"]+1;i++){
      name = s + " depth " + to_string(i) + " means max diff";
      tmph = (TH2F*)ref2dph->Clone();
      MakeTitle2d(tmph,name);
      temp.sub = s;
      temp.type = "mean";
      temp.depth = i;
      histo2dMD.insert(std::pair<map42D,TH2F*>(temp,tmph));
    };
  };
  if (t == 2){
    for (int i=1;i<depths["All"]+1;i++){
      name = s + " depth " + to_string(i) + " rms max diff";
      tmph = (TH2F*)ref2dph->Clone();
      MakeTitle2d(tmph,name);
      temp.sub = s;
      temp.type = "rms";
      temp.depth = i;
      histo2dMD.insert(std::pair<map42D,TH2F*>(temp,tmph));
    };
  };
  if (t == 3){
    for (int i=1;i<depths["All"]+1;i++){
      name = s + " depth " + to_string(i) + " gain max diff";
      tmph = (TH2F*)ref2dph->Clone();
      MakeTitle2d(tmph,name);
      temp.sub = s;
      temp.type = "gain";
      temp.depth = i;
      histo2dMD.insert(std::pair<map42D,TH2F*>(temp,tmph));
    };
   };
}


void Histo2dMD::MakeTitle2d(TH2F* h,string name){
  h->SetTitle(name.c_str());
  h->SetName(name.c_str());
}
