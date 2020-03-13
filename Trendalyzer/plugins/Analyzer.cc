#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "EventFilter/HcalRawToDigi/interface/HcalHTRData.h"
#include "EventFilter/HcalRawToDigi/interface/HcalDCCHeader.h"
#include "EventFilter/HcalRawToDigi/interface/HcalUnpacker.h"
#include "DataFormats/HcalDetId/interface/HcalOtherDetId.h"
#include "DataFormats/HcalDigi/interface/HcalQIESample.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"
#include "DataFormats/HcalDetId/interface/HcalCalibDetId.h"

#include "DataFormats/Common/interface/Handle.h"

#include "DataFormats/FEDRawData/interface/FEDRawDataCollection.h"
#include "DataFormats/FEDRawData/interface/FEDHeader.h"
#include "DataFormats/FEDRawData/interface/FEDTrailer.h"
#include "DataFormats/FEDRawData/interface/FEDNumbering.h"
#include "DataFormats/FEDRawData/interface/FEDRawData.h"

#include  "CondFormats/HcalObjects/interface/HcalElectronicsMap.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"
#include "CalibFormats/HcalObjects/interface/HcalCalibrations.h"
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"

//fitting, stolen from Aleko


#include "TH1I.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TProfile.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TSystem.h"
#include "TVector.h"
#include "TMath.h"
#include <fstream>

#include "Trends/Trendalyzer/interface/fitGain.h"
#include "Trends/Trendalyzer/interface/Dataformats.h"
#include "Trends/Trendalyzer/interface/Lmap.h"
#include "Trends/Trendalyzer/interface/ParTrends.h"


using namespace edm;


class Analyzer : public edm::EDAnalyzer
{
public:
    explicit Analyzer(const edm::ParameterSet&);
    ~Analyzer();

private:
    virtual void analyze(const edm::Event&, const edm::EventSetup&);

    virtual void beginJob() override;
    virtual void endJob() override;

// functions to book and delete histos
    void bookStuff();
    void FillDataTree();
    TGraphErrors *PSgraph(vector<double> vec,int Ev,int subd_,int iphi_,int ieta_,int depth_);
    template <class Collection, class DataFrame>
    void CollectionDataQIE(edm::Handle<Collection> DigiCollection,edm::ESHandle<HcalDbService> HCalconditions, int NofBins,float RangeL,float RangeR);
    template <class Collection, class DataFrame>
    void CollectionDataOld(edm::Handle<Collection> DigiCollection,edm::ESHandle<HcalDbService> HCalconditions, int NofBins,float RangeL,float RangeR);


    TH1D* histoPulse[NUMCHS];
    TGraphErrors *graphPS[NUMCHS];
    TH1D* histoPulse_;
    TGraphErrors *graphPS_;
    TFile * fileoutput;
    int _skipevents, _maxevts;
    string _outFileName;
    double _historangeLHBHE, _historangeRHBHE;
    int _numberofbinsHBHE;
    double _historangeLHO, _historangeRHO;
    int _numberofbinsHO;
    double _historangeLHF, _historangeRHF;
    int _numberofbinsHF;
    bool _processHO, _processHB, _processHE, _processHF;
    bool _fitpeaks;
    int _time;
    int _runnumber;
    int _seq;
    string RBXname;
    string _Lmapfile;
    TTree *DataTree;
    TTree *ProvTree;

    int vieta[NUMCHS], viphi[NUMCHS], vdepth[NUMCHS], vsubd[NUMCHS];
    edm::EDGetTokenT<QIE11DigiCollection> tok_QIE11DigiCollection_;
    edm::EDGetTokenT<QIE10DigiCollection> tok_QIE10DigiCollection_;
    edm::EDGetTokenT<HBHEDigiCollection> tok_HBHEDigiCollection_;
    edm::EDGetTokenT<HFDigiCollection> tok_HFDigiCollection_;
    edm::EDGetTokenT<HODigiCollection> tok_HODigiCollection_;
    int ieta, iphi, depth, tdc, capid, soi, sub;
    int RM, QIE, QIEch, BVch, MBch;
    const char *RBX;

