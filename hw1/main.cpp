#include <iostream>
#include "solve_equation.h"

/* Don't see any check for wrong input data, like "b b b" "drev diht etc" */
/* Are you sure? At least on these tests my program run perfectly. */
/* Ok, missed your if-statement last time, my apologizes */
void read_variables(double &a, double &b, double &c) {
    std::cout << "Square equation solver." << std::endl;
    std::cout << "Please write a, b, c from ax^2 + bx + c = 0." << std::endl;
    if (!(std::cin >> a >> b >> c)) {
        std::cout << "Wrong input data!" << std::endl;
        exit(1);
    }
}

/* What made you use here size_t? */
/* If we returned some container with roots then its size would be size_t.
 * So I used it in somehow similar situation. Should I use just unsigned int? */
/* Okay, it is not a big deal here, size_t is usually used when we speak about size of something, like file, array
   here I'd use unsigned, but it is just philosophical question, go with size_t if you like */
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
