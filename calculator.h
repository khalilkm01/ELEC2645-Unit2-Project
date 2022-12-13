#ifndef CALCULATOR_H
#define CALCULATOR_H


class FilterCalc{
    public:
        double calcResistorValue(double fc, double c,double cN);
        double calcCapacitorValue(double fc, double r,double cN);
        double calcCutoffFrequency(double r, double c,double cN);

};

#endif