    int nTS;
    float mean, rms;
    int maxsignalTS;
    double pulse;
    bool firstevent;
    int Numchs;
    int NumQIE11, NumQIE10, NumQIE8;
    float gain;
    vector<double> PShapeV[NUMCHS];
    int eventcounter;
    ChCoordPh chcph;
    ChCoordEl chcel;
    Lmap LMAP1;
};


Analyzer::Analyzer(const edm::ParameterSet& iConfig):
    _skipevents(iConfig.getUntrackedParameter<int>("skipevents")),
    _maxevts(iConfig.getUntrackedParameter<int>("maxevts")),
    _outFileName(iConfig.getUntrackedParameter<string>("OutFileName")),
    _historangeLHBHE(iConfig.getUntrackedParameter<double>("historangeLHBHE")),
    _historangeRHBHE(iConfig.getUntrackedParameter<double>("historangeRHBHE")),
    _numberofbinsHBHE(iConfig.getUntrackedParameter<int>("numberofbinsHBHE")),
    _historangeLHO(iConfig.getUntrackedParameter<double>("historangeLHO")),
    _historangeRHO(iConfig.getUntrackedParameter<double>("historangeRHO")),
    _numberofbinsHO(iConfig.getUntrackedParameter<int>("numberofbinsHO")),
    _historangeLHF(iConfig.getUntrackedParameter<double>("historangeLHF")),
    _historangeRHF(iConfig.getUntrackedParameter<double>("historangeRHF")),
    _numberofbinsHF(iConfig.getUntrackedParameter<int>("numberofbinsHF")),
    _processHO(iConfig.getUntrackedParameter<bool>("processHO")),
    _processHB(iConfig.getUntrackedParameter<bool>("processHB")),
    _processHE(iConfig.getUntrackedParameter<bool>("processHE")),
    _processHF(iConfig.getUntrackedParameter<bool>("processHF")),
    _fitpeaks(iConfig.getUntrackedParameter<bool>("fitPeaks")),
    _time(iConfig.getUntrackedParameter<int>("timeR")),
    _runnumber(iConfig.getUntrackedParameter<int>("rnumber")),
    _seq(iConfig.getUntrackedParameter<int>("seq")),
    _Lmapfile(iConfig.getUntrackedParameter<string>("Lmapfile"))
 {
  fileoutput = new TFile(_outFileName.c_str(), "recreate");
  tok_QIE11DigiCollection_ = consumes<HcalDataFrameContainer<QIE11DataFrame>>(edm::InputTag("hcalDigis"));
  tok_QIE10DigiCollection_ = consumes<HcalDataFrameContainer<QIE10DataFrame>>(edm::InputTag("hcalDigis"));
  tok_HBHEDigiCollection_ = consumes<edm::SortedCollection<HBHEDataFrame>>(edm::InputTag("hcalDigis"));//consumes<HcalDataFrameContainer<HBHEDataFrame>>(edm::InputTag("hcalDigis"));
  tok_HFDigiCollection_ = consumes<edm::SortedCollection<HFDataFrame>>(edm::InputTag("hcalDigis"));
  tok_HODigiCollection_ = consumes<edm::SortedCollection<HODataFrame>>(edm::InputTag("hcalDigis"));
}

void Analyzer::bookStuff(){
  DataTree = new TTree("DataTree", "Relevant output in each channel");
  for (int i=0; i<NUMCHS; i++){
    PShapeV[i] = {};
    histoPulse[i] = new TH1D();
  };
  DataTree->Branch("subd",&sub,"sub/I");
  DataTree->Branch("ieta",&ieta,"ieta/I");
  DataTree->Branch("iphi",&iphi,"iphi/I");
  DataTree->Branch("depth",&depth,"depth/I");
  DataTree->Branch("mean",&mean,"mean/F");
  DataTree->Branch("rms",&rms,"rms/F");
  DataTree->Branch("maxsignalTS",&maxsignalTS,"maxsignalTS/I");
  DataTree->Branch("gain",&gain,"gain/F");
  DataTree->Branch("RBX",&RBXname);
  DataTree->Branch("RM",&RM,"RM/I");
  DataTree->Branch("QIE",&QIE,"QIE/I");
  DataTree->Branch("QIEch",&QIEch,"QIEch/I");
  DataTree->Branch("BVch",&BVch,"BVch/I");
  DataTree->Branch("MBch",&MBch,"MBch/I");
  DataTree->Branch("PulseHisto","TH1D",&histoPulse_,10000,0);
  DataTree->Branch("PSHisto","TGraphErrors",&graphPS_,10000,0);

  ProvTree = new TTree("ProvTree", "General run info");
  ProvTree->Branch("time",&_time,"_time/I");
  ProvTree->Branch("runnumber",&_runnumber,"_runnumber/I");
  ProvTree->Branch("HBflag",&_processHB,"_HBflag/O");
  ProvTree->Branch("HEflag",&_processHE,"_HEflag/O");
  ProvTree->Branch("HFflag",&_processHF,"_HFflag/O");
  ProvTree->Branch("HOflag",&_processHO,"_HOflag/O");
}

