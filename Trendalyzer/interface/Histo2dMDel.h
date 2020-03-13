#ifndef Histo2dMDel_h
#define Histo2dMDel_h

#include "Lmap.h"
#include "Dataformats.h"
#include "ParTrends.h"

class Histo2dMDel{
public:

Histo2dMDel(){};

Histo2dMDel(Lmap l, string subdet, int type);

static map<map42Del,TH2F*> histo2dMDel;

private:

void Add2del(Lmap l, string subdet, int type);
void MakeEl2d(TH2F *tmph,string s);
void MakeTitle2d(TH2F* tmph,string name);

};

#endif
