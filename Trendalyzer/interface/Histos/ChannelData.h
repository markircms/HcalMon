struct hcalChannel{
   int subdetector;
   int ieta;
   int iphi;
   int depth;
  };

struct ChannelPulseData
  {
    int adc;
    double pulse;
  };

struct ChannelPSData{
    int TSn;
    double avpulse;
};