void Analyzer::FillDataTree(){
  LMAP1 = Lmap(_Lmapfile);
  cout << LMAP1.MapPhEl.size() << endl;
  cout << _Lmapfile << endl;
  GenPoisParams gpp;
  for (int i=0; i<Numchs; i++){
    gain = -1.;
    histoPulse_ = histoPulse[i];
    sub = vsubd[i];
    if (sub == 0) continue;
    ieta = vieta[i];
    iphi = viphi[i];
    depth = vdepth[i];
    graphPS[i] = PSgraph(PShapeV[i],eventcounter,sub,iphi,ieta,depth);
    graphPS_ = graphPS[i];
    mean = histoPulse[i] -> GetMean();
    rms =  histoPulse[i] -> GetRMS();
    int Npts = graphPS_ -> GetN();
    double *y = graphPS_->GetY();
    maxsignalTS = TMath::LocMax(Npts,y);
    chcph.ieta = ieta;
    chcph.iphi = iphi;
    chcph.depth = depth;
    chcel = LMAP1.MapPhEl.at(chcph);
    RBXname = chcel.RBX;
    RM = chcel.RM;
    QIE = chcel.QIE;
    QIEch = chcel.QIEch;
    BVch = chcel.BVch;
    MBch = chcel.MBch;
//    if (histoPulse_->GetMean() > 1.) DataTree -> Fill();
    if ((sub == HcalSubdetector::HcalBarrel) && _processHB) {
        if (_fitpeaks) {
          fitSPE(histoPulse_,gpp);
          gain = gpp.gain;
        };
        DataTree -> Fill();
    };
    if ((sub == HcalSubdetector::HcalEndcap) && _processHE) {
        if (_fitpeaks) {
          fitSPE(histoPulse_,gpp);
          gain = gpp.gain;
        };
        DataTree -> Fill();
    };
    if ((sub == HcalSubdetector::HcalOuter) && _processHO) DataTree -> Fill();
    if ((sub == HcalSubdetector::HcalForward) && _processHF) DataTree -> Fill();
  };
}

Analyzer::~Analyzer(){
}

// book histogram

void Analyzer::beginJob(){
  firstevent = true;
  NumQIE11 = 0;
  NumQIE10 = 0;
  NumQIE8 = 0;
  eventcounter = 0;
  bookStuff();
}

void Analyzer::endJob(){
  if (Numchs<NUMCHS) FillDataTree();
  ProvTree->Fill();
  fileoutput->cd();
  DataTree->Write();
  ProvTree->Write();
  // test output of histograms, will delete it later;

  /*TDirectory *Pulses = fileoutput->mkdir("Pulses");
  Pulses-> cd();
  for (int i=0; i<Numchs; i++){
    if (histoPulse[i]->GetMean()>1.) histoPulse[i]-> Write();
  };
  TDirectory *PShapes = fileoutput->mkdir("PulseShapes");
  PShapes-> cd();
  for (int i=0; i<Numchs; i++){
    graphPS[i]-> Write();
  };*/
  fileoutput->Close();
}

