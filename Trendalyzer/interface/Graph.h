#ifndef Graph_h
#define Graph_h

#include "Lmap.h"
#include "Dataformats.h"
#include "ParTrends.h"

class Graph{
public:

Graph(){};

Graph(vector<int> v, Lmap L);
void AddGr(string s, int t);

static map<map4gr,TGraph*> graphs;

private:

map<map4refgr,TGraph*> mrefgr;
void Refgr(vector<int> v);
void MakeTitleGr(TGraph* gr,string name);
Lmap LMAP;

};

#endif
