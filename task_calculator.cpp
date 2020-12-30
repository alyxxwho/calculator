// Copyright 2020 Alisa <alisa_rudovskaya@mail.ru>

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

double multiplication(double a, double b) { return a * b; }

double division(double a, double b) { return a / b; }

double addition(double a, double b) { return a + b; }

double subtraction(double a, double b) { return a - b; }

int main() {
    std::string expr;
    std::string number;
    std::vector<char> operation;
    std::vector<double> c;
    std::vector<char> exprVec;
    bool unMinus;

    std::cout << "Enter the expression: \n";
    std::getline(std::cin, expr);

    copy(expr.begin(), expr.end(), back_inserter(exprVec));

    if (exprVec[0] == '-') {
        unMinus = true;
        exprVec.erase(exprVec.cbegin());
    }

    for (unsigned int i = 0; i < exprVec.size(); i++) {
        if ((exprVec[i] == '+') || (exprVec[i] == '-') || (exprVec[i] == '*') || (exprVec[i] == '/')) {
            operation.push_back(exprVec[i]);
        } else {
            number += exprVec[i];
            if (i != exprVec.size() - 1) {
                if ((exprVec[i + 1] == '+') || (exprVec[i + 1] == '-')
                 || (exprVec[i + 1] == '*')
                 || (exprVec[i + 1] == '/')) {
                    double f = atof(number.c_str());
                    c.push_back(f);
                    number.clear();
                 }
            } else {
                double f = atof(number.c_str());
                c.push_back(f);
                number.clear();
            }
        }
    }

    if (unMinus) {
        c[0] = -c[0];
    }

    std::vector<int> firstOp;
    std::vector<int> secondOp;

    for (unsigned int i = 0; i < operation.size(); i++) {
        if ((operation[i] == '*') || (operation[i] == '/')) {
            firstOp.push_back(i);
        }
        else {
            secondOp.push_back(i);
        }
    }

    for (unsigned int i = 0; i < firstOp.size(); i++) {
        unsigned int a = firstOp[i];
        if (operation[a] == '*') {
            double result = multiplication(c[a], c[a + 1]);
            c[a] = result;
            c.erase(c.begin() + a + 1);
            for (unsigned int j = 0; j < secondOp.size(); j++) {
                if (a < secondOp[j]) {
                    secondOp[j] = secondOp[j] - 1;
                }
            }
            for (unsigned int j = 0; j < firstOp.size(); j++) {
                firstOp[j] = firstOp[j] - 1;
            }
        }

        if (operation[a] == '/') {
            double result = division(c[a], c[a + 1]);
            c[a] = result;
            c.erase(c.begin() + a + 1);
            for (unsigned int j = 0; j < secondOp.size(); j++) {
                if (a < secondOp[j]) {
                    secondOp[j] = secondOp[j] - 1;
                }
            }
            for (unsigned int j = 0; j < firstOp.size(); j++) {
                firstOp[j] = firstOp[j] - 1;
            }
        }

        operation.erase(operation.cbegin() + a);
    }

    for (unsigned int i = 0; i < secondOp.size(); i++) {
        unsigned int b = secondOp[i];
        if (operation[b] == '+') {
            double result = addition(c[b], c[b + 1]);
            c[b] = result;
            c.erase(c.begin() + b + 1);
            for (unsigned int j = 0; j < secondOp.size(); j++) {
                secondOp[j] = secondOp[j] - 1;
            }

        }

        if ((operation[b] == '-') && (operation.size() != 0)) {
            double result = subtraction(c[b], c[b + 1]);
            c[b] = result;
            c.erase(c.begin() + b + 1);
            for (unsigned int j = 0; j < secondOp.size(); j++) {
                secondOp[j] = secondOp[j] - 1;

            }
        }
        operation.erase(operation.cbegin() + b);
    }

    for (unsigned i = 0; i < c.size(); i++) {
        std::cout << c[i] << std::endl;
    }

    return 0;
}
