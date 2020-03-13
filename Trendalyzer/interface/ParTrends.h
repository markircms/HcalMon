#ifndef ParTrends_h
#define ParTrends_h

#define NUMCHS 30000
#include <stdlib.h>
#include <map>

using namespace std;

extern const string prefix;// = "Runs/";

extern map<string,const int> depths;// = {{"HB",4}, {"HE",7}, {"HO",1}, {"HF",4}, {"All", 7}};
// HO kinda special depth = 4 only

//total number of depths

//extern const int NumbrofdepthsHCAL = 7;

extern const int HOdepth;// = 4;

extern const int NiphisHB;// = 72;
extern const int NiphisHE;//  = 72;
extern const int NiphisHF;// = 36;
extern const int NphisHO;// = 72;

extern const int NumberofHBrbxs;// = 36;
extern const int NumberofHErbxs;// = 36;
extern const int NumberofHFrbxs;// = 16;
extern const int NumberofHOrbxs;// = 36;

extern const int NumberofHBrms;// = 4;
extern const int NumberofHErms;// = 4;
extern const int NumberofHFrms;// = 4;
extern const int NumberofHOrms;// = 4;

extern const int NumberofHBQIEs;// = 4;
extern const int NumberofHEQIEs;// = 4;
extern const int NumberofHFQIEs;// = 9;
extern const int NumberofHOQIEs;// = 4;

extern const int NumberofHBQIEchs;// = 16;
extern const int NumberofHEQIEchs;// = 12;
extern const int NumberofHFQIEchs;// = 24;
extern const int NumberofHOQIEchs;// = 6;

extern const int HBsub;// = 1;
extern const int HEsub;// = 2;
extern const int HOsub;// = 3;
extern const int HFsub;// = 4;

extern map<int,string> HcalSub;// = { {0,"Empty"}, {1,"HB"}, {2,"HE"}, {3,"HO"}, {4,"HF"}, {7,"Other"}};

extern const int maxiphi;// = 72;
extern const int miniphi;// = 1;

extern const int minieta;// = -41;
extern const int maxieta;// = 41;

extern const int Netas;// = 80;
extern const int Nphis;// = 72;


extern map<string, int> HOrbxs; /* = {
  {"HO001",-1},
  {"HO002",-2},
  {"HO003",-3},
  {"HO1M02",-4},
  {"HO1M04",-5},
  {"HO1P02",-6},
  {"HO1P04",-7},
  {"HO2M02",-8},
  {"HO2M04",-9},
  {"HO2P02",-10},
  {"HO2P04",-11},
  {"HO007",-12},
  {"HO008",-13},
  {"HO009",-14},
  {"HO1M08",-15},
  {"HO1M10",-16},
  {"HO1P08",-17},
  {"HO1P10",-18},
  {"HO2M08",1},
  {"HO2M10",2},
  {"HO2P08",3},
  {"HO2P10",4},
  {"HO004",5},
  {"HO005",6},
  {"HO006",7},
  {"HO1M06",8},
  {"HO1P06",9},
  {"HO2M06",10},
  {"HO2P06",11},
  {"HO010",12},
  {"HO011",13},
  {"HO012",14},
  {"HO1M12",15},
  {"HO1P12",16},
  {"HO2M12",17},
  {"HO2P12",18}
};*/

extern map<string, int> HBrbxs;/* = {
  {"HBM01",-1},
  {"HBM02",-2},
  {"HBM03",-3},
  {"HBM04",-4},
  {"HBM05",-5},
  {"HBM06",-6},
  {"HBM07",-7},
  {"HBM08",-8},
  {"HBM09",-9},
  {"HBM10",-10},
  {"HBM11",-11},
  {"HBM12",-12},
  {"HBM13",-13},
  {"HBM14",-14},
  {"HBM15",-15},
  {"HBM16",-16},
  {"HBM17",-17},
  {"HBM18",-18},
  {"HBP01",1},
  {"HBP02",2},
  {"HBP03",3},
  {"HBP04",4},
  {"HBP05",5},
  {"HBP06",6},
  {"HBP07",7},
  {"HBP08",8},
  {"HBP09",9},
  {"HBP10",10},
  {"HBP11",11},
  {"HBP12",12},
  {"HBP13",13},
  {"HBP14",14},
  {"HBP15",15},
  {"HBP16",16},
  {"HBP17",17},
  {"HBP18",18}
};*/

extern map<string, int> HErbxs; /* = {
  {"HEM01",-1},
  {"HEM02",-2},
  {"HEM03",-3},
  {"HEM04",-4},
  {"HEM05",-5},
  {"HEM06",-6},
  {"HEM07",-7},
  {"HEM08",-8},
  {"HEM09",-9},
  {"HEM10",-10},
  {"HEM11",-11},
  {"HEM12",-12},
  {"HEM13",-13},
  {"HEM14",-14},
  {"HEM15",-15},
  {"HEM16",-16},
  {"HEM17",-17},
  {"HEM18",-18},
  {"HEP01",1},
  {"HEP02",2},
  {"HEP03",3},
  {"HEP04",4},
  {"HEP05",5},
  {"HEP06",6},
  {"HEP07",7},
  {"HEP08",8},
  {"HEP09",9},
  {"HEP10",10},
  {"HEP11",11},
  {"HEP12",12},
  {"HEP13",13},
  {"HEP14",14},
  {"HEP15",15},
  {"HEP16",16},
  {"HEP17",17},
  {"HEP18",18}
};*/

