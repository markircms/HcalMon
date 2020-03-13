#include "Trends/Trendalyzer/interface/Histo2dMDel.h"

Histo2dMDel::Histo2dMDel(Lmap l, string subdet, int type){
  Add2del(l, subdet, type);
};

map<map42Del,TH2F*> Histo2dMDel::histo2dMDel;

void Histo2dMDel::Add2del(Lmap l, string s, int t){
    string name;
    TH2F *tmph = new TH2F();
    map42Del temp;
    if (t == 1){
        name = s + " " + "means max diff";
        MakeEl2d(tmph,s);
        MakeTitle2d(tmph,name);
        temp.sub = s;
        temp.type = "mean";
        histo2dMDel.insert(std::pair<map42Del,TH2F*>(temp,tmph));
    };
    if (t == 2){
        name = s + " " +  " rms max diff";
        MakeEl2d(tmph,s);
        MakeTitle2d(tmph,name);
        temp.sub = s;
        temp.type = "rms";
        histo2dMDel.insert(std::pair<map42Del,TH2F*>(temp,tmph));
    };
    if (t == 3){
        name = s + " " + " gain max diff";
        MakeEl2d(tmph,s);
        MakeTitle2d(tmph,name);
        temp.sub = s;
        temp.type = "gain";
        histo2dMDel.insert(std::pair<map42Del,TH2F*>(temp,tmph));
     };
}

void Histo2dMDel::MakeEl2d(TH2F *tmph,string s){
  if (s == "HB"){
      tmph->SetBins(NumberofHBrbxs*NumberofHBQIEs+1,-NumberofHBrbxs*NumberofHBQIEs/2-0.5,NumberofHBrbxs*NumberofHBQIEs/2-0.5,NumberofHBrms*NumberofHBQIEchs,0,NumberofHBrms*NumberofHBQIEchs-1);
  };
  if (s == "HE"){
      tmph->SetBins(NumberofHErbxs*NumberofHEQIEs+1,-NumberofHErbxs*NumberofHEQIEs/2-0.5,NumberofHErbxs*NumberofHEQIEs/2-0.5,NumberofHErms*NumberofHEQIEchs,0,NumberofHErms*NumberofHEQIEchs-1);
  };
  if (s == "HF"){
      tmph->SetBins(NumberofHFrbxs*NumberofHFQIEs+1,-NumberofHFrbxs*NumberofHFQIEs/2-0.5,NumberofHFrbxs*NumberofHFQIEs/2-0.5,NumberofHFrms*NumberofHFQIEchs,0,NumberofHFrms*NumberofHFQIEchs-1);
  };
  if (s == "HO"){
      tmph->SetBins(NumberofHOrbxs*NumberofHOQIEs+1,-NumberofHOrbxs*NumberofHOQIEs/2-0.5,NumberofHOrbxs*NumberofHOQIEs/2-0.5,NumberofHOrms*NumberofHOQIEchs,0,NumberofHOrms*NumberofHOQIEchs-1);
  };
};

void Histo2dMDel::MakeTitle2d(TH2F* h,string name){
  h->SetTitle(name.c_str());
  h->SetName(name.c_str());
}
