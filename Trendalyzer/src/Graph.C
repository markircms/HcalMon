#include "Trends/Trendalyzer/interface/Graph.h"

Graph::Graph(vector<int> runs, Lmap L){
  Refgr(runs);
  LMAP = L;
};

map<map4gr,TGraph*> Graph::graphs;

void Graph::AddGr(string s, int t){
  string name;
  TGraph *tmph;
  map4gr temp;
  map4refgr tmpref;
  ChCoordPh tmpPh;
  ChCoordEl tmpEl;
  map<ChCoordPh,ChCoordEl>::iterator it;
  if (t == 1){
      for (int i=1;i<maxiphi+1;i++){
        for (int j=1;j<maxieta+1;j++){
          for (int k=1;k<depths["All"]+1;k++){
             tmpPh.ieta = j;
             tmpPh.iphi =i;
             tmpPh.depth = k;
             it = LMAP.MapPhEl.find(tmpPh);
             if(it ==  LMAP.MapPhEl.end()){
               continue;
             };
             tmpEl = LMAP.MapPhEl.at(tmpPh);
             name = s + " means " + "iphi " + to_string(i) + " ieta " + to_string(j) + " depth " + to_string(k) + " RBX " + tmpEl.RBX + " RM " + to_string(tmpEl.RM) + " QIE " + to_string(tmpEl.QIE) +  " QIEch " + to_string(tmpEl.QIEch);
             temp.sub = s;
             temp.type = "mean";
             temp.iphi = i;
             temp.ieta = j;
             temp.depth = k;
             ped? tmpref.runtype ="ped": tmpref.runtype="led";
             tmpref.sub = s;
             tmpref.grtype = temp.type;
             tmph = (TGraph*)mrefgr[tmpref]->Clone();
             MakeTitleGr(tmph,name);
             graphs.insert(pair<map4gr,TGraph*>(temp,tmph));
          };
        };
        for (int j=minieta;j<0;j++){
          for (int k=1;k<depths["All"]+1;k++){
            tmpPh.ieta = j;
            tmpPh.iphi =i;
            tmpPh.depth = k;
            it = LMAP.MapPhEl.find(tmpPh);
            if(it ==  LMAP.MapPhEl.end()){
              continue;
            };
            tmpEl = LMAP.MapPhEl.at(tmpPh);
            name = s + " means " + "iphi " + to_string(i) + " ieta " + to_string(j) + " depth " + to_string(k) + " RBX " + tmpEl.RBX + " RM " + to_string(tmpEl.RM) + " QIE " + to_string(tmpEl.QIE) +  " QIEch " + to_string(tmpEl.QIEch);
            temp.sub = s;
            temp.type = "mean";
            temp.iphi = i;
            temp.ieta = j;
            temp.depth = k;
            ped? tmpref.runtype ="ped": tmpref.runtype="led";
            tmpref.sub = s;
            tmpref.grtype = temp.type;
            tmph = (TGraph*)mrefgr[tmpref]->Clone();
            MakeTitleGr(tmph,name);
            graphs.insert(pair<map4gr,TGraph*>(temp,tmph));
          };
        };
      }
  };
  if (t == 2){
    for (int i=1;i<maxiphi+1;i++){
      for (int j=1;j<maxieta+1;j++){
        for (int k=1;k<depths["All"]+1;k++){
          tmpPh.ieta = j;
          tmpPh.iphi =i;
          tmpPh.depth = k;
          it = LMAP.MapPhEl.find(tmpPh);
          if(it ==  LMAP.MapPhEl.end()){
            continue;
          };
          tmpEl = LMAP.MapPhEl.at(tmpPh);
          name = s + " rms " + "iphi " + to_string(i) + " ieta " + to_string(j) + " depth " + to_string(k) + " RBX " + tmpEl.RBX + " RM " + to_string(tmpEl.RM) + " QIE " + to_string(tmpEl.QIE) +  " QIEch " + to_string(tmpEl.QIEch);
          temp.sub = s;
          temp.type = "rms";
          temp.iphi = i;
          temp.ieta = j;
          temp.depth = k;
          ped? tmpref.runtype ="ped": tmpref.runtype="led";
          tmpref.sub = s;
          tmpref.grtype = temp.type;
          tmph = (TGraph*)mrefgr[tmpref]->Clone();
          MakeTitleGr(tmph,name);
          graphs.insert(pair<map4gr,TGraph*>(temp,tmph));
        };
      };
      for (int j=minieta;j<0;j++){
        for (int k=1;k<depths["All"]+1;k++){
          tmpPh.ieta = j;
          tmpPh.iphi =i;
          tmpPh.depth = k;
          it = LMAP.MapPhEl.find(tmpPh);
          if(it ==  LMAP.MapPhEl.end()){
            continue;
          };
          tmpEl = LMAP.MapPhEl.at(tmpPh);
          name = s + " gain " + "iphi " + to_string(i) + " ieta " + to_string(j) + " depth " + to_string(k) + " RBX " + tmpEl.RBX + " RM " + to_string(tmpEl.RM) + " QIE " + to_string(tmpEl.QIE) +  " QIEch " + to_string(tmpEl.QIEch);
          temp.sub = s;
          temp.type = "rms";
          temp.iphi = i;
          temp.ieta = j;
          temp.depth = k;
          ped? tmpref.runtype ="ped": tmpref.runtype="led";
          tmpref.sub = s;
          tmpref.grtype = temp.type;
          tmph = (TGraph*)mrefgr[tmpref]->Clone();
          MakeTitleGr(tmph,name);
          graphs.insert(pair<map4gr,TGraph*>(temp,tmph));
        };
      };
    }
  };
  if (t == 3){
    for (int i=1;i<maxiphi+1;i++){
      for (int j=1;j<maxieta+1;j++){
        for (int k=1;k<depths["All"]+1;k++){
          tmpPh.ieta = j;
          tmpPh.iphi =i;
          tmpPh.depth = k;
          it = LMAP.MapPhEl.find(tmpPh);
          if(it ==  LMAP.MapPhEl.end()){
            continue;
          };
          tmpEl = LMAP.MapPhEl.at(tmpPh);
          name = s + " means " + "iphi " + to_string(i) + " ieta " + to_string(j) + " depth " + to_string(k) + " RBX " + tmpEl.RBX + " RM " + to_string(tmpEl.RM) + " QIE " + to_string(tmpEl.QIE) +  " QIEch " + to_string(tmpEl.QIEch);
          temp.sub = s;
          temp.type = "gain";
          temp.iphi = i;
          temp.ieta = j;
          temp.depth = k;
          ped? tmpref.runtype ="ped": tmpref.runtype="led";
          tmpref.sub = s;
          tmpref.grtype = temp.type;
          tmph = (TGraph*)mrefgr[tmpref]->Clone();
          MakeTitleGr(tmph,name);
          graphs.insert(pair<map4gr,TGraph*>(temp,tmph));
        };
      };
      for (int j=minieta;j<0;j++){
        for (int k=1;k<depths["All"]+1;k++){
          tmpPh.ieta = j;
          tmpPh.iphi =i;
          tmpPh.depth = k;
          it = LMAP.MapPhEl.find(tmpPh);
          if(it ==  LMAP.MapPhEl.end()){
            continue;
          };
          tmpEl = LMAP.MapPhEl.at(tmpPh);
          name = s + " means " + "iphi " + to_string(i) + " ieta " + to_string(j) + " depth " + to_string(k) + " RBX " + tmpEl.RBX + " RM " + to_string(tmpEl.RM) + " QIE " + to_string(tmpEl.QIE) +  " QIEch " + to_string(tmpEl.QIEch);
          temp.sub = s;
          temp.type = "gain";
          temp.iphi = i;
          temp.ieta = j;
          temp.depth = k;
          ped? tmpref.runtype ="ped": tmpref.runtype="led";
          tmpref.sub = s;
          tmpref.grtype = temp.type;
          tmph = (TGraph*)mrefgr[tmpref]->Clone();
          MakeTitleGr(tmph,name);
          graphs.insert(pair<map4gr,TGraph*>(temp,tmph));
        };
      };
    }
  };
};