extern map<string, int> HFrbxs;/* = {
  {"HFM01",-1},
  {"HFM02",-2},
  {"HFM03",-3},
  {"HFM04",-4},
  {"HFM05",-5},
  {"HFM06",-6},
  {"HFM07",-7},
  {"HFM08",-8},
  {"HFP01",1},
  {"HFP02",2},
  {"HFP03",3},
  {"HFP04",4},
  {"HFP05",5},
  {"HFP06",6},
  {"HFP07",7},
  {"HFP08",8}
};*/


extern map<int,string> HBnum2rbx;/* = {
  {0,"HBM01"},
  {1,"HBM02"},
  {2,"HBM03"},
  {3,"HBM04"},
  {4,"HBM05"},
  {5,"HBM06"},
  {6,"HBM07"},
  {7,"HBM08"},
  {8,"HBM09"},
  {9,"HBM10"},
  {10,"HBM11"},
  {11,"HBM12"},
  {12,"HBM13"},
  {13,"HBM14"},
  {14,"HBM15"},
  {15,"HBM16"},
  {16,"HBM17"},
  {17,"HBM18"},
  {18,"HBP01"},
  {19,"HBP02"},
  {20,"HBP03"},
  {21,"HBP04"},
  {22,"HBP05"},
  {23,"HBP06"},
  {24,"HBP07"},
  {25,"HBP08"},
  {26,"HBP09"},
  {27,"HBP10"},
  {28,"HBP11"},
  {29,"HBP12"},
  {30,"HBP13"},
  {31,"HBP14"},
  {32,"HBP15"},
  {33,"HBP16"},
  {34,"HBP17"},
  {35,"HBP18"}
};*/

extern map<int,string> HEnum2rbx;/* = {
  {0,"HEM01"},
  {1,"HEM02"},
  {2,"HEM03"},
  {3,"HEM04"},
  {4,"HEM05"},
  {5,"HEM06"},
  {6,"HEM07"},
  {7,"HEM08"},
  {8,"HEM09"},
  {9,"HEM10"},
  {10,"HEM11"},
  {11,"HEM12"},
  {12,"HEM13"},
  {13,"HEM14"},
  {14,"HEM15"},
  {15,"HEM16"},
  {16,"HEM17"},
  {17,"HEM18"},
  {18,"HEP01"},
  {19,"HEP02"},
  {20,"HEP03"},
  {21,"HEP04"},
  {22,"HEP05"},
  {23,"HEP06"},
  {24,"HEP07"},
  {25,"HEP08"},
  {26,"HEP09"},
  {27,"HEP10"},
  {28,"HEP11"},
  {29,"HEP12"},
  {30,"HEP13"},
  {31,"HEP14"},
  {32,"HEP15"},
  {33,"HEP16"},
  {34,"HEP17"},
  {35,"HEP18"}
};*/

extern map<int,string> HOnum2rbx;/* = {
  {0,"HO001"},
  {1,"HO002"},
  {2,"HO003"},
  {3,"HO1M02"},
  {4,"HO1M04"},
  {5,"HO1P02"},
  {6,"HO1P04"},
  {7,"HO2M02"},
  {8,"HO2M04"},
  {9,"HO2P02"},
  {10,"HO2P04"},
  {11,"HO007"},
  {12,"HO008"},
  {13,"HO009"},
  {14,"HO1M08"},
  {15,"HO1M10"},
  {16,"HO1P08"},
  {17,"HO1P10"},
  {18,"HO2M08"},
  {19,"HO2M10"},
  {20,"HO2P08"},
  {21,"HO2P10"},
  {22,"HO004"},
  {23,"HO005"},
  {24,"HO006"},
  {25,"HO1M06"},
  {26,"HO1P06"},
  {27,"HO2M06"},
  {28,"HO2P06"},
  {29,"HO010"},
  {30,"HO011"},
  {31,"HO012"},
  {32,"HO1M12"},
  {33,"HO1P12"},
  {34,"HO2M12"},
  {35,"HO2P12"}
};*/

extern map<int,string> HFnum2rbx;/* = {
  {0,"HFM01"},
  {1,"HFM02"},
  {2,"HFM03"},
  {3,"HFM04"},
  {4,"HFM05"},
  {5,"HFM06"},
  {6,"HFM07"},
  {7,"HFM08"},
  {8,"HFP01"},
  {9,"HFP02"},
  {10,"HFP03"},
  {11,"HFP04"},
  {12,"HFP05"},
  {13,"HFP06"},
  {14,"HFP07"},
  {15,"HFP08"}
};*/

extern map<string, map<int,string>> Num2rbx;/* = {
  {"HB",HBnum2rbx},
  {"HE",HEnum2rbx},
  {"HF",HFnum2rbx},
  {"HO",HOnum2rbx},
};*/

extern map<int,int> HFQIEs;/* = {
  {3,1},
  {4,2},
  {5,3},
  {6,4},
  {10,5},
  {11,6},
  {12,7},
  {13,8},
  {14,9}
};*/

extern map<string,int> NumberofRBXs;/* = {
  {"HB",36},
  {"HE",36},
  {"HO",36},
  {"HF",16}
};*/

extern map<string,int> NumberofRMs;/* = {
  {"HB",4},
  {"HE",4},
  {"HO",4},
  {"HF",1}
};*/

#endif
