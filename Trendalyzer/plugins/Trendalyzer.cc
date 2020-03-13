// -*- C++ -*-
//
// Package:    Trends/Trendalyzer
// Class:      Trendalyzer
//
/**\class Trendalyzer Trendalyzer.cc Trends/Trendalyzer/plugins/Trendalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Martin Kirakosyan
//         Created:  Fri, 08 Nov 2019 13:05:32 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/global/OutputModule.h"
#include "FWCore/Framework/interface/one/OutputModule.h"
#include "FWCore/Framework/interface/RunForOutput.h"

#include "FWCore/Framework/interface/EventForOutput.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"

 #include <vector>
 #include <exception>
 #include <iostream>
 #include <stdlib.h>
 #include <fstream>
 #include <string>
 #include <cstdio>
 #include <map>
 #include <sstream>

 #include <sys/types.h>
 #include <dirent.h>

 #include "TStyle.h"
 #include "TFile.h"
 #include "TTree.h"
 #include "TMath.h"
 #include "TF1.h"
 #include "TH2.h"
 #include "TH1F.h"
 #include "TH2F.h"
 #include "TH2C.h"
 #include "TProfile.h"
 #include "TCanvas.h"
 #include "TLatex.h"
 #include "TColor.h"

#include "Trends/Trendalyzer/interface/Dataformats.h"
#include "Trends/Trendalyzer/interface/Lmap.h"
#include "Trends/Trendalyzer/interface/ParTrends.h"
#include "Trends/Trendalyzer/interface/Histos.h"


class Trendalyzer : public edm::one::OutputModule<> {
   public:
      explicit Trendalyzer(const edm::ParameterSet&);
      ~Trendalyzer() override;

   private:
      TTree *sourceTree;
      TTree *provTree;
      TFile *fileinput;
      TFile *fileoutput;
      RunData rundata;
      ChannelData HcalLoc;
      string Runtype;
      string Lmapinput;
      vector<int> Runsvector;
      Histos hist;
      map<ChCoord,ChData> ChannelTrends;
//      virtual void beginJob() override;
      void endJob() override;
      void beginJob(string Runtype, vector<int> runs);

      void write(edm::EventForOutput const& e) override {};
      void writeLuminosityBlock(edm::LuminosityBlockForOutput const&) override {};
      void writeRun(edm::RunForOutput const&) override {};

      void ReadDataTree(TFile *fileinput);

      void ReadProv(TFile *fileinput);
      void openSource(string Runtype, string name);
      int RunPos(int r, vector<int> Runsvector);
      void Setbin2del(TH2F* h,map42Del tm,ChCoordEl elc,float diff);
      void FillHistos(string Runtype,vector<int> Runsvector);
      void AddTrend2Channels(int Run);
      void WriteHistograms(TFile* fileoutput);
};


Trendalyzer::Trendalyzer(const edm::ParameterSet& iConfig):
  edm::one::OutputModuleBase::OutputModuleBase(iConfig),
  edm::one::OutputModule<>(iConfig),
  Runtype(iConfig.getUntrackedParameter<string>("Runtype")),
  Lmapinput(iConfig.getUntrackedParameter<string>("Lmapinput")),
  Runsvector(iConfig.getUntrackedParameter<vector<int>>("Runsvector"))
{
   //now do what ever initialization is needed

}


Trendalyzer::~Trendalyzer()
{

}

void Trendalyzer::ReadDataTree(TFile *fileinput){
  sourceTree = (TTree*)fileinput->Get("DataTree");
  if (!(sourceTree)) {
    return;
  };
  sourceTree->SetBranchAddress("subd", &(HcalLoc.sub));
  sourceTree->SetBranchAddress("ieta", &(HcalLoc.ieta));
  sourceTree->SetBranchAddress("iphi", &(HcalLoc.iphi));
  sourceTree->SetBranchAddress("depth", &(HcalLoc.depth));
  sourceTree->SetBranchAddress("mean", &(HcalLoc.mean));
  sourceTree->SetBranchAddress("rms", &(HcalLoc.rms));
  sourceTree->SetBranchAddress("maxsignalTS", &(HcalLoc.maxsignalTS));
  sourceTree->SetBranchAddress("gain", &(HcalLoc.gain));
// electronic coordinates

  sourceTree->SetBranchAddress("RBX", &(HcalLoc.RBX));
  sourceTree->SetBranchAddress("RM", &(HcalLoc.RM));
  sourceTree->SetBranchAddress("QIE", &(HcalLoc.QIE));
  sourceTree->SetBranchAddress("QIEch", &(HcalLoc.QIEch));
  sourceTree->SetBranchAddress("BVch", &(HcalLoc.BVch));
  sourceTree->SetBranchAddress("MBch", &(HcalLoc.MBch));

// histograms
//   sourceTree->SetBranchAddress("PulseHisto", &(HcalLoc.histoPulse));
//   sourceTree->SetBranchAddress("PSHisto", &(HcalLoc.graphPS));
};

void Trendalyzer::ReadProv(TFile *fileinput){
  provTree = (TTree*)fileinput->Get("ProvTree");
  if (!(provTree)) return;
  provTree->SetBranchAddress("time", &(rundata.time));
  provTree->SetBranchAddress("runnumber", &(rundata.runnumber));
};

void Trendalyzer::openSource(string Runtype, string name){
  string filename = prefix + Runtype + "/" + name;
  fileinput = new TFile(filename.c_str());
};

int Trendalyzer::RunPos(int r, vector<int> Runsvector){
  for (unsigned int i = 0;i<Runsvector.size();i++){
    if (Runsvector.at(i)==r) {
      return i;
    };
  };
  cout << "run " << r << " not in list of runs" << endl;
  return -1;
};

void Trendalyzer::AddTrend2Channels(int Run){
  ChCoord tmpc;
  ChData tmpd;
  Int_t nentries = (Int_t) sourceTree->GetEntries();
  cout << nentries << endl;
  for (int i = 0; i<nentries;i++){
    sourceTree -> GetEntry(i);
    tmpc.run = Run;
    tmpc.ieta = HcalLoc.ieta;
    tmpc.iphi = HcalLoc.iphi;
    tmpc.depth = HcalLoc.depth;
    tmpc.sub = HcalLoc.sub;
    tmpd.mean = HcalLoc.mean;
    tmpd.rms = HcalLoc.rms;
    tmpd.gain = HcalLoc.gain;
    tmpd.maxsignalTS = HcalLoc.maxsignalTS;
    tmpd.RBX =  *HcalLoc.RBX;
    tmpd.RM =  HcalLoc.RM;
    tmpd.QIE = HcalLoc.QIE;
    tmpd.QIEch =  HcalLoc.QIEch;
    tmpd.BVch =  HcalLoc.BVch;
    tmpd.MBch =  HcalLoc.MBch;
    ChannelTrends.insert(pair<ChCoord,ChData>(tmpc,tmpd));
  };
};

void Trendalyzer::Setbin2del(TH2F* h,map42Del tm,ChCoordEl elc,float diff){
  int rbx;
  if (tm.sub == "HB"){
    rbx = HBrbxs.at(elc.RBX);
    h->SetBinContent(rbx*NumberofHBQIEs + elc.QIE,elc.RM*NumberofHBQIEchs+elc.QIEch,diff);
  }
  if (tm.sub == "HF"){
    rbx = HFrbxs.at(elc.RBX);
    h->SetBinContent(rbx*NumberofHFQIEs + HFQIEs.at(elc.QIE) , elc.QIEch ,diff);
  }
  if (tm.sub == "HE"){
    rbx = HErbxs.at(elc.RBX);
    h->SetBinContent(rbx*NumberofHEQIEs + elc.QIE,elc.RM*NumberofHEQIEchs+elc.QIEch,diff);
  }
  if (tm.sub == "HO"){
    rbx = HOrbxs.at(elc.RBX);
    h->SetBinContent(rbx*NumberofHOQIEs + elc.QIE,elc.RM*NumberofHOQIEchs+elc.QIEch,diff);
  }
};


void Trendalyzer::FillHistos(string Runtype,vector<int> Runsvector){
  float gainsmdiff, meansmdiff, rmssmdiff;
  map41D tmp;
  map42D tmp2d;
  map42Del tmp2del;
  map4gr tmpgr;
  map4multi tmpmulti;
  map4zmeyka tmpzmeyki;
  int NofR;
//    fill graphs
  for (map<ChCoord,ChData>::iterator it = ChannelTrends.begin();it!=ChannelTrends.end();it++){
        NofR = RunPos(it->first.run, Runsvector);
        tmpgr.ieta = it->first.ieta;
        tmpgr.iphi = it->first.iphi;
        tmpgr.depth = it->first.depth;
        tmpgr.sub = HcalSub[it->first.sub];
        tmpgr.type = "mean";
        tmpzmeyki.sub = tmpgr.sub;
        tmpzmeyki.type = tmpgr.type;
        tmpzmeyki.RBX =  it->second.RBX;
        tmpzmeyki.RM =  it->second.RM;
      if ( !(Graph::graphs.find(tmpgr) == Graph::graphs.end()) ) {
          Graph::graphs.at(tmpgr)->SetPoint(NofR,NofR,it->second.mean);
          Zmeyka::zmeyki.at(tmpzmeyki)->Fill(NofR,it->second.mean);
        };
        tmpgr.type = "rms";
        tmpzmeyki.type = tmpgr.type;
      if ( !(Graph::graphs.find(tmpgr) == Graph::graphs.end()) ){
        Graph::graphs[tmpgr]->SetPoint(NofR,NofR,it->second.rms);
        Zmeyka::zmeyki.at(tmpzmeyki)->Fill(NofR,it->second.rms);
      }
        tmpgr.type = "gain";
        tmpzmeyki.type = tmpgr.type;
      if ( !(Graph::graphs.find(tmpgr) == Graph::graphs.end()) ) {
        Graph::graphs[tmpgr]->SetPoint(NofR,NofR,it->second.gain);
        Zmeyka::zmeyki.at(tmpzmeyki)->Fill(NofR,it->second.gain);
      }
  };

// fill histogram
  double *yaxis;
  int narr;
  for (map<ChCoord,ChData>::iterator it = ChannelTrends.begin();it!=ChannelTrends.end();it++){
        TGraph *tmpgraph;
        ChCoordEl elcoord;
        tmpgr.ieta = it->first.ieta;
        tmpgr.iphi = it->first.iphi;
        tmpgr.depth = it->first.depth;
        tmpgr.sub = HcalSub[it->first.sub];
        tmpgr.type = "mean";
        tmp.sub = tmpgr.sub;
        tmp2d.sub = tmpgr.sub;
        tmp2d.depth = tmpgr.depth;
        tmpmulti.sub = tmpgr.sub;
        tmp2del.sub = tmpgr.sub;
        elcoord.sub = tmpgr.sub;
        // derefference pointer
        elcoord.RBX = it->second.RBX;
        elcoord.RM = it->second.RM;
        tmpmulti.RBX = elcoord.RBX;
        (tmp.sub != "HF")? tmpmulti.RM = elcoord.RM: tmpmulti.RM = 1;
        elcoord.QIE = it->second.QIE;
        elcoord.QIEch = it->second.QIEch;
        elcoord.BVch = it->second.BVch;
        elcoord.MBch = it->second.MBch;
        if ( !(Graph::graphs.find(tmpgr) == Graph::graphs.end()) ){
          tmp.type = "mean";
          tmp2d.type ="mean";
          tmpmulti.type = "mean";
          tmp2del.type = tmpmulti.type;
          yaxis = Graph::graphs.at(tmpgr)->GetY();
          narr = Graph::graphs.at(tmpgr)->GetN();
          if (yaxis){
            meansmdiff = *max_element(yaxis,yaxis + narr) -*min_element(yaxis,yaxis + narr);
            Histo1dMD::histo1dMD.at(tmp)->Fill(meansmdiff);
            Histo2dMD::histo2dMD.at(tmp2d)->SetBinContent(tmpgr.ieta-minieta+1,tmpgr.iphi,meansmdiff);
            Setbin2del(Histo2dMDel::histo2dMDel.at(tmp2del),tmp2del,elcoord,meansmdiff);
            tmpgraph = (TGraph*)Graph::graphs.at(tmpgr)->Clone();
            hist.GraphStyle4Multi(tmpgraph,tmpgr.ieta,tmpgr.depth);
            Multi::multigraphs.at(tmpmulti)->Add(tmpgraph);
            tmp2d.sub = "All";
            Histo2dMD::histo2dMD.at(tmp2d)->SetBinContent(tmpgr.ieta-minieta+1,tmpgr.iphi,meansmdiff);
          };
        };
        tmpgr.type = "rms";
      if ( !(Graph::graphs.find(tmpgr) == Graph::graphs.end()) ){
          tmp.type = "rms";
          tmp2d.type = "rms";
          tmp2d.sub = tmpgr.sub;
          tmpmulti.type = "rms";
          tmp2del.type = tmpmulti.type;
          yaxis = Graph::graphs.at(tmpgr)->GetY();
          narr = Graph::graphs.at(tmpgr)->GetN();
          if (yaxis){
            rmssmdiff = *max_element(yaxis,yaxis + narr) -*min_element(yaxis,yaxis + narr);
            Histo1dMD::histo1dMD.at(tmp)->Fill(rmssmdiff);
            Histo2dMD::histo2dMD.at(tmp2d)->SetBinContent(tmpgr.ieta-minieta+1,tmpgr.iphi,rmssmdiff);
            Setbin2del(Histo2dMDel::histo2dMDel.at(tmp2del),tmp2del,elcoord,rmssmdiff);
            tmpgraph = (TGraph*)Graph::graphs.at(tmpgr)->Clone();
            hist.GraphStyle4Multi(tmpgraph,tmpgr.ieta,tmpgr.depth);
            Multi::multigraphs.at(tmpmulti)->Add(tmpgraph);
            tmp2d.sub = "All";
            Histo2dMD::histo2dMD.at(tmp2d)->SetBinContent(tmpgr.ieta-minieta+1,tmpgr.iphi,rmssmdiff);
          };
        };
        tmpgr.type = "gain";
      if ( !(Graph::graphs.find(tmpgr) == Graph::graphs.end()) ){
          tmp.type = "gain";
          tmp2d.type = "gain";
          tmp2d.sub = tmpgr.sub;    
          tmpmulti.type = "gain";
          tmp2del.type = tmpmulti.type;
          yaxis = Graph::graphs.at(tmpgr)->GetY();
          narr = Graph::graphs.at(tmpgr)->GetN();
          if (yaxis){
            gainsmdiff = *max_element(yaxis,yaxis + narr) -*min_element(yaxis,yaxis + narr);
            Histo1dMD::histo1dMD.at(tmp)->Fill(gainsmdiff);
            Histo2dMD::histo2dMD.at(tmp2d)->SetBinContent(tmpgr.ieta-minieta+1,tmpgr.iphi,gainsmdiff);
            Setbin2del(Histo2dMDel::histo2dMDel.at(tmp2del),tmp2del,elcoord,gainsmdiff);
            tmpgraph = (TGraph*)Graph::graphs.at(tmpgr)->Clone();
            hist.GraphStyle4Multi(tmpgraph,tmpgr.ieta,tmpgr.depth);
            Multi::multigraphs.at(tmpmulti)->Add(tmpgraph);
            tmp2d.sub = "All";
            Histo2dMD::histo2dMD.at(tmp2d)->SetBinContent(tmpgr.ieta-minieta+1,tmpgr.iphi,gainsmdiff);
          };
      };
   };
}

void Trendalyzer::WriteHistograms(TFile* fileoutput){
  fileoutput->cd();
  TDirectory *dirhisto1d = fileoutput -> mkdir("Histo1d");
  dirhisto1d->cd();
  TDirectory *dirHB = dirhisto1d -> mkdir("HB");
  dirHB->cd();
// write 1d histograms
  for (map<map41D,TH1F*>::iterator it = Histo1dMD::histo1dMD.begin();it!=Histo1dMD::histo1dMD.end();it++){
    if (it->first.sub == "HB") it->second->Write();
  };
  fileoutput->cd();

//  write graphs
  TDirectory *dirgr = fileoutput->mkdir("Graphs");
  dirgr->cd();
  TDirectory *grHB = dirgr -> mkdir("HB");
  grHB->cd();
  TDirectory *grHBmeans = grHB -> mkdir("Mean");
  grHBmeans->cd();
  TCanvas *cgr;
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HB") {
      if (it->first.type == "mean"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);//new TCanvas();
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
  //          cgr->Draw();
            cgr->Write();
            delete cgr;
        }
      };
    };
  }
  dirHB->cd();
  TDirectory *grHBrms = grHB -> mkdir("RMS");
  grHBrms->cd();
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HB") {
      if (it->first.type == "rms"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);//  cgr = new TCanvas();
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
            cgr->Draw();
            cgr->Write();
            delete cgr;
        }
      };
    };
  }
  dirHB->cd();
  TDirectory *grHBgain = grHB -> mkdir("Gain");
  grHBgain->cd();
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HB") {
      if (it->first.type == "gain"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);//new TCanvas();
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
            cgr->Draw();
            cgr->Write();
            delete cgr;
        };
      };
    };
  }

// HE
  dirhisto1d->cd();
  TDirectory *dirHE = dirhisto1d -> mkdir("HE");
  dirHE->cd();
// write 1d histograms
  for (map<map41D,TH1F*>::iterator it = Histo1dMD::histo1dMD.begin();it!=Histo1dMD::histo1dMD.end();it++){
    if (it->first.sub == "HE") it->second->Write();
  };
  dirgr->cd();
  TDirectory *grHE = dirgr -> mkdir("HE");
  grHE->cd();
  TDirectory *grHEmeans = grHE -> mkdir("Mean");
  grHEmeans->cd();
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HE") {
      if (it->first.type == "mean"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
            cgr->Draw();
            cgr->Write();
            delete cgr;
        }
      };
    };
  }
  dirHE->cd();
  TDirectory *grHErms = grHE -> mkdir("RMS");
  grHErms->cd();
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HE") {
      if (it->first.type == "rms"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);//cgr = new TCanvas();
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
            cgr->Draw();
            cgr->Write();
            delete cgr;
        }
      };
    };
  }
  dirHE->cd();
  TDirectory *grHEgain = grHE -> mkdir("Gain");
  grHEgain->cd();
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HE") {
      if (it->first.type == "gain"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);//cgr = new TCanvas();
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
            cgr->Draw();
            cgr->Write();
            delete cgr;
        }
      };
    };
  }
// HF
  dirhisto1d->cd();
  TDirectory *dirHF = dirhisto1d -> mkdir("HF");
  dirHF->cd();
// write 1d histograms
  for (map<map41D,TH1F*>::iterator it = Histo1dMD::histo1dMD.begin();it!=Histo1dMD::histo1dMD.end();it++){
    if (it->first.sub == "HF") it ->second->Write();
  };
  dirgr->cd();
  TDirectory *grHF = dirgr -> mkdir("HF");
  grHF->cd();
  TDirectory *grHFmeans = grHF -> mkdir("Mean");
  grHFmeans->cd();
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HF") {
      if (it->first.type == "mean"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);//cgr = new TCanvas();
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
            cgr->Draw();
            cgr->Write();
            delete cgr;
        };
      };
    };
  }
  dirHF->cd();
  TDirectory *grHFrms = grHF -> mkdir("RMS");
  grHFrms->cd();
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HF") {
      if (it->first.type == "rms"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);//cgr = new TCanvas();
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
            cgr->Draw();
            cgr->Write();
            delete cgr;
        }
      };
    };
  }
  dirHF->cd();
  TDirectory *grHFgain = grHF -> mkdir("Gain");
  grHFgain->cd();
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HF") {
      if (it->first.type == "gain"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);//cgr = new TCanvas();
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
            cgr->Draw();
            cgr->Write();
            delete cgr;
        };
      };
    };
  }
// HO
  dirhisto1d->cd();
  TDirectory *dirHO = dirhisto1d -> mkdir("HO");
  dirHO->cd();
// write 1d histograms
  for (map<map41D,TH1F*>::iterator it = Histo1dMD::histo1dMD.begin();it!=Histo1dMD::histo1dMD.end();it++){
    if (it->first.sub == "HO") it ->second->Write();
  };
  dirgr->cd();
  TDirectory *grHO = dirgr -> mkdir("HO");
  grHO->cd();
  TDirectory *grHOmeans = grHO -> mkdir("Mean");
  grHOmeans->cd();
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HO") {
      if (it->first.type == "mean"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);//cgr = new TCanvas();
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
            cgr->Draw();
            cgr->Write();
            delete cgr;
        };
      };
    };
  }
  dirHO->cd();
  TDirectory *grHOrms = grHO -> mkdir("RMS");
  grHOrms->cd();
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HO") {
      if (it->first.type == "rms"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);//cgr = new TCanvas();
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
            cgr->Draw();
            cgr->Write();
            delete cgr;
        }
      };
    };
  }
  dirHO->cd();
  TDirectory *grHOgain = grHO -> mkdir("Gain");
  grHOgain->cd();
  for (map<map4gr,TGraph*>::iterator it = Graph::graphs.begin();it!=Graph::graphs.end();it++){
    if (it->first.sub == "HO") {
      if (it->first.type == "gain"){
        if (it->second->GetN()>0){
            cgr = new TCanvas("","",200,10,500,300);//cgr = new TCanvas();
            hist.GraphStyle(cgr,it->second,it->first.sub, Runsvector);
            cgr->Draw();
            cgr->Write();
            delete cgr;
        };
      };
    };
  }
  fileoutput->cd();
  TDirectory *dirhisto2d = fileoutput -> mkdir("Histo2d");
  dirhisto2d->cd();
  TDirectory *dirHB2d = dirhisto2d -> mkdir("HB");
  dirHB2d->cd();
  TDirectory *dirmean2dHB = dirHB2d -> mkdir("Mean");
  dirmean2dHB->cd();
// write 2d histograms
  TCanvas *ch2d;
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "HB"){
      if (it->first.type == "mean"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        if (it->second->GetSumOfWeights()) ch2d->Write();
        delete ch2d;
      };
    };
  };
  dirHB2d->cd();
  TDirectory *dirrms2dHB = dirHB2d -> mkdir("RMS");
  dirrms2dHB->cd();
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "HB"){
      if (it->first.type == "rms"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        if (it->second->GetSumOfWeights()) ch2d->Write();
        delete ch2d;
      };
    };
  };
  dirHB2d->cd();
  TDirectory *dirgain2dHB = dirHB2d -> mkdir("Gain");
  dirgain2dHB->cd();
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "HB"){
      if (it->first.type == "gain"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        if (it->second->GetSumOfWeights()) ch2d->Write();
        delete ch2d;
      };
    };
  };

  dirhisto2d->cd();
  TDirectory *dirHE2d = dirhisto2d -> mkdir("HE");
  dirHE2d->cd();
  TDirectory *dirmean2dHE = dirHE2d-> mkdir("Mean");
  dirmean2dHE->cd();
// write 2d histograms
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "HE"){
      if (it->first.type == "mean"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        if (it->second->GetSumOfWeights()) ch2d->Write();
        delete ch2d;
      };
    };
  };
  dirHE2d->cd();
  TDirectory *dirrms2dHE = dirHE2d -> mkdir("RMS");
  dirrms2dHE->cd();
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "HE"){
      if (it->first.type == "rms"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        if (it->second->GetSumOfWeights()) ch2d->Write();
        delete ch2d;
      };
    };
  };
  dirHE2d->cd();
  TDirectory *dirgain2dHE = dirHE2d -> mkdir("Gain");
  dirgain2dHE->cd();
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "HE"){
      if (it->first.type == "gain"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        if (it->second->GetSumOfWeights()) ch2d->Write();
        delete ch2d;
      };
    };
  };

  dirhisto2d->cd();
  TDirectory *dirHF2d = dirhisto2d -> mkdir("HF");
  dirHF2d->cd();
  TDirectory *dirmean2dHF = dirHF2d -> mkdir("Mean");
  dirmean2dHF->cd();
// write 2d histograms
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "HF"){
      if (it->first.type == "mean"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        if (it->second->GetSumOfWeights()) ch2d->Write();
        delete ch2d;
      };
    };
  };
  dirHF2d->cd();
  TDirectory *dirrms2dHF = dirHF2d -> mkdir("RMS");
  dirrms2dHF->cd();
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "HF"){
      if (it->first.type == "rms"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        if (it->second->GetSumOfWeights()) ch2d->Write();
        delete ch2d;
      };
    };
  };

  dirhisto2d->cd();
  TDirectory *dirHO2d = dirhisto2d -> mkdir("HO");
  dirHO2d->cd();
  TDirectory *dirmean2dHO = dirHO2d -> mkdir("Mean");
  dirmean2dHO->cd();
// write 2d histograms
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "HO"){
      if (it->first.type == "mean"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        if (it->second->GetSumOfWeights()) ch2d->Write();
        delete ch2d;
      };
    };
  };
  dirHO2d->cd();
  TDirectory *dirrms2dHO = dirHO2d -> mkdir("RMS");
  dirrms2dHO->cd();
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "HO"){
      if (it->first.type == "rms"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        if (it->second->GetSumOfWeights()) ch2d->Write();
        delete ch2d;
      };
    };
  };


  dirhisto2d->cd();
  TDirectory *dirAll2d = dirhisto2d -> mkdir("All");
  dirAll2d->cd();
  TDirectory *dirmean2dAll = dirAll2d -> mkdir("Mean");
  dirmean2dAll->cd();
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "All"){
      if (it->first.type == "mean"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        ch2d->Write();ch2d->Write();
        delete ch2d;
      };
    };
  };

  dirAll2d->cd();
  TDirectory *dirrms2dAll = dirAll2d -> mkdir("RMS");
  dirrms2dAll->cd();
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "All"){
      if (it->first.type == "rms"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        ch2d->Write();
        delete ch2d;
      };
    };
  };
  TDirectory *dirgain2dAll = dirAll2d -> mkdir("Gain");
  dirgain2dAll->cd();
  for (map<map42D,TH2F*>::iterator it = Histo2dMD::histo2dMD.begin();it!=Histo2dMD::histo2dMD.end();it++){
    if (it->first.sub == "All"){
      if (it->first.type == "gain"){
        ch2d = new TCanvas();
        hist.Histo2dStyle(ch2d,it->second);
        ch2d->Write();
        delete ch2d;
      };
    };
  };
  fileoutput->cd();
  TDirectory *dirmult = fileoutput -> mkdir("Multigraphs");
  dirmult->cd();
  TDirectory *dirHBmult = dirmult -> mkdir("HB");
  dirHBmult->cd();
  TDirectory *HBmeanmult = dirHBmult -> mkdir("Mean");
  HBmeanmult->cd();
  TCanvas *cmulti;
  for (map<map4multi,TMultiGraph*>::iterator it = Multi::multigraphs.begin();it!=Multi::multigraphs.end();it++){
    if (it->first.sub == "HB"){
      if (it->first.type == "mean"){
        if (it->second->GetListOfGraphs()){
           cmulti = new TCanvas("","",200,10,500,300);
           hist.MultiStyle(cmulti,it->second,Runsvector);
           cmulti->Write();
           delete cmulti;
        };
      };
    };
  };
  dirHBmult->cd();
  TDirectory *HBrmsmult = dirHBmult -> mkdir("RMS");
  HBrmsmult->cd();
  for (map<map4multi,TMultiGraph*>::iterator it = Multi::multigraphs.begin();it!=Multi::multigraphs.end();it++){
    if (it->first.sub == "HB"){
      if (it->first.type == "rms"){
        if (it->second->GetListOfGraphs()){
           cmulti = new TCanvas("","",200,10,500,300);
           hist.MultiStyle(cmulti, it->second,Runsvector);
           cmulti->Write();
           delete cmulti;
        };
      };
    };
  };
  dirHBmult->cd();
  TDirectory *HBgainmult = dirHBmult -> mkdir("Gain");
  HBgainmult->cd();
  for (map<map4multi,TMultiGraph*>::iterator it = Multi::multigraphs.begin();it!=Multi::multigraphs.end();it++){
    if (it->first.sub == "HB"){
      if (it->first.type == "gain"){
        if (it->second->GetListOfGraphs()){
           cmulti = new TCanvas("","",200,10,500,300);
           hist.MultiStyle(cmulti,it->second,Runsvector);
           cmulti->Write();
           delete cmulti;
        };
      };
    };
  };
  TDirectory *dirHEmult = dirmult -> mkdir("HE");
  dirHEmult->cd();
  TDirectory *HEmeanmult = dirHEmult -> mkdir("Mean");
  HEmeanmult->cd();
  for (map<map4multi,TMultiGraph*>::iterator it = Multi::multigraphs.begin();it!=Multi::multigraphs.end();it++){
    if (it->first.sub == "HE"){
      if (it->first.type == "mean"){
        if (it->second->GetListOfGraphs()){
          if (it->second->GetListOfGraphs()){
             cmulti = new TCanvas("","",200,10,500,300);
             hist.MultiStyle(cmulti,it->second,Runsvector);
             cmulti->Write();
             delete cmulti;
          };
        };
      };
    };
  };
  dirHEmult->cd();
  TDirectory *HErmsmult = dirHEmult -> mkdir("RMS");
  HErmsmult->cd();
  for (map<map4multi,TMultiGraph*>::iterator it = Multi::multigraphs.begin();it!=Multi::multigraphs.end();it++){
    if (it->first.sub == "HE"){
      if (it->first.type == "rms"){
        if (it->second->GetListOfGraphs()){
          if (it->second->GetListOfGraphs()){
             cmulti = new TCanvas("","",200,10,500,300);
             hist.MultiStyle(cmulti,it->second,Runsvector);
             cmulti->Write();
             delete cmulti;
          };
        };
      };
    };
  };
  dirHEmult->cd();
  TDirectory *HEgainmult = dirHEmult -> mkdir("Gain");
  HEgainmult->cd();
  for (map<map4multi,TMultiGraph*>::iterator it = Multi::multigraphs.begin();it!=Multi::multigraphs.end();it++){
    if (it->first.sub == "HE"){
      if (it->first.type == "gain"){
         if (it->second->GetListOfGraphs()){
           if (it->second->GetListOfGraphs()){
              cmulti = new TCanvas("","",200,10,500,300);
              hist.MultiStyle(cmulti,it->second,Runsvector);
              cmulti->Write();
              delete cmulti;
           };
         };
      };
    };
  };
  TDirectory *dirHFmult = dirmult -> mkdir("HF");
  dirHFmult->cd();
  TDirectory *HFmeanmult = dirHFmult -> mkdir("Mean");
  HFmeanmult->cd();
  for (map<map4multi,TMultiGraph*>::iterator it = Multi::multigraphs.begin();it!=Multi::multigraphs.end();it++){
    if (it->first.sub == "HF"){
      if (it->first.type == "mean"){
        if (it->second->GetListOfGraphs()){
           cmulti = new TCanvas("","",200,10,500,300);
           hist.MultiStyle(cmulti,it->second,Runsvector);
           cmulti->Write();
           delete cmulti;
        };
      };
    };
  };
  dirHFmult->cd();
  TDirectory *HFrmsmult = dirHFmult -> mkdir("RMS");
  HFrmsmult->cd();
  for (map<map4multi,TMultiGraph*>::iterator it = Multi::multigraphs.begin();it!=Multi::multigraphs.end();it++){
    if (it->first.sub == "HF"){
      if (it->first.type == "rms"){
        if (it->second->GetListOfGraphs()){
           cmulti = new TCanvas("","",200,10,500,300);
           hist.MultiStyle(cmulti,it->second,Runsvector);
           cmulti->Write();
           delete cmulti;
        };
      };
    };
  };
  TDirectory *dirHOmult = dirmult -> mkdir("HO");
  dirHOmult->cd();
  TDirectory *HOmeanmult = dirHOmult -> mkdir("Mean");
  HOmeanmult->cd();
  for (map<map4multi,TMultiGraph*>::iterator it = Multi::multigraphs.begin();it!=Multi::multigraphs.end();it++){
    if (it->first.sub == "HO"){
      if (it->first.type == "mean"){
        if (it->second->GetListOfGraphs()){
           cmulti = new TCanvas("","",200,10,500,300);
           hist.MultiStyle(cmulti,it->second,Runsvector);
           cmulti->Write();
           delete cmulti;
        };
      };
    };
  };
  dirHOmult->cd();
  TDirectory *HOrmsmult = dirHOmult -> mkdir("RMS");
  HOrmsmult->cd();
  for (map<map4multi,TMultiGraph*>::iterator it = Multi::multigraphs.begin();it!=Multi::multigraphs.end();it++){
    if (it->first.sub == "HO"){
      if (it->first.type == "rms"){
        if (it->second->GetListOfGraphs()){
           cmulti = new TCanvas("","",200,10,500,300);
           hist.MultiStyle(cmulti,it->second,Runsvector);
           cmulti->Write();
           delete cmulti;
        };
      };
    };
  };

  // zmeyka

  fileoutput->cd();
  TDirectory *dirzmeyka = fileoutput -> mkdir("Multizmeyka");
  dirzmeyka->cd();
  TDirectory *dirHBzmeyka = dirzmeyka -> mkdir("HB");
  dirHBzmeyka->cd();
  TDirectory *HBmeanzmeyka = dirHBzmeyka -> mkdir("Mean");
  HBmeanzmeyka->cd();
  TCanvas *czmeyka;
  for (map<map4zmeyka,TH2F*>::iterator it = Zmeyka::zmeyki.begin();it!=Zmeyka::zmeyki.end();it++){
    if (it->first.sub == "HB"){
      if (it->first.type == "mean"){
           czmeyka = new TCanvas();
           hist.ZmeykaStyle(czmeyka,it->second,it->first.sub,Runsvector);
           czmeyka->Write();
           delete czmeyka;
        };
      };
  };
  dirHBzmeyka->cd();
  TDirectory *HBrmszmeyka = dirHBzmeyka -> mkdir("RMS");
  HBrmszmeyka->cd();
  for (map<map4zmeyka,TH2F*>::iterator it = Zmeyka::zmeyki.begin();it!=Zmeyka::zmeyki.end();it++){
    if (it->first.sub == "HB"){
      if (it->first.type == "rms"){
           czmeyka = new TCanvas();
           hist.ZmeykaStyle(czmeyka,it->second,it->first.sub,Runsvector);
           czmeyka->Write();
           delete czmeyka;
        };
      };
  };
  dirHBzmeyka->cd();
  TDirectory *HBgainzmeyka = dirHBzmeyka -> mkdir("Gain");
  HBgainzmeyka->cd();
  for (map<map4zmeyka,TH2F*>::iterator it = Zmeyka::zmeyki.begin();it!=Zmeyka::zmeyki.end();it++){
    if (it->first.sub == "HB"){
      if (it->first.type == "gain"){
           czmeyka = new TCanvas();
           hist.ZmeykaStyle(czmeyka,it->second,it->first.sub,Runsvector);
           czmeyka->Write();
           delete czmeyka;
        };
      };
  };
  TDirectory *dirHEzmeyka = dirzmeyka -> mkdir("HE");
  dirHEzmeyka->cd();
  TDirectory *HEmeanzmeyka = dirHEzmeyka -> mkdir("Mean");
  HEmeanzmeyka->cd();
  for (map<map4zmeyka,TH2F*>::iterator it = Zmeyka::zmeyki.begin();it!=Zmeyka::zmeyki.end();it++){
    if (it->first.sub == "HE"){
      if (it->first.type == "mean"){
           czmeyka = new TCanvas();
           hist.ZmeykaStyle(czmeyka,it->second,it->first.sub,Runsvector);
           czmeyka->Write();
           delete czmeyka;
        };
      };
  };
  dirHEzmeyka->cd();
  TDirectory *HErmszmeyka = dirHEzmeyka -> mkdir("RMS");
  HErmszmeyka->cd();
  for (map<map4zmeyka,TH2F*>::iterator it = Zmeyka::zmeyki.begin();it!=Zmeyka::zmeyki.end();it++){
    if (it->first.sub == "HE"){
      if (it->first.type == "rms"){
           czmeyka = new TCanvas();
           hist.ZmeykaStyle(czmeyka,it->second,it->first.sub,Runsvector);
           czmeyka->Write();
           delete czmeyka;
        };
      };
  };
  dirHEzmeyka->cd();
  TDirectory *HEgainzmeyka = dirHEzmeyka -> mkdir("Gain");
  HEgainzmeyka->cd();
  for (map<map4zmeyka,TH2F*>::iterator it = Zmeyka::zmeyki.begin();it!=Zmeyka::zmeyki.end();it++){
    if (it->first.sub == "HE"){
      if (it->first.type == "gain"){
           czmeyka = new TCanvas();
           hist.ZmeykaStyle(czmeyka,it->second,it->first.sub,Runsvector);
           czmeyka->Write();
           delete czmeyka;
        };
      };
  };
  TDirectory *dirHFzmeyka = dirzmeyka -> mkdir("HF");
  dirHFzmeyka->cd();
  TDirectory *HFmeanzmeyka = dirHFzmeyka -> mkdir("Mean");
  HFmeanzmeyka->cd();
  for (map<map4zmeyka,TH2F*>::iterator it = Zmeyka::zmeyki.begin();it!=Zmeyka::zmeyki.end();it++){
    if (it->first.sub == "HF"){
      if (it->first.type == "mean"){
           czmeyka = new TCanvas();
           hist.ZmeykaStyle(czmeyka,it->second,it->first.sub,Runsvector);
           czmeyka->Write();
           delete czmeyka;
        };
      };
  };
  dirHFzmeyka->cd();
  TDirectory *HFrmszmeyka = dirHFzmeyka -> mkdir("RMS");
  HFrmszmeyka->cd();
  for (map<map4zmeyka,TH2F*>::iterator it = Zmeyka::zmeyki.begin();it!=Zmeyka::zmeyki.end();it++){
    if (it->first.sub == "HF"){
      if (it->first.type == "rms"){
           czmeyka = new TCanvas();
           hist.ZmeykaStyle(czmeyka,it->second,it->first.sub,Runsvector);
           czmeyka->Write();
           delete czmeyka;
        };
      };
  };
  TDirectory *dirHOzmeyka = dirzmeyka -> mkdir("HO");
  dirHOzmeyka->cd();
  TDirectory *HOmeanzmeyka = dirHOzmeyka -> mkdir("Mean");
  HOmeanzmeyka->cd();
  for (map<map4zmeyka,TH2F*>::iterator it = Zmeyka::zmeyki.begin();it!=Zmeyka::zmeyki.end();it++){
    if (it->first.sub == "HO"){
      if (it->first.type == "mean"){
           czmeyka = new TCanvas();
           hist.ZmeykaStyle(czmeyka,it->second,it->first.sub,Runsvector);
           czmeyka->Write();
           delete czmeyka;
        };
      };
  };
  dirHOzmeyka->cd();
  TDirectory *HOrmszmeyka = dirHOzmeyka -> mkdir("RMS");
  HOrmszmeyka->cd();
  for (map<map4zmeyka,TH2F*>::iterator it = Zmeyka::zmeyki.begin();it!=Zmeyka::zmeyki.end();it++){
    if (it->first.sub == "HO"){
      if (it->first.type == "rms"){
           czmeyka = new TCanvas();
           hist.ZmeykaStyle(czmeyka,it->second,it->first.sub,Runsvector);
           czmeyka->Write();
           delete czmeyka;
        };
      };
  };
};


void Trendalyzer::beginJob(string Runtype, vector<int> runs){
// initialize histos and graphs
  hist = Histos(runs,Runtype,Lmapinput);
// initialize El. coord. map

  HcalLoc.RBX = new string();

  string fileoutname = "Trends_" + Runtype + ".root";
  fileoutput = new TFile(fileoutname.c_str(),"recreate");
  fileoutput->cd();
};


void Trendalyzer::endJob(){
  sort(Runsvector.begin(),Runsvector.end());
  string name;
  beginJob(Runtype,Runsvector);
  for (unsigned int i=0; i<Runsvector.size(); i++){
    name = "run" + to_string(Runsvector.at(i)) + ".root";
    openSource(Runtype, name);
    if (!fileinput) continue;
    if (fileinput->IsZombie()) continue;
    ReadDataTree(fileinput);
    if (!sourceTree) continue;
    ReadProv(fileinput);
    if (!provTree) continue;
    provTree -> GetEntry();
    AddTrend2Channels(rundata.runnumber);
    fileinput->Close();
  };
  FillHistos(Runtype, Runsvector);
  WriteHistograms(fileoutput);
  delete HcalLoc.RBX;
  fileoutput->Close();
};

DEFINE_FWK_MODULE(Trendalyzer);
