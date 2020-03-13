#ifndef Multi_h
#define Multi_h

#include "Lmap.h"
#include "Dataformats.h"
#include "ParTrends.h"

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
