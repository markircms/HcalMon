#ifndef Zmeyka_h
#define Zmeyka_h

#include "Lmap.h"
#include "Dataformats.h"
#include "ParTrends.h"

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
