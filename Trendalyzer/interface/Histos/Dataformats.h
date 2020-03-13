#ifndef Dataformats_h
#define Dataformats_h

#include <string>
#include <stdlib.h>
#include <map>

#include "TF1.h"
#include "TH2.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH2C.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"

using namespace std;

struct map4gr{
  std::string sub;
  int iphi;
  int ieta;
  int depth;
  string type;
};

bool operator<(const map4gr& x, const map4gr& y) {
    return std::tie(x.sub, x.iphi, x.ieta, x.depth ,x.type) < std::tie(y.sub, y.iphi, y.ieta, y.depth ,y.type);
}

struct map41D{
  string sub;
  string type;
};

bool operator<(const map41D& x, const map41D& y) {
    return std::tie(x.sub, x.type) < std::tie(y.sub, y.type);
}


struct map42D{
  string sub;
  int depth;
  string type;
};

struct map42Del{
  string sub;
  string type;
};

struct map4zmeyka{
  string sub;
  string type;
  string RBX;
  int RM;
};

bool operator<(const map4zmeyka& x, const map4zmeyka& y) {
    return std::tie(x.sub, x.type,x.RBX,x.RM) < std::tie(y.sub, y.type,y.RBX,y.RM);
}



bool operator<(const map42Del& x, const map42Del& y) {
    return std::tie(x.sub ,x.type) < std::tie(y.sub, y.type);
}

bool operator<(const map42D& x, const map42D& y) {
    return std::tie(x.sub, x.depth ,x.type) < std::tie(y.sub, y.depth, y.type);
}

struct map4multi{
  string type;
  string sub;
  string RBX;
  int RM;
};

bool operator<(const map4multi& x, const map4multi& y) {
    return std::tie(x.sub ,x.RBX, x.RM, x.type) < std::tie(y.sub, y.RBX, y.RM,  y.type);
}

struct RunData{
  int time;
  int runnumber;
/*  bool HBflag;
  bool HEflag;
  bool HFflag;
  bool HOflag;*/
};

struct ChannelData{
  int sub;
  int ieta;
  int iphi;
  int depth;
  string *RBX;
  int RM;
  int QIE;
  int QIEch;
  int BVch;
  int MBch;
  float mean;
  float rms;
  int maxsignalTS;
  float gain;
  TH1D *histoPulse;
  TGraphErrors *graphPS;
};

struct ChCoord{
  int run;
  int sub;
  int ieta;
  int iphi;
  int depth;
};

bool operator<(const ChCoord& x, const ChCoord& y) {
    return std::tie(x.run, x.sub, x.ieta, x.iphi ,x.depth) < std::tie(y.run, y.sub, y.ieta, y.iphi ,y.depth);
};

struct map4refgr{
  string runtype;
  string sub;
  string grtype;
};


bool operator<(const map4refgr& x, const map4refgr& y) {
    return std::tie(x.runtype, x.sub ,x.grtype) < std::tie(y.runtype, y.sub, y.grtype);
};

struct ChData{
  string RBX;
  int RM;
  int QIE;
  int QIEch;
  int BVch;
  int MBch;
  float mean;
  float rms;
  float gain;
  int maxsignalTS;
};


struct ChCoordEl{
  string sub;
  string RBX;
  int RM;
  int QIE;
  int QIEch;
  int BVch;
  int MBch;
};

struct ChCoordPh{
  int iphi;
  int ieta;
  int depth;
};

bool operator<(const ChCoordPh& x, const ChCoordPh& y) {
    return std::tie(x.iphi,x.ieta, x.depth) < std::tie(y.iphi ,y.ieta, y.depth);
};


bool HBhex = false;
bool HEhex = false;
bool HFhex = false;
bool HOhex = false;
bool ped = false;

map<ChCoord,ChData> ChannelTrends;

#endif
