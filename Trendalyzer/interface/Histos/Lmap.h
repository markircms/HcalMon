#ifndef __Lmap_h
#define __Lmap_h

#include "Dataformats.h"
#include <fstream>

using namespace std;

class Lmap{

public:

Lmap(string Lmapinput){
  ElectronicMap(Lmapinput);
};

Lmap(){
}

map<ChCoordPh,ChCoordEl> MapPhEl;


private:

void split(vector<string>& dest, const string& str, const char* delim)
{
	char* pTempStr = strdup(str.c_str());
	char* pWord = strtok(pTempStr, delim);
	while (pWord != NULL) {
		dest.push_back(pWord);
		pWord = strtok(NULL, delim);
	}
	free(pTempStr);
};

void ElectronicMap(string Lmapinput){
  ifstream fileLMAP;
  fileLMAP.open(Lmapinput);
  if (!fileLMAP.is_open()) {
    cout << "wrong filename" << endl;
    return;
  };
  string buffer;
  const char* delim = " ";
  vector<std::string> items;
  ChCoordPh tempph;
  ChCoordEl tempel;
  getline(fileLMAP,buffer);
  int sch=0;
  while (getline(fileLMAP,buffer)) {
    sch++;
    items = {};
  //  getline(fileLMAP,buffer);
	//	cout << buffer << endl;
    split(items,buffer,delim);
    if (items.at(0)== "#") continue;
    tempph.iphi = stoi(items.at(2));
    tempph.ieta = stoi(items.at(0))*stoi(items.at(1));
    tempph.depth = stoi(items.at(4));
    tempel.sub = items.at(5);
    tempel.RBX = string(items.at(6));
  //  cout <<  tempel.sub << " ";
    if (tempel.sub!= "HF"){
      if ((tempel.sub!= "HO") && (tempel.sub!= "HOX") && (tempel.sub!= "CALIB_HO")){
        tempel.QIE = stoi(items.at(10));
        tempel.QIEch = stoi(items.at(11));
        tempel.BVch = stoi(items.at(9));
        tempel.MBch = stoi(items.at(8));
        tempel.RM = stoi(items.at(12));
      }
      else {
        tempel.QIE = stoi(items.at(10));
        tempel.QIEch = stoi(items.at(11));
        tempel.BVch = stoi(items.at(8));
        tempel.MBch = -1;
        tempel.RM = stoi(items.at(12));
      }
    };
    if (tempel.sub == "HF"){
      tempel.QIE = stoi(items.at(19));
      tempel.QIEch = stoi(items.at(21));
      tempel.BVch = stoi(items.at(15));
      tempel.RM = stoi(items.at(10));
      tempel.MBch = -1;
    };
    MapPhEl.insert(pair<ChCoordPh,ChCoordEl>(tempph,tempel));
  };
}
};

#endif
