#include <cmath>
#include <limits>
#include <cstddef>

static bool is_equal(double a, double b, double eps) {
    return fabs(a - b) <= eps;
}

//------------------------------------------------------------------------------
//! Solves a linear equation ax + b = 0
//!
//! @param [in] a a-coefficient
//! @param [in] b b-coefficient
//! @param [out] x Reference to the first root
//! @param [in] eps Accuracy of checking for zero equality (eps=0.0 by default)
//!
//! @return Number of roots
//!
//! @note In case of infinite number of roots, returns std::numeric_limits<size_t>::max()
//------------------------------------------------------------------------------

size_t solve_linear_equation(double a, double b, double &x, double eps=0.0) {
    if (is_equal(a, 0.0, eps)) {
        return is_equal(b, 0.0, eps) ? std::numeric_limits<size_t>::max() : 0;
    } else {
        x = -b / a;
        return 1;
    }
}

//------------------------------------------------------------------------------
//! Solves a square equation ax^2 + bx + c = 0
//!
//! @param [in] a   a-coefficient
//! @param [in] b   b-coefficient
//! @param [in] c   c-coefficient
//! @param [out] x1 Reference to the first root
//! @param [out] x2 Reference to the second root
//! @param [in] eps Accuracy of checking for zero equality (eps=0.0 by default)
//!
//! @return Number of roots
//!
//! @note In case of infinite number of roots, returns std::numeric_limits<size_t>::max()
//------------------------------------------------------------------------------

size_t solve_quadratic_equation(double a, double b, double c, double &x1, double &x2, double eps=0.0) {
    assert(eps >= 0.0);
    if (is_equal(a, 0.0, eps)) {
        return solve_linear_equation(b, c, x1, eps);
    }
    double discriminant = b * b - 4 * a * c;
    if (is_equal(discriminant, 0.0, eps)) {
        x1 = -b / (2 * a);
        return 1;
    } else if (discriminant < 0) {
        return 0;
    } else {
        double sqrt_of_discriminant = sqrt(discriminant);
        x1 = (-b - sqrt_of_discriminant) / (2 * a);
        x2 = (-b + sqrt_of_discriminant) / (2 * a);
        return 2;
    }
}
