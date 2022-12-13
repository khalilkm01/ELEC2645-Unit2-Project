#include <iostream>
#include <cmath>
#include <map>
#include <vector>
#include "filter.h"
#include "filterEnum.h"
#include "polesEnum.h"
#include "calculator.h"
#include "passTypeEnum.h"
#include <regex>


#define MAIN_MENU 1
#define FILTER_TYPE 2
#define RC_TYPE 3
#define RL_TYPE 4
#define RLC_TYPE 5

void ralph_main_menu();
int get_user_input();
void select_menu_item(int input, int menuType);
void print_menu(int menuType);
void go_back_to_main_menu();
bool is_integer(std::string num);

void menu_item_1();
void menu_item_2();
void menu_item_3();
void menu_item_4();

void filter_type_rc();
void filter_type_rl();
void filter_type_rlc();

void low_pass_rc();
void high_pass_rc();

void low_pass_rl();
void high_pass_rl();

void low_pass_rlc();
void high_pass_rlc();
void band_pass_rlc();


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
void kabeer_main_menu();
std::vector<float> pickNormalisingFactor(POLESEnum poles, FILTEREnum filter, PassTypeEnum passType);

int main(){
    kabeer_main_menu();
    ralph_main_menu();

    return 0;
}

void kabeer_main_menu() {

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

void ralph_main_menu() {
  print_menu(MAIN_MENU);
  int input = get_user_input();
  select_menu_item(input, MAIN_MENU);
}

int get_user_input() {
  int input;
  std::string input_string;
  bool valid_input = false;
  int menu_items = 5;

  do {
    std::cout << "\nSelect item: ";
    std::cin >> input_string;
    valid_input = is_integer(input_string);
    // if input is not an integer, print an error message
    if (valid_input == false) {
      std::cout << "Enter an integer!\n";
    } else {  // if it is an int, check whether in range
      input = std::stoi(input_string);  // convert to int
      if (input >= 1 && input <= menu_items) {
        valid_input = true;
      } else {
        std::cout << "Invalid menu item!\n";
        valid_input = false;
      }
    }
  } while (valid_input == false);

  return input;
}

void select_menu_item(int input, int menuType) {
    switch(menuType) {
        case MAIN_MENU:
            switch (input) {
                case 1:
                    menu_item_1();
                    break;
                case 2:
                    menu_item_2();
                    break;
                case 3:
                    menu_item_3();
                    break;
                case 4:
                    menu_item_4();
                    break;
                default:
                    exit(1);
                    break;
            }
            break;

        case FILTER_TYPE:
            switch (input) {
                case 1:
                    filter_type_rc();
                    break;
                case 2:
                    filter_type_rl();
                    break;
                case 3:
                    filter_type_rlc();
                    break;
                default:
                    exit(1);
                    break;
            }
            break;

        case RC_TYPE:
            switch (input) {
                case 1:
                    low_pass_rc();
                    break;
                case 2:
                    high_pass_rc();
                    break;
                default:
                    exit(1);
                    break;
            }
            break;

        case RL_TYPE:
            switch (input) {
                case 1:
                    low_pass_rl();
                    break;
                case 2:
                    high_pass_rl();
                    break;
                default:
                    exit(1);
                    break;
            }
            break;

        case RLC_TYPE:
            switch (input) {
                case 1:
                    low_pass_rlc();
                    break;
                case 2:
                    high_pass_rlc();
                    break;
                    break;
                case 3:
                    band_pass_rlc();
                    break;
                default:
                    exit(1);
                    break;
            }
            break;

        default:
            exit(1);
            break;
    }
}

void print_menu(int menuType) {
    switch(menuType) {
        case MAIN_MENU:
            std::cout << "Main menu\n";
            std::cout << "1. Menu item 1\n";
            std::cout << "2. Menu item 2\n";
            std::cout << "3. Menu item 3\n";
            std::cout << "4. Menu item 4\n";
            std::cout << "5. Exit\n";
            break;

        case FILTER_TYPE:
            std::cout<< "Select filter type:\n";
            std::cout << "1. RC Filter\n";
            std::cout << "2. RL Filter\n";
            std::cout << "3. RLC Filter\n";
            break;

        case RC_TYPE:
            std::cout<< "Select RC filter type:\n";
            std::cout << "1. Low-pass\n";
            std::cout << "2. High-pass\n";
            break;

        case RL_TYPE:
            std::cout<< "Select RL filter type:\n";
            std::cout << "1. Low-pass\n";
            std::cout << "2. High-pass\n";
            break;

        case RLC_TYPE:
            std::cout<< "Select RLC filter type:\n";
            std::cout << "1. Low-pass\n";
            std::cout << "2. High-pass\n";
            std::cout << "3. Band-pass\n";
            break;

        default:
            exit(1);
            break;
    }
}

void go_back_to_main() {
  std::string input;
  do {
    std::cout << "\nEnter 'b' or 'B' to go back to main menu: ";
    std::cin >> input;
  } while (input != "b" && input != "B");
  ralph_main_menu();
}

// https://codereview.stackexchange.com/questions/162569/checking-if-each-char-in-a-string-is-a-decimal-digit
bool is_integer(std::string num) {
  return std::regex_match(num, std::regex("[+-]?[0-9]+"));
}

void menu_item_1() {
  print_menu(FILTER_TYPE);
  int input = get_user_input();
  select_menu_item(input, FILTER_TYPE);
  go_back_to_main();
}
void menu_item_2() {
  std::cout << "\n>> Menu 2\n";
  std::cout << "\nSome code here does something useful\n";
  // you can call a function from here that handles menu 2
  go_back_to_main();
}
void menu_item_3() {
  std::cout << "\n>> Menu 3\n";
  std::cout << "\nSome code here does something useful\n";
  // you can call a function from here that handles menu 3
  go_back_to_main();
}
void menu_item_4() {
  std::cout << "\n>> Menu 4\n";
  std::cout << "\nSome code here does something useful\n";
  // you can call a function from here that handles menu 4
  go_back_to_main();
}

void filter_type_rc() {
  print_menu(RC_TYPE);
  int input = get_user_input();
  select_menu_item(input, RC_TYPE);
  go_back_to_main();
}
void filter_type_rl() {
  print_menu(RL_TYPE);
  int input = get_user_input();
  select_menu_item(input, RL_TYPE);
  go_back_to_main();
}
void filter_type_rlc() {
  print_menu(RLC_TYPE);
  int input = get_user_input();
  select_menu_item(input, RLC_TYPE);
  go_back_to_main();
}

void low_pass_rc() {
float w = 0;
float r = 0;
float c = 0;
std::cout << "Enter resistance (R):\n";
std::cin >> r;
  if (std::cin.fail()) {
    // Print a message if the input is not a float
    std::cout << "Invalid input. Please enter a float number.\n" ;
  }

std::cout << "Enter capacitance (C):\n";
std::cin >> c;
std::cout << "Input angular cutoff frequency value (ω):\n";
std::cin >> w;
float m = w * r * c;
float p = pow(m, 2.0);
float a = 1 + p;
float s = sqrt(a);
float n = 1 / s;
std::cout << "The calculated gain is " << n << std::endl;

  
}
void high_pass_rc() {
float w = 0;
float r = 0;
float c = 0;
std::cout << "Enter resistance (R):\n";
std::cin >> r;
std::cout << "Enter capacitance (C):\n";
std::cin >> c;
std::cout << "Input angular cutoff frequency value (ω):\n";
std::cin >> w;
float m = w * r * c;
float p = pow(m, 2.0);
float a = 1 + p;
float s = sqrt(a);
float n = m / s;
std::cout << "The calculated gain is " << n << std::endl;
}

void low_pass_rl() {
float w = 0;
float r = 0;
float l = 0;
std::cout << "Enter resistance (R):\n";
std::cin >> r;
std::cout << "Enter inductance (L):\n";
std::cin >> l;
std::cout << "Enter capacitance (C):\n";
std::cin >> w;
float m = w  * l;
float p = pow(m, 2.0);
float a = pow(r,2.0) + p;
float s = sqrt(a);
float n = r / s;
std::cout << "The calculated gain is " << n << std::endl;
}
void high_pass_rl() {

float w = 0;
float r = 0;
float l = 0;
std::cout << "Enter resistance (R):\n";
std::cin >> r;
std::cout << "Enter inductance (L):\n";
std::cin >> l;
std::cout << "Enter capacitance (C):\n";
std::cin >> w;
float m = w  * l;
float p = r + m;
float n = r / p;
std::cout << "The calculated gain is " << n << std::endl;

}

void low_pass_rlc() {
float w = 0;
float r = 0;
float l = 0;
std::cout << "Enter resistance (R):\n";
std::cin >> r;
std::cout << "Enter inductance (L):\n";
std::cin >> l;
std::cout << "Enter angular cutoff frequency (ω):\n";
std::cin >> w;
float n = 1 / (1 + (w * l) / r);
std::cout << "The calculated gain is " << n << std::endl;

}
void high_pass_rlc() {
float w = 0;
float r = 0;
float l = 0;
std::cout << "Enter resistance (R):\n";
std::cin >> r;
std::cout << "Enter inductance (L):\n";
std::cin >> l;
std::cout << "Enter angular cutoff frequency (ω):\n";
std::cin >> w;
float n = r / (r + w * l);
std::cout << "The calculated gain is " << n << std::endl;

}
void band_pass_rlc() {
double pi = 3.14159265359;
float f = 0;
float f1 = 0;
float f2 = 0;
float R = 0;
float L = 0;
float C = 0;
std::  cout << "Enter resistance (R): ";
std::cin >> R;
std::cout << "Enter center frequency (f): ";
std::cin >> f;
std::cout << "Enter lower cutoff frequency (f1): ";
std::cin >> f1;
std::cout << "Enter upper cutoff frequency (f2): ";
std::cin >> f2;
std::cout << "Enter inductance (L): ";
std::cin >> L;
std::cout << "Enter capacitance (C): ";
std::cin >> C;
double n = (R / (2 * pi * L)) * (1 / sqrt(1 + pow(f1/f, 2)) - 1 / sqrt(1 + pow(f2/f, 2)));
std::cout << "The calculated gain is " << n << std::endl;

}
