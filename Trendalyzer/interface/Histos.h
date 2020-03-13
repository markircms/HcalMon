#include "Dataformats.h"
#include "Lmap.h"
/*#include "Histos/Histo2dMDel.C"
#include "Histos/Histo2dMD.C"
#include "Histos/Histo1dMD.C"
#include "Histos/Graph.C"
#include "Histos/Multi.C"
#include "Histos/Zmeyka.C"*/

#include "Histo2dMDel.h"
#include "Histo2dMD.h"
#include "Histo1dMD.h"
#include "Graph.h"
#include "Multi.h"
#include "Zmeyka.h"

#include "Styles.h"

class Histos{

public:
//HBHE

Lmap LMAP;
Graph Gr;

Histos(vector<int> runs, string R, string Lmapfile){
  LMAP = Lmap(Lmapfile);
  Gr = Graph(runs, LMAP);
  bookHistograms(runs, R);
};
Histos(){
  // default constructor
};

//styling

void GraphStyle(TCanvas* c,TGraph* gr,string sub, vector<int> v){
  c->cd();
  string cname = gr->GetTitle();
  c->SetName(cname.c_str());
  c->SetTitle(cname.c_str());
//  c->SetCanvasSize(600, 600);
  string lab;
  gr->Draw("AC*");
  int ndiv = v.size();
  TAxis *a = gr->GetXaxis();
  a-> SetNdivisions(ndiv);
  for (unsigned int i=0;i<v.size();i++){
    lab = to_string(v.at(i));
    a->ChangeLabel(i+1,-1,-1,-1,-1,-1,lab.c_str());
//    refgr->GetXaxis()->SetBinLabel(i+1,lab.c_str());
  };
  //gr->Draw("AC*");
  c->Update();
};

void ZmeykaStyle(TCanvas* c, TH2F* h, string sub, vector<int> v){
  string lab;
  string cname = h->GetTitle();
  c->SetName(cname.c_str());
  c->SetTitle(cname.c_str());
  h->SetStats(0);
  h->SetOption("colz");
  int ndiv = v.size();
  TAxis *a = h->GetXaxis();
  a-> SetNdivisions(ndiv);
  for (unsigned int i=0;i<v.size();i++){
    lab = to_string(v.at(i));
    a->ChangeLabel(i+1,-1,-1,-1,-1,-1,lab.c_str());
  };
  h->Draw();
}

void Histo2dStyle(TCanvas* c,TH2F* h){
  h->SetStats(0);
  h->SetOption("colz");
  h->Draw();
};

void MultiStyle(TCanvas *c,TMultiGraph* mg, vector<int> v){
  string lab;
  string cname = mg->GetTitle();
  c->SetName(cname.c_str());
  c->SetTitle(cname.c_str());
  mg->Draw("AC*");
  int ndiv = v.size();
  TAxis *a = mg->GetXaxis();
  a-> SetNdivisions(ndiv);
  for (unsigned int i=0;i<v.size();i++){
    lab = to_string(v.at(i));
    a->ChangeLabel(i+1,-1,-1,-1,-1,-1,lab.c_str());
  //  refgr->GetXaxis()->SetBinLabel(i+1,lab.c_str());
  };
  c->Update();
}

void GraphStyle4Multi(TGraph* gr,int i, int j){
   gr->SetLineColor((i-minieta+1)*j);
};

// book histograms
private:

TMultiGraph *refMulti;
// reference map for each subdetector

void MakeTitleMulti(TMultiGraph* mg,string name){
  mg->SetTitle(name.c_str());
  mg->SetName(name.c_str());
}

void bookHistograms(vector<int> rv, string Runtype){

      string nameh;

// 1d everything
      if ((Runtype == "HBloled") || (Runtype == "Multiloled")){
        HBhex = true;
        ped = true;
        Gr.AddGr("HB",1);
        Gr.AddGr("HB",2);
        Gr.AddGr("HB",3);
        Histo1dMD("HB", 3,1000,0,10);
        Histo1dMD("HB", 1,1000,0,10);
        Histo1dMD("HB", 2,1000,0,10);
        Histo2dMD("HB", 3);
        Histo2dMD("HB", 1);
        Histo2dMD("HB", 2);
        Histo2dMDel(LMAP, "HB", 3);
        Histo2dMDel(LMAP, "HB", 1);
        Histo2dMDel(LMAP, "HB", 2);
        Multi("HB", 1);
        Multi("HB", 2);
        Multi("HB", 3);
        Zmeyka(rv, "HB", 1);
        Zmeyka(rv, "HB", 2);
        Zmeyka(rv, "HB", 3);
      };
      if ((Runtype == "HEloled") || (Runtype == "Multiloled")) {
        HEhex = true;
        ped = true;
        Gr.AddGr("HE",1);
        Gr.AddGr("HE",2);
        Gr.AddGr("HE",3);
        Histo1dMD("HE", 3,1000,0,10);
        Histo1dMD("HE", 1,1000,0,10);
        Histo1dMD("HE", 2,1000,0,10);
        Histo2dMD("HE", 3);
        Histo2dMD("HE", 1);
        Histo2dMD("HE", 2);
        Histo2dMDel(LMAP, "HE", 3);
        Histo2dMDel(LMAP, "HE", 1);
        Histo2dMDel(LMAP, "HE", 2);
        Multi("HE", 1);
        Multi("HE", 2);
        Multi("HE", 3);
        Zmeyka(rv, "HE", 1);
        Zmeyka(rv, "HE", 2);
        Zmeyka(rv, "HE", 3);
      };
      if ((Runtype == "HBled6") || (Runtype == "Multiled6")){
        HBhex = true;
        Gr.AddGr("HB",1);
        Gr.AddGr("HB",2);
        Histo1dMD("HB", 1,1000,0,20000);
        Histo1dMD("HB", 2,1000,0,20000);
        Histo2dMD("HB", 1);
        Histo2dMD("HB", 2);
        Histo2dMDel(LMAP, "HB", 1);
        Histo2dMDel(LMAP, "HB", 2);
        Multi("HB", 1);
        Multi("HB", 2);
        Zmeyka(rv, "HB", 1);
        Zmeyka(rv, "HB", 2);
      };
      if ((Runtype == "HEled6") || (Runtype == "Multiled6")) {
        HEhex = true;
        Gr.AddGr("HE",1);
        Gr.AddGr("HE",2);
        Histo1dMD("HE", 1,1000,0,200000);
        Histo1dMD("HE", 2,1000,0,20000);
        Histo2dMD("HE", 1);
        Histo2dMD("HE", 2);
        Histo2dMDel(LMAP, "HE", 1);
        Histo2dMDel(LMAP, "HE", 2);
        Multi("HE", 1);
        Multi("HE", 2);
        Zmeyka(rv, "HE", 1);
        Zmeyka(rv, "HE", 2);
      }
      if (Runtype == "Multiled6") {
        HFhex = true;
        Gr.AddGr("HF",1);
        Gr.AddGr("HF",2);
        Histo1dMD("HF", 1,1000,0,200000);
        Histo1dMD("HF", 2,1000,0,20000);
        Histo2dMD("HF", 1);
        Histo2dMD("HF", 2);
        Histo2dMDel(LMAP, "HF", 1);
        Histo2dMDel(LMAP, "HF", 2);
        Multi("HF", 1);
        Multi("HF", 2);
        Zmeyka(rv, "HF", 1);
        Zmeyka(rv, "HF", 2);
      };
      if (Runtype == "Multiled6") {
        HOhex = true;
        Gr.AddGr("HO",1);
        Gr.AddGr("HO",2);
        Histo1dMD("HO", 1,1000,0,200000);
        Histo1dMD("HO", 2,1000,0,20000);
        Histo2dMD("HO", 1);
        Histo2dMD("HO", 2);
        Histo2dMDel(LMAP, "HO", 1);
        Histo2dMDel(LMAP, "HO", 2);
        Multi("HO", 1);
        Multi("HO", 2);
        Zmeyka(rv, "HO", 1);
        Zmeyka(rv, "HO", 2);
      };

      if ((Runtype == "HBled1") || (Runtype == "Multiled1")) {
        HBhex = true;
        Gr.AddGr("HB",1);
        Gr.AddGr("HB",2);
        Histo1dMD("HB", 1,1000,0,200000);
        Histo1dMD("HB", 2,1000,0,20000);
        Histo2dMD("HB", 1);
        Histo2dMD("HB", 2);
        Histo2dMDel(LMAP, "HB", 1);
        Histo2dMDel(LMAP, "HB", 2);
        Multi("HB", 1);
        Multi("HB", 2);
        Zmeyka(rv, "HB", 1);
        Zmeyka(rv, "HB", 2);
      };
      if ((Runtype == "HEled1") || (Runtype == "Multiled1")) {
        HEhex = true;
        Gr.AddGr("HE",1);
        Gr.AddGr("HE",2);
        Histo1dMD("HE", 1,1000,0,200000);
        Histo1dMD("HE", 2,1000,0,20000);
        Histo2dMD("HE", 1);
        Histo2dMD("HE", 2);
        Histo2dMDel(LMAP, "HE", 1);
        Histo2dMDel(LMAP, "HE", 2);
        Multi("HE", 1);
        Multi("HE", 2);
        Zmeyka(rv, "HE", 1);
        Zmeyka(rv, "HE", 2);
      };
      if ((Runtype == "HFled1") || (Runtype == "Multiled1")) {
        HFhex = true;
        Gr.AddGr("HF",1);
        Gr.AddGr("HF",2);
        Histo1dMD("HF", 1,1000,0,200000);
        Histo1dMD("HF", 2,1000,0,20000);
        Histo2dMD("HF", 1);
        Histo2dMD("HF", 2);
        Histo2dMDel(LMAP, "HF", 1);
        Histo2dMDel(LMAP, "HF", 2);
        Multi("HF", 1);
        Multi("HF", 2);
        Zmeyka(rv, "HF", 1);
        Zmeyka(rv, "HF", 2);
      };
      if ((Runtype == "HOled") || (Runtype == "Multiled1")) {
        HOhex = true;
        Gr.AddGr("HO",1);
        Gr.AddGr("HO",2);
        Histo1dMD("HO", 1,1000,0,20000);
        Histo1dMD("HO", 2,1000,0,2000);
        Histo2dMD("HO", 1);
        Histo2dMD("HO", 2);
        Histo2dMDel(LMAP, "HO", 1);
        Histo2dMDel(LMAP, "HO", 2);
        Multi("HO", 1);
        Multi("HO", 2);
        Zmeyka(rv, "HO", 1);
        Zmeyka(rv, "HO", 2);
      };

//   ped runs

      if ((Runtype == "HBped6") || (Runtype == "Multiped6")) {
        HBhex = true;
        Gr.AddGr("HB",1);
        Gr.AddGr("HB",2);
        Histo1dMD("HB", 1,1000,0,10);
        Histo1dMD("HB", 2,1000,0,10);
        Histo2dMD("HB", 1);
        Histo2dMD("HB", 2);
        Histo2dMDel(LMAP, "HB", 1);
        Histo2dMDel(LMAP, "HB", 2);
        Multi("HB", 1);
        Multi("HB", 2);
        Zmeyka(rv, "HB", 1);
        Zmeyka(rv, "HB", 2);
      };
      if ((Runtype == "HEped6") || (Runtype == "Multiped6")) {
        HEhex = true;
        Gr.AddGr("HE",1);
        Gr.AddGr("HE",2);
        Histo1dMD("HE", 1,1000,0,10);
        Histo1dMD("HE", 2,1000,0,10);
        Histo2dMD("HE", 1);
        Histo2dMD("HE", 2);
        Histo2dMDel(LMAP, "HE", 1);
        Histo2dMDel(LMAP, "HE", 2);
        Multi("HE", 1);
        Multi("HE", 2);
        Zmeyka(rv, "HE", 1);
        Zmeyka(rv, "HE", 2);
      }
      if (Runtype == "Multiped6") {
        HFhex = true;
        Gr.AddGr("HF",1);
        Gr.AddGr("HF",2);
        Histo1dMD("HF", 1,1000,0,10);
        Histo1dMD("HF", 2,1000,0,10);
        Histo2dMD("HF", 1);
        Histo2dMD("HF", 2);
        Histo2dMDel(LMAP, "HF", 1);
        Histo2dMDel(LMAP, "HF", 2);
        Multi("HF", 1);
        Multi("HF", 2);
        Zmeyka(rv, "HF", 1);
        Zmeyka(rv, "HF", 2);
      };
      if (Runtype == "Multiped6") {
        HOhex = true;
        Gr.AddGr("HO",1);
        Gr.AddGr("HO",2);
        Histo1dMD("HO", 1,1000,0,10);
        Histo1dMD("HO", 2,1000,0,10);
        Histo2dMD("HO", 1);
        Histo2dMD("HO", 2);
        Histo2dMDel(LMAP, "HO", 1);
        Histo2dMDel(LMAP, "HO", 2);
        Multi("HO", 1);
        Multi("HO", 2);
        Zmeyka(rv, "HO", 1);
        Zmeyka(rv, "HO", 2);
      };

      if ((Runtype == "HBped1") || (Runtype == "Multiped1")) {
        HBhex = true;
        ped = true;
        Gr.AddGr("HB",1);
        Gr.AddGr("HB",2);
        Gr.AddGr("HB",3);
        Histo1dMD("HB", 1,1000,0,10);
        Histo1dMD("HB", 2,1000,0,10);
        Histo1dMD("HB", 3,1000,0,10);
        Histo2dMD("HB", 3);
        Histo2dMD("HB", 1);
        Histo2dMD("HB", 2);
        Histo2dMDel(LMAP, "HB", 3);
        Histo2dMDel(LMAP, "HB", 1);
        Histo2dMDel(LMAP, "HB", 2);
        Multi("HB", 1);
        Multi("HB", 2);
        Multi("HB", 3);
        Zmeyka(rv, "HB", 1);
        Zmeyka(rv, "HB", 2);
        Zmeyka(rv, "HB", 3);
      };
      if ((Runtype == "HEped1") || (Runtype == "Multiped1")) {
        HEhex = true;
        ped = true;
        Gr.AddGr("HE",1);
        Gr.AddGr("HE",2);
        Gr.AddGr("HE",3);
        Histo1dMD("HE", 1,1000,0,10);
        Histo1dMD("HE", 2,1000,0,10);
        Histo1dMD("HE", 3,1000,0,10);
        Histo2dMD("HE", 3);
        Histo2dMD("HE", 1);
        Histo2dMD("HE", 2);
        Histo2dMDel(LMAP, "HE", 3);
        Histo2dMDel(LMAP, "HE", 1);
        Histo2dMDel(LMAP, "HE", 2);
        Multi("HE", 1);
        Multi("HE", 2);
        Multi("HE", 3);
        Zmeyka(rv, "HE", 1);
        Zmeyka(rv, "HE", 2);
        Zmeyka(rv, "HE", 3);
      };
      if ((Runtype == "HFped1") || (Runtype == "Multiped1")) {
        HFhex = true;
        ped = true;
        Gr.AddGr("HF",1);
        Gr.AddGr("HF",2);
        Histo1dMD("HF", 1,1000,0,10);
        Histo1dMD("HF", 2,1000,0,10);
        Histo2dMD("HF", 1);
        Histo2dMD("HF", 2);
        Histo2dMDel(LMAP, "HF", 1);
        Histo2dMDel(LMAP, "HF", 2);
        Multi("HF", 1);
        Multi("HF", 2);
        Zmeyka(rv, "HF", 1);
        Zmeyka(rv, "HF", 2);
      };
      if ((Runtype == "HOped") || (Runtype == "Multiped1")) {
        HOhex = true;
        ped = true;
        Gr.AddGr("HO",1);
        Gr.AddGr("HO",2);
        Histo1dMD("HO", 1,1000,0,20000);
        Histo1dMD("HO", 2,1000,0,2000);
        Histo2dMD("HO", 1);
        Histo2dMD("HO", 2);
        Histo2dMDel(LMAP, "HO", 1);
        Histo2dMDel(LMAP, "HO", 2);
        Multi("HO", 1);
        Multi("HO", 2);
        Zmeyka(rv, "HO", 1);
        Zmeyka(rv, "HO", 2);
      };
      Histo2dMD("All", 1);
      Histo2dMD("All", 2);
      if (ped) Histo2dMD("All",3);
}
};
