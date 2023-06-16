//
// Created by mac on 27.12.2022.
//

#ifndef BASEEQSCOUNTER_EQUATION_H
#define BASEEQSCOUNTER_EQUATION_H

#include <vector>



    class Equation {
    public:
        void EQ_AddEquation(double a, double b);
        void EQ_AddEquation(double a, double b, double c);

        void EQ_CalcRoots();

        std::vector<double> EQ_GetRoots();

        double EQ_GetRoot(int id);

        void EQ_PrintRoots(int id = -1);

    private:
        std::vector<double> roots;
        std::vector<double> params;

        bool quadraticEqCounter(double a, double b, double c);
        bool linerEqCounter(double a, double b);

    };



#endif //BASEEQSCOUNTER_EQUATION_H