void Graph::MakeTitleGr(TGraph* gr,string name){
  gr->SetTitle(name.c_str());
  gr->SetName(name.c_str());
};

void Graph::Refgr(vector<int> v){
    string lab;
    map4refgr tmp;
    TGraph* refgr = new TGraph();
    TGraph* tmpgr;
    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,300000);
    tmp.runtype = "led";
    tmp.sub = "HB";
    tmp.grtype = "mean";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,300000);
    tmp.runtype = "led";
    tmp.sub = "HE";
    tmp.grtype = "mean";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,300);
    tmp.runtype = "ped";
    tmp.sub = "HB";
    tmp.grtype = "mean";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,300);
    tmp.runtype = "ped";
    tmp.sub = "HE";
    tmp.grtype = "mean";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    // rms

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,50000);
    tmp.runtype = "led";
    tmp.sub = "HB";
    tmp.grtype = "rms";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,50000);
    tmp.runtype = "led";
    tmp.sub = "HE";
    tmp.grtype = "rms";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,100);
    tmp.runtype = "ped";
    tmp.sub = "HB";
    tmp.grtype = "rms";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,100);
    tmp.runtype = "ped";
    tmp.sub = "HE";
    tmp.grtype = "rms";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    // gain

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,100);
    tmp.runtype = "ped";
    tmp.sub = "HB";
    tmp.grtype = "gain";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,100);
    tmp.runtype = "ped";
    tmp.sub = "HE";
    tmp.grtype = "gain";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    // HO, HF

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,50000);
    tmp.runtype = "led";
    tmp.sub = "HF";
    tmp.grtype = "rms";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,50000);
    tmp.runtype = "led";
    tmp.sub = "HO";
    tmp.grtype = "rms";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,100);
    tmp.runtype = "ped";
    tmp.sub = "HF";
    tmp.grtype = "rms";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));

    tmpgr = (TGraph*) refgr->Clone();
    tmpgr->GetYaxis()->SetLimits(0,100);
    tmp.runtype = "ped";
    tmp.sub = "HO";
    tmp.grtype = "rms";
    mrefgr.insert(pair<map4refgr,TGraph*>(tmp,tmpgr));
};
