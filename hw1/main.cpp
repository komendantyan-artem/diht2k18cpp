#include <iostream>
#include "solve_equation.h"

void read_variables(double &a, double &b, double &c) {
    std::cout << "Square equation solver." << std::endl;
    std::cout << "Please write a, b, c from ax^2 + bx + c = 0." << std::endl;
    if (!(std::cin >> a >> b >> c)) {
        std::cout << "Wrong input data!" << std::endl;
        exit(1);
    }
}

void write_answer(size_t number_of_roots, double x1, double x2) {
    if (number_of_roots == 0) {
        std::cout << "There is no solution of the equation." << std::endl;
    } else if (number_of_roots == 1) {
        std::cout << "There is one solution of the equation: " << x1 << std::endl;
    } else if (number_of_roots == 2) {
        std::cout << "There are two solutions of the equation: " << x1 << ", " << x2 << std::endl;
    } else if (number_of_roots == std::numeric_limits<size_t>::max()){
        std::cout << "There are infinitely many solutions of the equation." << std::endl;
    } else {
        std::cout << "Oops, some unexpected error happened." << std::endl;
    }
}

int main() {
    double a, b, c;
    read_variables(a, b, c);
    double x1, x2;
    size_t number_of_roots = solve_quadratic_equation(a, b, c, x1, x2);
    write_answer(number_of_roots, x1, x2);
}
