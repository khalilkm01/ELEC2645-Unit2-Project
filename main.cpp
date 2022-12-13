#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include "filter.h"
#include "filterEnum.h"
#include "polesEnum.h"
#include "calculator.h"
#include "passTypeEnum.h"
using namespace std;


std::vector<float> poleTwoGainChebyshev05;
std::vector<float> poleFourGainChebyshev05;
std::vector<float> poleSixGainChebyshev05;

std::vector<float> poleTwoGainChebyshev20;
std::vector<float> poleFourGainChebyshev20;
std::vector<float> poleSixGainChebyshev20;

std::vector<float> poleTwoGainButterworth;
std::vector<float> poleFourGainButterworth;
std::vector<float> poleSixGainButterworth;

std::map<POLESEnum, std::vector<float> > CHEBYSHEV05GainFactors;
std::map<POLESEnum, std::vector<float> > CHEBYSHEV20GainFactors;
std::map<POLESEnum, std::vector<float> > BUTTERWORTHGainFactors;

std::vector<float> poleTwoNFChebyshev05LP;
std::vector<float> poleFourNFChebyshev05LP;
std::vector<float> poleSixNFChebyshev05LP;
std::vector<float> poleTwoNFChebyshev05HP;
std::vector<float> poleFourNFChebyshev05HP;
std::vector<float> poleSixNFChebyshev05HP;

std::vector<float> poleTwoNFChebyshev20HP;
std::vector<float> poleFourNFChebyshev20HP;
std::vector<float> poleSixNFChebyshev20HP;
std::vector<float> poleTwoNFChebyshev20LP;
std::vector<float> poleFourNFChebyshev20LP;
std::vector<float> poleSixNFChebyshev20LP;


std::map<POLESEnum, std::vector<float> > CHEBYSHEV05LPNFactors;
std::map<POLESEnum, std::vector<float> > CHEBYSHEV05HPNFactors;
std::map<POLESEnum, std::vector<float> > CHEBYSHEV20LPNFactors;
std::map<POLESEnum, std::vector<float> > CHEBYSHEV20HPNFactors;




void setupFilterVals();
void kabeerMain();
std::vector<float> pickNormalisingFactor(POLESEnum poles, FILTEREnum filter, PassTypeEnum passType);

int main(){
    kabeerMain();

    return 0;
}

void kabeerMain() {

    int inputFilterType;
    int inputPassType;
    int inputPoleNumber;

    double resistance,capacitance,cFrequency;
    std::vector<float> resistances,capacitances,cFrequencies;
    string paramToCalc;
    FilterCalc calculator;
    PassTypeEnum passType = LOWPASS;
    FILTEREnum filterType;
    POLESEnum poles;
    Filter filter;
    setupFilterVals();
    // Variables to store filter type, number of poles and parameter to calculate


    



    // Ask user to choose filter type
    cout << "Choose filter type: " << endl;
    cout << "1. Chebyshev 0.5dB" << endl;
    cout << "2. Butterworth" << endl;
    cout << "3. Chebyshev 2.0dB" << endl;
    cin >> inputFilterType;
    if (inputFilterType>3 ||inputFilterType<1){
        cout << "Invalid parameter to calculate" << endl;
    } else {
        switch (inputFilterType) {
            case 1:
                filterType = CHEBYSHEV05;
                break;
            case 2: 
                filterType= BUTTERWORTH;
                break;
            case 3: 
                filterType = CHEBYSHEV20;
                break;
            default:
                filterType = BUTTERWORTH;
                break;
        }

        if (filterType!=BUTTERWORTH){
            cout << "Enter 1 for highpass filter, 2 for lowpass filter (default): ";
            cin >> inputPassType; 
            if (inputPassType==1){
                passType = HIGHPASS;
            }
        }

        // Ask user to choose parameter to calculate
        cout << "Enter number of poles to calculate (2(default)/4/6): ";
        cin >> inputPoleNumber;

        switch(inputPoleNumber){
            case 2:
                poles = PoleTWO;
                break;
            case 4: 
                poles = PoleFOUR;
                break;
            case 6:
                poles = PoleSIX;
                break;
            default:
                poles = PoleTWO;
                break;
        }


        // Ask user to choose parameter to calculate
        cout << "Enter parameter to calculate (cutoff/resistor/capacitor): ";
        cin >> paramToCalc;

        std::vector<float> cN = pickNormalisingFactor(poles,filterType,passType);


        // Calculate resistor value for single pole
        if (paramToCalc == "resistor"){

            for (int i = 0; i< inputPoleNumber/2;i++){
                cout<<"Stage: "<< i+1<<endl;
                cout <<"Input Capacitor Value: "<<endl;
                cin>>capacitance;
                capacitances.push_back(capacitance);

                cout <<"Input Cutoff Frequency: "<<endl;
                cin>>cFrequency;
                cFrequencies.push_back(cFrequency);
            }
            


            // Calculate resistor value 
            filter.createUnknownResistor(filterType,poles,capacitances,cFrequencies,cN);

            filter.printFilterValues();
            
            // double r = calculator.calcResistorValue(cFrequency, capacitance,1);

            // // Print pole number and resistor value
            // cout << "Resistor  "  << ": " << r << " ohms" << endl;
        }
        // Calculate capacitor value for single pole
        else if (paramToCalc == "capacitor"){
          
            for (int i = 0; i< inputPoleNumber/2;i++){
                cout<<"Stage: "<< i+1<<endl;
                cout <<"Input Cutoff Frequency: "<<endl;
                cin>>cFrequency;
                cFrequencies.push_back(cFrequency);

                cout <<"Input Resistor Value: "<<endl;
                cin>>resistance;
                resistances.push_back(resistance);
            }
            // Calculate capacitor value 
            filter.createUnknownCapacitance(filterType,poles,cFrequencies,resistances,cN);

            filter.printFilterValues();



            // Calculate capacitor value
            // double c = calculator.calcCapacitorValue(cFrequency, resistance,1);

            // // Print pole number and capacitor value
            // cout << "Capacitor " << ": " << c << " Farads" << endl;
        }
        // Calculate cutoff frequency for single pole
        else if (paramToCalc == "cutoff"){

            for (int i = 0; i< inputPoleNumber/2;i++){
                cout<<"Stage: "<< i+1<<endl;
                cout <<"Input Capacitor Value: "<<endl;
                cin>>capacitance;
                capacitances.push_back(capacitance);

                cout <<"Input Resistor Value: "<<endl;
                cin>>resistance;
                resistances.push_back(resistance);
            }
             // Calculate resistor value 
            filter.createUnknownCutOff(filterType,poles,capacitances,resistances,cN);

            filter.printFilterValues();

            // Calculate cutoff frequency 
            // double fc = calculator.calcCutoffFrequency(resistance, capacitance,1);

            // // Print pole number and cutoff frequency
            // cout << "Cutoff Frequency "  << ": " << fc << " Hz" << endl;
        }
        else{
            cout << "Invalid parameter to calculate" << endl;
        }

    }

    

}

