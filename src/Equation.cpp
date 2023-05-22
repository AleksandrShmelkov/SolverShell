//
// Created by mac on 27.12.2022.
//
//#include <stdafx.h>
//#include "../../external/rang/include/rang.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include "Equation.h"



//  [PUBLIC]

    void Equation::EQ_AddEquation(double a, double b) {
        params.assign({a, b});
    }

    void Equation::EQ_AddEquation(double a, double b, double c) {
        params.assign({a, b, c});
    }

    void Equation::EQ_CalcRoots() {
        bool isCalculated = false;

        //Liner
        if (params.size() == 2) {

            isCalculated = Equation::linerEqCounter(
                params[0],
                params[1]
            );
        }




        //Quadratic
        else if(params.size() == 3) {
            isCalculated = Equation::quadraticEqCounter(
                    params[0],
                    params[1],
                    params[2]
            );
        }

        else
          std::cout 
          << "Error! Check num of entered roots!"
          << std::endl;



        if(!isCalculated && params.size() == 3) {
            std::cout
                      << "D < 0; No roots!"
                      << std::endl;
        }
        else if(!isCalculated){
            std::cout 
                    << "Count was failed"
                    << std::endl;
        }
    }

    std::vector<double> Equation::EQ_GetRoots() {
        return roots;
    }
    
    /*
    double Equation::EQ_GetRoot(int id) {
        if(id > roots.size());
    };
    */

    void Equation::EQ_PrintRoots(int id) {
        if(roots.size() > 0)
            std::cout
            << "[ROOTS]"
            << std::endl;

        if(id < 1) {
            for (int i = 0; i < roots.size(); i++)
                std::cout
                << "[" + std::to_string(i + 1) + "] " +
                std::to_string(roots[i])
                << std::endl;
        }

        else {
              std::cout 
              << "[" + std::to_string(id) + "] " +
              std::to_string(roots[id-1])
              << std::endl;
        }

    }

//  [PRIVATE]

    bool Equation::quadraticEqCounter(double a, double b, double c) {
        double D = pow(b, 2) - 4 * a * c;
        if (D > 0) {
            double firstR = (b * (-1) + pow(D, 0.5)) / (2 * a);
            double secondR = (b * (-1) - pow(D, 0.5)) / (2 * a);

            roots.assign({firstR, secondR});
        }
        else if(D == 0){
            double onceRoot = b * (-1) / 2 * a;
            roots.assign({onceRoot});
        }
        else
            return false;

        return true;
    }

    bool Equation::linerEqCounter(double a, double b) {
        double onceRoot = b*(-1)/a;
        roots.assign({onceRoot});
        return true;
    }