TGraphErrors *Analyzer::PSgraph(vector<double> vec,int Ev,int subd_,int iphi_,int ieta_,int depth_){
  int N = vec.size();
  char label[100];
  vector<double> xerr = {};
  xerr.resize(N);
  vector<double> yerr = {};
  yerr.resize(N);
  vector<double> x = {};
  x.resize(N);
  vector<double> y = {};
  y.resize(N);

  for (int i=0;i<N;i++){
    y.at(i) = (1/double(Ev)) * vec.at(i);
    yerr.at(i) = (1/sqrt(double(Ev)))*y.at(i);
    x.at(i) = i + 0.5;
  };

  TGraphErrors *temp = new TGraphErrors(N,&x[0],&y[0],&xerr[0],&yerr[0]);
  sprintf(label,"PS, subid = %d, iphi = %d, ieta = %d, depth = %d",subd_, iphi_, ieta_, depth_);
  temp->SetTitle(label);
  temp->SetName(label);
  temp->SetMarkerColor(4);
  temp->SetMarkerStyle(21);
  return temp;
}


// template to read data collection
template <class Collection, class DataFrame>
void Analyzer::CollectionDataQIE(edm::Handle<Collection> DigiCollection, edm::ESHandle<HcalDbService> HCalconditions, int NofBins, float RangeL,float RangeR){
  char label[100];
  int iphi_, subd_, ieta_, depth_;
  for (typename Collection::const_iterator it = DigiCollection->begin(); it != DigiCollection->end(); ++it) {
      const DataFrame digi = static_cast<const DataFrame>(*it);
      // Extract info on detector location
      DetId detid = digi.detid();
      if ((HcalDetId(detid.rawId()).subdet() ==  HcalSubdetector::HcalOther) || (HcalDetId(detid.rawId()).subdet() ==  HcalSubdetector::HcalEmpty)) continue;
      // iterator number of channels
      int flavor = digi.flavor();
      HcalDetId hcaldetid = HcalDetId(detid);
      nTS = digi.samples();
      pulse = 0.;
//      set histogram names if the first event
      if (firstevent){
        subd_ = HcalDetId(detid.rawId()).subdet();
        iphi_ = hcaldetid.iphi();
        ieta_ = hcaldetid.ieta();
        depth_ = hcaldetid.depth();
        sprintf(label,"Pulse, subid =%d, iphi = %d, ieta = %d, depth = %d", subd_,iphi_,ieta_,depth_);
        histoPulse[it - DigiCollection->begin()+Numchs] -> SetName(label);
        histoPulse[it - DigiCollection->begin()+Numchs] -> SetBins(NofBins,RangeL,RangeR);
        vieta[it - DigiCollection->begin()+Numchs] =  ieta_;
        viphi[it - DigiCollection->begin()+Numchs] = iphi_;
        vdepth[it - DigiCollection->begin()+Numchs] = depth_;
        vsubd[it - DigiCollection->begin()+Numchs] = subd_;
        PShapeV[it - DigiCollection->begin()+Numchs].resize(nTS);
      };
      const HcalQIECoder *channelCoder = HCalconditions->getHcalCoder(detid);
      const HcalQIEShape *shape = HCalconditions->getHcalShape(channelCoder);
      // loop over the samples in the digi
      for(int i=0; i<nTS; ++i)
      {
        pulse+=channelCoder->charge(*shape, digi[i].adc(),digi[i].capid());
        PShapeV[it - DigiCollection->begin()+Numchs].at(i) = PShapeV[it - DigiCollection->begin()+Numchs].at(i) + channelCoder->charge(*shape, digi[i].adc(),digi[i].capid());
      };
      histoPulse[it - DigiCollection->begin()+Numchs] -> Fill(pulse);
   };
};

