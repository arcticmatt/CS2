#include <stdio.h>
#include <math.h>
/**
 * @brief Solves the given quadratic equation.
 *
 * This function, given real coefficients A, B, C to the equation
 * A*x*x + B*x + C = 0, returns the real part of a solution to the
 * equation thus defined. Where two real solutions exist, the one
 * closer to positive infinity is chosen.
 *
 * @param a the quadratic coefficient.
 * @param b the linear coefficient.
 * @param c the constant coefficient.
 *
 * @return the real part of a solution to the defined quadratic equation,
 *         as described.
 */
double qfsolve(double a, double b, double c)
{
    // If there is a negative square root, return only the real part
    // of the solution.
    if ((pow(b, 2) - 4 * a * c) < 0)
        return -b / (2 * a);
    // Return the real solution closer to positive infinity.
    return (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
}

/**
 * @brief Test of the qfsolve function.
 */
int main(int argc, char ** argv)
{
    printf("Input: 1, 2, 3. Output: %g\n", qfsolve(1, 2, 3));
    printf("Input: 2, 3, -4. Output: %g\n", qfsolve(2, 3, -4));
    printf("Input: 3, 4, -5. Output: %g\n", qfsolve(3, 4, -5));
    printf("Input: 4, 5, -6. Output: %g\n", qfsolve(4, 5, -6));
    printf("Input: 5, 6, -7. Output: %g\n", qfsolve(5, 6, -7));
    return 0;
}
