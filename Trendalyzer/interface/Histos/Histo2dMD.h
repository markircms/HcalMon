#ifndef Histo2dMD_h
#define Histo2dMD_h

#include "Trends/Trendalyzer/interface/Lmap.h"
#include "Trends/Trendalyzer/interface/Dataformats.h"

class Histo2dMD{
public:

Histo2dMD(){};

Histo2dMD(string subdet, int type);

static map<map42D,TH2F*> histo2dMD;

private:

void Add2d(string subdet, int type);
void MakeTitle2d(TH2F* tmph,string name);
const TH2F* ref2dph = new TH2F("","", maxieta - minieta +1,minieta-0.5,maxieta-0.5, maxiphi - miniphi +1,miniphi,maxiphi);
};

#endif