void setupFilterVals(){
    poleTwoGainChebyshev05.push_back(1.842);
    poleFourGainChebyshev05.push_back(1.582);
    poleFourGainChebyshev05.push_back(2.660);

    poleSixGainChebyshev05.push_back(1.537);
    poleSixGainChebyshev05.push_back(2.448);
    poleSixGainChebyshev05.push_back(2.846);

    CHEBYSHEV05GainFactors[PoleTWO] = poleTwoGainChebyshev05;
    CHEBYSHEV05GainFactors[PoleFOUR] = poleFourGainChebyshev05;
    CHEBYSHEV05GainFactors[PoleSIX] = poleSixGainChebyshev05;


    poleTwoGainChebyshev20.push_back(2.114);

    poleFourGainChebyshev20.push_back(1.924);
    poleFourGainChebyshev20.push_back(2.782);

    poleSixGainChebyshev20.push_back(1.891);
    poleSixGainChebyshev20.push_back(2.648);
    poleSixGainChebyshev20.push_back(2.904);

    CHEBYSHEV20GainFactors[PoleTWO] = poleTwoGainChebyshev20;
    CHEBYSHEV20GainFactors[PoleFOUR] = poleFourGainChebyshev20;
    CHEBYSHEV20GainFactors[PoleSIX] = poleSixGainChebyshev20;

    poleTwoGainButterworth.push_back(1.586);

    poleFourGainButterworth.push_back(1.152);
    poleFourGainButterworth.push_back(2.325);

    poleSixGainButterworth.push_back(1.068);
    poleSixGainButterworth.push_back(1.586);
    poleSixGainButterworth.push_back(2.483);

    BUTTERWORTHGainFactors[PoleTWO] = poleTwoGainButterworth;
    BUTTERWORTHGainFactors[PoleFOUR] = poleFourGainButterworth;
    BUTTERWORTHGainFactors[PoleSIX] = poleSixGainButterworth;


    poleTwoNFChebyshev05LP.push_back(1.231);

    poleFourNFChebyshev05LP.push_back(0.597);
    poleFourNFChebyshev05LP.push_back(1.031);

    poleSixNFChebyshev05LP.push_back(0.396);
    poleSixNFChebyshev05LP.push_back(0.768);
    poleSixNFChebyshev05LP.push_back(1.011);

    CHEBYSHEV05LPNFactors[PoleTWO] = poleTwoNFChebyshev05LP;
    CHEBYSHEV05LPNFactors[PoleFOUR] = poleFourNFChebyshev05LP;
    CHEBYSHEV05LPNFactors[PoleSIX] = poleSixNFChebyshev05LP;

    poleTwoNFChebyshev05HP.push_back(0.812);

    poleFourNFChebyshev05HP.push_back(1.675);
    poleFourNFChebyshev05HP.push_back(0.970);

    poleSixNFChebyshev05HP.push_back(2.525);
    poleSixNFChebyshev05HP.push_back(1.302);
    poleSixNFChebyshev05HP.push_back(0.989);

    CHEBYSHEV05HPNFactors[PoleTWO] = poleTwoNFChebyshev05HP;
    CHEBYSHEV05HPNFactors[PoleFOUR] = poleFourNFChebyshev05HP;
    CHEBYSHEV05HPNFactors[PoleSIX] = poleSixNFChebyshev05HP;


    poleTwoNFChebyshev20LP.push_back(0.907);

    poleFourNFChebyshev20LP.push_back(0.471);
    poleFourNFChebyshev20LP.push_back(0.964);

    poleSixNFChebyshev20LP.push_back(0.316);
    poleSixNFChebyshev20LP.push_back(0.730);
    poleSixNFChebyshev20LP.push_back(0.983);

    CHEBYSHEV20LPNFactors[PoleTWO] = poleTwoNFChebyshev20LP;
    CHEBYSHEV20LPNFactors[PoleFOUR] = poleFourNFChebyshev20LP;
    CHEBYSHEV20LPNFactors[PoleSIX] = poleSixNFChebyshev20LP;

    poleTwoNFChebyshev20HP.push_back(1.103);

    poleFourNFChebyshev20HP.push_back(2.123);
    poleFourNFChebyshev20HP.push_back(1.037);

    poleSixNFChebyshev20HP.push_back(3.165);
    poleSixNFChebyshev20HP.push_back(1.370);
    poleSixNFChebyshev20HP.push_back(1.017);

    CHEBYSHEV20HPNFactors[PoleTWO] = poleTwoNFChebyshev20HP;
    CHEBYSHEV20HPNFactors[PoleFOUR] = poleFourNFChebyshev20HP;
    CHEBYSHEV20HPNFactors[PoleSIX] = poleSixNFChebyshev20HP;
};



