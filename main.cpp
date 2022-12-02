#include <iostream>
#include <cmath>
using namespace std;
// Function to calculate the resistor value for a single pole in a filter
double calcResistorValue(double fc, double c){
    return 1 / (2 * M_PI * fc * c);
}
// Function to calculate the capacitor value for a single pole in a filter
double calcCapacitorValue(double fc, double r){
    return 1 / (2 * M_PI * fc * r);
}
// Function to calculate the cutoff frequency for a single pole in a filter
double calcCutoffFrequency(double r, double c){
    return 1 / (2 * M_PI * r * c);
}
int main() {
    // Variables to store filter type, number of poles and parameter to calculate
    int filterType;
    double resistance,capacitance,cFrequency;
    string paramToCalc;

    // Ask user to choose filter type
    cout << "Choose filter type: " << endl;
    cout << "1. Chebyshev 0.5dB" << endl;
    cout << "2. Butterworth" << endl;
    cout << "3. Chebyshev 2.0dB" << endl;
    cin >> filterType;

    // Ask user to choose parameter to calculate
    cout << "Enter parameter to calculate (cutoff/resistor/capacitor): ";
    cin >> paramToCalc;


        // Calculate resistor value for single pole
        if (paramToCalc == "resistor"){
            
            cout <<"Input Capacitor Value: "<<endl;
            cin>>capacitance;

            cout <<"Input Cutoff Frequency: "<<endl;
            cin>>cFrequency;

            // Calculate resistor value 
            double r = calcResistorValue(cFrequency, capacitance);

            // Print pole number and resistor value
            cout << "Resistor  "  << ": " << r << " ohms" << endl;
        }
        // Calculate capacitor value for single pole
        else if (paramToCalc == "capacitor"){
          

            cout <<"Input Cutoff Frequency: "<<endl;
            cin>>cFrequency;

            cout <<"Input Resistor Value: "<<endl;
            cin>>resistance;
            // Calculate capacitor value
            double c = calcCapacitorValue(cFrequency, resistance);

            // Print pole number and capacitor value
            cout << "Capacitor " << ": " << c << " Farads" << endl;
        }
        // Calculate cutoff frequency for single pole
        else if (paramToCalc == "cutoff"){

            cout <<"Input Capacitor Value: "<<endl;
            cin>>capacitance;

            cout <<"Input Resistor Value: "<<endl;
            cin>>resistance;

            // Calculate cutoff frequency 
            double fc = calcCutoffFrequency(resistance, capacitance);

            // Print pole number and cutoff frequency
            cout << "Cutoff Frequency "  << ": " << fc << " Hz" << endl;
        }
        else{
            cout << "Invalid parameter to calculate" << endl;
        }


    return 0;
}