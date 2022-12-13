 #include "calculator.h"
 #include <cmath>
 
        // Function to calculate the resistor value for a single pole in a filter
double FilterCalc::calcResistorValue(double fc, double c,double cN){
    return 1 / (2 * M_PI * fc * c * cN);
}
// Function to calculate the capacitor value for a single pole in a filter
double FilterCalc::calcCapacitorValue(double fc, double r,double cN){
    return 1 / (2 * M_PI * fc * r * cN);
}
// Function to calculate the cutoff frequency for a single pole in a filter
double FilterCalc::calcCutoffFrequency(double r, double c,double cN){
    return 1 / (2 * M_PI * r * c * cN);
}