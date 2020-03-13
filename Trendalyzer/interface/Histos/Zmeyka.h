#ifndef Zmeyka_h
#define Zmeyka_h

#include "Trends/Trendalyzer/interface/Lmap.h"
#include "Trends/Trendalyzer/interface/Dataformats.h"

class Zmeyka{
public:

Zmeyka(){};
Zmeyka(vector<int> v, string s, int t);

static map<map4zmeyka,TH2F*> zmeyki;

private:

//TMultiGraph *refMu;
void MakeTitleZmeyka(TH2F* h2,string name);
void AddZmeyka(vector<int> v, string s, int t);

Lmap LMAP;

};

#endif