std::vector<float> pickNormalisingFactor(POLESEnum poles, FILTEREnum filter, PassTypeEnum passType){
    std::vector<float> cN;
    switch (poles){
        case PoleTWO:
            switch (filter){
                case BUTTERWORTH:
                    cN.push_back(1);
                    return cN;
                    break;
                case CHEBYSHEV05:
                    switch (passType){
                        case LOWPASS:
                            return poleTwoNFChebyshev05LP;  
                            break;
                        case HIGHPASS:
                            return poleTwoNFChebyshev05HP; 
                            break;
                    }
                    break;
                case CHEBYSHEV20:
                    switch (passType){
                        case LOWPASS:
                            return poleTwoNFChebyshev20LP; 
                            break;
                        case HIGHPASS:
                            return poleTwoNFChebyshev20HP; 
                            break;
                    }
                    break;
            }
            break;
        case PoleFOUR:
            switch (filter){
                case BUTTERWORTH:
                    cN.push_back(1);
                    cN.push_back(1);
                    return cN;
                    break;
                case CHEBYSHEV05:
                    switch (passType){
                        case LOWPASS:
                            return poleFourNFChebyshev05LP;  
                            break;
                        case HIGHPASS:
                            return poleFourNFChebyshev05HP; 
                            break;
                    }
                    break;
                case CHEBYSHEV20:
                    switch (passType){
                        case LOWPASS:
                            return poleFourNFChebyshev20LP; 
                            break;
                        case HIGHPASS:
                            return poleFourNFChebyshev20HP; 
                            break;
                    }
                    break;
            }
            break;
        case PoleSIX:
            switch (filter){
                case BUTTERWORTH:
                    cN.push_back(1);
                    cN.push_back(1);
                    cN.push_back(1);
                    return cN;
                    break;
                case CHEBYSHEV05:
                    switch (passType){
                        case LOWPASS:
                            return poleSixNFChebyshev05LP;  
                            break;
                        case HIGHPASS:
                            return poleSixNFChebyshev05HP; 
                            break;
                    }
                    break;
                case CHEBYSHEV20:
                    switch (passType){
                        case LOWPASS:
                            return poleSixNFChebyshev20LP; 
                            break;
                        case HIGHPASS:
                            return poleSixNFChebyshev20HP; 
                            break;
                    }
                    break;
            }
            break;
    }
}
