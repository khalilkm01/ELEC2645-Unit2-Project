#include "filter.h"
#include <iostream>


double findPoleValue(POLESEnum polesNew){
    if (polesNew == PoleTWO){
        return 2;
    }if (polesNew == PoleFOUR){
        return 4;
    } else{
        return 6;
    }
}

void Filter::printFilterValues(){
    for (double i = 0; i < findPoleValue(poles)/2;i++) {
        std::cout<<"Stage: "<<i+1<<std::endl;
        std::cout<<"CutOff Frequency: "<<cutOffFrequency.at(i)<<std::endl;
        std::cout<<"Resistance: "<<resistor.at(i)<<std::endl;
        std::cout<<"Capacitance: "<<capacitance.at(i)<<std::endl;
    }
}

void Filter::createUnknownCutOff(FILTEREnum filterTypeNew, POLESEnum polesNew, std::vector<float> capacitanceNew, std::vector<float> resistorNew, std::vector<float> cN) {
    FilterCalc calc;
	filterType= filterTypeNew;
	poles = polesNew;
	capacitance.assign( capacitanceNew.begin(), capacitanceNew.end());
	resistor .assign(resistorNew.begin(), resistorNew.end()); 

	for (double i = 0; i < findPoleValue(polesNew)/2;i++) {
		cutOffFrequency.push_back(calc.calcCutoffFrequency(resistorNew.at(i), capacitanceNew.at(i),cN.at(i)));
	}

}

void Filter::createUnknownResistor(FILTEREnum filterTypeNew, POLESEnum polesNew, std::vector<float> capacitanceNew, std::vector<float> cutOffFrequencyNew, std::vector<float> cN) {
	FilterCalc calc;
    filterType = filterTypeNew;
	poles = polesNew;
	capacitance.assign( capacitanceNew.begin(), capacitanceNew.end());
	cutOffFrequency.assign(cutOffFrequencyNew.begin(), cutOffFrequencyNew.end());

	for (double i = 0; i < findPoleValue(polesNew)/2;i++) {
		resistor.push_back(calc.calcResistorValue(cutOffFrequencyNew.at(i),capacitanceNew.at(i),cN.at(i) ));
	}
}

void Filter::createUnknownCapacitance(FILTEREnum filterTypeNew, POLESEnum polesNew, std::vector<float> cutOffFrequencyNew, std::vector<float> resistorNew, std::vector<float> cN) {
	FilterCalc calc;
    filterType = filterTypeNew;
	poles = polesNew;
	cutOffFrequency.assign(cutOffFrequencyNew.begin(), cutOffFrequencyNew.end());
	resistor .assign(resistorNew.begin(), resistorNew.end()); 

	for (double i = 0; i < findPoleValue(polesNew)/2; i++) {
		capacitance.push_back(calc.calcCapacitorValue(cutOffFrequencyNew.at(i),resistorNew.at(i),cN.at(i)));
	}
}
