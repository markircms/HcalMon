#ifndef Histo1dMD_h
#define Histo1dMD_h

#include "Lmap.h"
#include "Dataformats.h"

class Histo1dMD{
public:

Histo1dMD(){};

Histo1dMD(string subdet, int type, int nbins, float left, float right);

static map<map41D,TH1F*> histo1dMD;

private:

void Add1d(string subdet, int type, int nb, float left, float right);
};

#endif
