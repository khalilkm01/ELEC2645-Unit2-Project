#ifndef FILTER_H
#define FILTER_H

#include <map>
#include <vector>
#include "filterEnum.h"
#include "polesEnum.h"
#include "calculator.h"




class Filter{
    private:
        FILTEREnum filterType;
        POLESEnum poles;
        std::vector<float> cutOffFrequency;
        std::vector<float> capacitance;
        std::vector<float> resistor;

    public:
	    void printFilterValues();
        void createUnknownCutOff(FILTEREnum filterTypeNew, POLESEnum polesNew, std::vector<float> capacitanceNew, std::vector<float> resistorNew,std::vector<float> cN);
        void createUnknownResistor(FILTEREnum filterTypeNew, POLESEnum polesNew, std::vector<float> capacitanceNew, std::vector<float> cutOffFrequencyNew,std::vector<float> cN); 
        void createUnknownCapacitance(FILTEREnum filterTypeNew, POLESEnum polesNew, std::vector<float> cutOffFrequencyNew, std::vector<float> resistorNew,std::vector<float> cN);
};





#endif

    // std::vector<float> poleTwoGainChebyshev05 {1.842};
    // std::vector<float> poleFourGainChebyshev05 {1.582,2.660};
    // std::vector<float> poleSixGainChebyshev05 {1.537,2.448,2.846};

    // std::vector<float> poleTwoGainChebyshev20 {2.114};
    // std::vector<float> poleFourGainChebyshev20 {1.924,2.782};
    // std::vector<float> poleSixGainChebyshev20 {1.891,2.648,2.904};

    // std::vector<float> poleTwoGainButterworth {1.586};
    // std::vector<float> poleFourGainButterworth {1.152,2.325};
    // std::vector<float> poleSixGainButterworth {1.068,1.586,2.483};

    // std::map<POLESEnum, std::vector<float> > CHEBYSHEV05GainFactors;
    // std::map<POLESEnum, std::vector<float> > CHEBYSHEV20GainFactors;
    // std::map<POLESEnum, std::vector<float> > BUTTERWORTHGainFactors;

    // std::vector<float> poleTwoNFChebyshev05LP {1.231};
    // std::vector<float> poleFourNFChebyshev05LP {0.597,1.031};
    // std::vector<float> poleSixNFChebyshev05LP {0.396,0.768,1.011};
    // std::vector<float> poleTwoNFChebyshev05HP {0.812};
    // std::vector<float> poleFourNFChebyshev05HP {1.675,0.970};
    // std::vector<float> poleSixNFChebyshev05HP {2.525,1.302,0.989};


    // std::vector<float> poleTwoNFChebyshev20HP {0.907};
    // std::vector<float> poleFourNFChebyshev20HP {0.471,0.964};
    // std::vector<float> poleSixNFChebyshev20HP {0.316,0.730,0.983};
    // std::vector<float> poleTwoNFChebyshev20LP {1.103};
    // std::vector<float> poleFourNFChebyshev20LP {2.123,1.037};
    // std::vector<float> poleSixNFChebyshev20LP {3.165,1.370,1.017};


    // std::map<POLESEnum, std::vector<float> > CHEBYSHEV05LPNFactors;
    // std::map<POLESEnum, std::vector<float> > CHEBYSHEV05HPNFactors;
    // std::map<POLESEnum, std::vector<float> > CHEBYSHEV20LPNFactors;
    // std::map<POLESEnum, std::vector<float> > CHEBYSHEV20HPNFactors;


    // CHEBYSHEV05GainFactors[PoleTWO] = poleTwoGainChebyshev05;
    // CHEBYSHEV05GainFactors[PoleFOUR] = poleFourGainChebyshev05;
    // CHEBYSHEV05GainFactors[PoleSIX] = poleSixGainChebyshev05;


    // CHEBYSHEV20GainFactors[PoleTWO] = poleTwoGainChebyshev20;
    // CHEBYSHEV20GainFactors[PoleFOUR] = poleFourGainChebyshev20;
    // CHEBYSHEV20GainFactors[PoleSIX] = poleSixGainChebyshev20;


    // BUTTERWORTHGainFactors[PoleTWO] = poleTwoGainButterworth;
    // BUTTERWORTHGainFactors[PoleFOUR] = poleFourGainButterworth;
    // BUTTERWORTHGainFactors[PoleSIX] = poleSixGainButterworth;


    // CHEBYSHEV05LPNFactors[PoleTWO] = poleTwoNFChebyshev05LP;
    // CHEBYSHEV05LPNFactors[PoleFOUR] = poleFourNFChebyshev05LP;
    // CHEBYSHEV05LPNFactors[PoleSIX] = poleSixNFChebyshev05LP;


    // CHEBYSHEV05HPNFactors[PoleTWO] = poleTwoNFChebyshev05HP;
    // CHEBYSHEV05HPNFactors[PoleFOUR] = poleFourNFChebyshev05HP;
    // CHEBYSHEV05HPNFactors[PoleSIX] = poleSixNFChebyshev05HP;

    // CHEBYSHEV20LPNFactors[PoleTWO] = poleTwoNFChebyshev20LP;
    // CHEBYSHEV20LPNFactors[PoleFOUR] = poleFourNFChebyshev20LP;
    // CHEBYSHEV20LPNFactors[PoleSIX] = poleSixNFChebyshev20LP;



    // CHEBYSHEV20HPNFactors[PoleTWO] = poleTwoNFChebyshev20HP;
    // CHEBYSHEV20HPNFactors[PoleFOUR] = poleFourNFChebyshev20HP;
    // CHEBYSHEV20HPNFactors[PoleSIX] = poleSixNFChebyshev20HP;