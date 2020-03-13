#include "Trends/Trendalyzer/interface/Zmeyka.h"

Zmeyka::Zmeyka(vector<int> v, string s, int t){
  AddZmeyka(v, s, t);
};

map<map4zmeyka,TH2F*> Zmeyka::zmeyki;

void Zmeyka::AddZmeyka(vector<int> v, string s, int t){
  string name;
  map4zmeyka temp;
  TH2F* tmph;
  float limithisto;
  temp.sub = s;
  if (t == 1){
      for (int i=0;i<NumberofRBXs.at(s);i++){
        temp.RBX = Num2rbx.at(s).at(i);
        temp.type = "mean";
        for (int j=0;j<NumberofRMs.at(s);j++){
            temp.RM = j+1;
            name = s + " means " + "RBX " + temp.RBX + " RM " + to_string(temp.RM);
            if (ped) limithisto = 300.; else limithisto = 300000.;
            tmph = new TH2F("","",v.size(),-0.5,v.size()-0.5,1000,0,limithisto);
  //          if (ped) tmph->GetYaxis()->SetLimits(0,300); else tmph->GetYaxis()->SetLimits(0,300000);
            MakeTitleZmeyka(tmph,name);
            zmeyki.insert(pair<map4zmeyka,TH2F*>(temp,tmph));
        };
      };
  };
  if (t == 2){
    for (int i=0;i<NumberofRBXs.at(s);i++){
      temp.RBX = Num2rbx.at(s).at(i);
      temp.type = "rms";
      for (int j=0;j<NumberofRMs.at(s);j++){
          temp.RM = j+1;
          name = s + " rms " + "RBX " + temp.RBX + " RM " + to_string(temp.RM);
/*        tmph = new TH2F();
          if (ped) tmph->GetYaxis()->SetLimits(0,100); else tmph->GetYaxis()->SetLimits(0,50000);*/
          if (ped) limithisto = 100.; else limithisto = 50000.;
          tmph = new TH2F("","",v.size(),-0.5,v.size()-0.5,1000,0,limithisto);
          MakeTitleZmeyka(tmph,name);
          zmeyki.insert(pair<map4zmeyka,TH2F*>(temp,tmph));
      };
    };
  };
  if (t == 3){
    for (int i=0;i<NumberofRBXs.at(s);i++){
      temp.RBX = Num2rbx.at(s).at(i);
      temp.type = "gain";
      for (int j=0;j<NumberofRMs.at(s);j++){
          temp.RM = j+1;
          name = s + " gain " + "RBX " + temp.RBX + " RM " + to_string(temp.RM);
          limithisto = 100.;
          tmph = new TH2F("","",v.size(),-0.5,v.size()-0.5,1000,0,limithisto);
          MakeTitleZmeyka(tmph,name);
          zmeyki.insert(pair<map4zmeyka,TH2F*>(temp,tmph));
      };
    };
  };
}

void Zmeyka::MakeTitleZmeyka(TH2F* h,string name){
  h->SetTitle(name.c_str());
  h->SetName(name.c_str());
}