template <class Collection, class DataFrame>
void Analyzer::CollectionDataOld(edm::Handle<Collection> DigiCollection, edm::ESHandle<HcalDbService> HCalconditions, int NofBins, float RangeL,float RangeR){
  char label[100];
  int iphi_, subd_, ieta_, depth_;
  for (typename Collection::const_iterator it = DigiCollection->begin(); it !=DigiCollection->end(); ++it) {
      const DataFrame digi = static_cast<const DataFrame>(*it);
      // Extract info on detector location
      DetId detid = digi.id();
      // check if legit subdetector
      if ((HcalDetId(detid.rawId()).subdet() ==  HcalSubdetector::HcalOther) || (HcalDetId(detid.rawId()).subdet() ==  HcalSubdetector::HcalEmpty)) continue;
      // iterator number of channels
      HcalDetId hcaldetid = HcalDetId(detid);
      nTS = digi.size();
      pulse = 0.;
//      set histogram names if the first event
      if (firstevent){
        subd_ = HcalDetId(detid.rawId()).subdet();
        iphi_ = hcaldetid.iphi();
        ieta_ = hcaldetid.ieta();
        depth_ = hcaldetid.depth();
        sprintf(label,"Pulse, subid =%d, iphi = %d, ieta = %d, depth = %d", subd_,iphi_,ieta_,depth_);
        histoPulse[it - DigiCollection->begin()+Numchs] -> SetName(label);
        histoPulse[it - DigiCollection->begin()+Numchs] -> SetBins(NofBins,RangeL,RangeR);
        vieta[it - DigiCollection->begin()+Numchs] =  ieta_;
        viphi[it - DigiCollection->begin()+Numchs] = iphi_;
        vdepth[it - DigiCollection->begin()+Numchs] = depth_;
        vsubd[it - DigiCollection->begin()+Numchs] = subd_;
        PShapeV[it - DigiCollection->begin()+Numchs].resize(nTS);
      };
      const HcalQIECoder *channelCoder = HCalconditions->getHcalCoder(detid);
      const HcalQIEShape *shape = HCalconditions->getHcalShape(channelCoder);
      // loop over the samples in the digi
      for(int i=0; i<nTS; ++i)
      {
        pulse+=channelCoder->charge(*shape, digi[i].adc(),digi[i].capid());
        PShapeV[it - DigiCollection->begin()+Numchs].at(i) = PShapeV[it - DigiCollection->begin()+Numchs].at(i) + channelCoder->charge(*shape, digi[i].adc(),digi[i].capid());
      };
      histoPulse[it - DigiCollection->begin()+Numchs] -> Fill(pulse);
   };
};

void Analyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup){
  eventcounter++;
  if ((_seq ==1) && ((eventcounter<_skipevents+1) || (eventcounter>_skipevents+_maxevts))) return;
  Numchs = 0;
  edm::ESHandle<HcalDbService> HCalconditions;
  iSetup.get<HcalDbRecord>().get(HCalconditions);
// HBHE
  if ((_processHB) || (_processHE)){
    edm::Handle<QIE11DigiCollection> qie11DigiCollection;
    iEvent.getByToken(tok_QIE11DigiCollection_,qie11DigiCollection);
    const QIE11DigiCollection& qie11digies=*(qie11DigiCollection);
      NumQIE11 = qie11digies.size();
      Numchs += NumQIE11;
      if (Numchs>NUMCHS) {
        std::cout << "Too many channels \n";
        return;
      };
      Numchs-=NumQIE11;
    CollectionDataQIE<QIE11DigiCollection,QIE11DataFrame>(qie11DigiCollection, HCalconditions, _numberofbinsHBHE,_historangeLHBHE,_historangeRHBHE);
    Numchs+=NumQIE11;
  };
  // HF
  if (_processHF){
    edm::Handle<QIE10DigiCollection> qie10DigiCollection;
    iEvent.getByToken(tok_QIE10DigiCollection_,qie10DigiCollection);
    const QIE10DigiCollection& qie10digies=*(qie10DigiCollection);
      NumQIE10 = qie10digies.size();
      Numchs += NumQIE10;
      if (Numchs>NUMCHS) {
        std::cout << "Too many channels \n";
        return;
      };
      Numchs-=NumQIE10;
    CollectionDataQIE<QIE10DigiCollection,QIE10DataFrame>(qie10DigiCollection, HCalconditions, _numberofbinsHF,_historangeLHF,_historangeRHF);
    Numchs+=NumQIE10;
  };
  // H)
  if (_processHO){
    edm::Handle<HODigiCollection> hoDigiCollection;
    iEvent.getByToken(tok_HODigiCollection_,hoDigiCollection);
    const HODigiCollection& hodigies=*(hoDigiCollection);
      NumQIE8 = hodigies.size();
      Numchs += NumQIE8;
      if (Numchs>NUMCHS) {
        std::cout << "Too many channels \n";
        return;
      };
      Numchs-=NumQIE8;
    CollectionDataOld<HODigiCollection,HODataFrame>(hoDigiCollection,HCalconditions, _numberofbinsHO,_historangeLHO,_historangeRHO);
    Numchs+=NumQIE8;
  };
  firstevent = false;
}

DEFINE_FWK_MODULE(Analyzer);
