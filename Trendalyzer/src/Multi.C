#include "Trends/Trendalyzer/interface/Multi.h"

Multi::Multi(string s, int t){
  AddMulti(s, t);
};

map<map4multi,TMultiGraph*> Multi::multigraphs;

void Multi::AddMulti(string s, int t){
  string name;
  map4multi temp;
  TMultiGraph* tmph;
  temp.sub = s;
  if (t == 1){
      for (int i=0;i<NumberofRBXs.at(s);i++){
        temp.RBX = Num2rbx.at(s).at(i);
        temp.type = "mean";
        for (int j=0;j<NumberofRMs.at(s);j++){
            temp.RM = j+1;
            name = s + " means " + "RBX " + temp.RBX + " RM " + to_string(temp.RM);
            tmph = new TMultiGraph();
            MakeTitleMulti(tmph,name);
            multigraphs.insert(pair<map4multi,TMultiGraph*>(temp,tmph));
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
          tmph = new TMultiGraph();
          MakeTitleMulti(tmph,name);
          multigraphs.insert(pair<map4multi,TMultiGraph*>(temp,tmph));
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
          tmph = new TMultiGraph();
          MakeTitleMulti(tmph,name);
          multigraphs.insert(pair<map4multi,TMultiGraph*>(temp,tmph));
      };
    };
  };
}

void Multi::MakeTitleMulti(TMultiGraph* mg,string name){
  mg->SetTitle(name.c_str());
  mg->SetName(name.c_str());
}
