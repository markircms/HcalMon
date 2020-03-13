#ifndef Multi_h
#define Multi_h

#include "Trends/Trendalyzer/interface/Lmap.h"
#include "Trends/Trendalyzer/interface/Dataformats.h"

class Multi{
public:

Multi(){};

Multi(string s, int t);

static map<map4multi,TMultiGraph*> multigraphs;

private:

TMultiGraph *refMulti;
void MakeTitleMulti(TMultiGraph* mg,string name);
void AddMulti(string s, int t);

Lmap LMAP;

};

#endif
