#include <cassert>
#include <limits>
#include "solve_equation.h"

void test(
        double a, double b, double c,
        size_t expected_number_of_roots,
        double expected_x1=0.0, double expected_x2=0.0
) {
    double x1, x2;
    size_t number_of_roots = solve_quadratic_equation(a, b, c, x1, x2);
    assert(number_of_roots == expected_number_of_roots);
    if (number_of_roots == 1 || number_of_roots == 2) {
        assert(x1 == expected_x1);
    }
    if (number_of_roots == 2) {
        assert(x2 == expected_x2);
    }
}

int main() {
    test(0, 0, 0, std::numeric_limits<size_t>::max());
    test(0, 0, 1, 0);
    test(0, 2, 1, 1, -0.5);
    test(1, 2, 2, 0);
    test(1, 2, 1, 1, -1.0);
    test(1, 1, 0, 2, -1.0, 0.0);
}
