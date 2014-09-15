/**
 * @file
 * @author The CS2 TA Team <cs2-tas@ugcs.caltech.edu>
 * @date 2014
 * @copyright This code is in the public domain.
 *
 * @brief An example of the utility of printf() in debugging.
 */

/*
 * The code runs until b is 0. For each run through
 * the loop, it checks if b is odd. If so, it adds a to x.
 * Then a is bitshifted left (multiplying it be 2) and b is bitshifted right
 * (dividing it by 2).
 * The variable x ends up being 14790, or the product of a and b.
 * If you change a and b you end up with a different final x and a.
 * However, x will still be the product of the initial a and b.
 *
 * To answer "why it does what it does," it basically just adds multiples
 * of a. These multiples are of the form a * 2^n.
 */

#include <cstdio>

/**
 * @brief Does a thing.
 *
 * Does a thing, I dunno, you tell me.
 */
int main(int argc, char ** argv)
{
    // Much of the following is intentionally undocumented.
    // Part of the assignment is to figure out what is going on.
    // You may need to look up some operators!
    unsigned int a = 174, b = 85, x = 0;
    printf("Initial: a: %d, b: %d, x: %d\n", a, b, x);

    // This construct is known as a 'while loop'.
    // The interior of the loop is run if, and while,
    // the given condition is true.
    // The program proceeds past the loop if, and when,
    // the given condition is found to be false just before any iteration
    // of the interior of the loop.
    while(b != 0)
    {
        // This construct is known as a conditional statement
        // ('if' statement).
        // The interior of the statement is run exactly once in its entirety
        // if the given condition is found to be true.
        // Note that 'true' is defined as nonzero,
        // and 'false' is defined as zero.

        // If b is odd
        if((b & 1) != 0)
        {
            x += a;
            printf("In if statement: b: %d, x: %d\n", b, x);
        }
        a <<= 1;
        b >>= 1;
        printf("In loop: a: %d, b: %d, x: %d\n", a, b, x);
    }
    printf("Final: a: %d, b: %d, x: %d\n", a, b, x);

    // Question for you now: so what is x anyway?

    return 0;
}
