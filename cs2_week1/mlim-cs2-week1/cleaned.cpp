#include <stdio.h>

/**
 * @brief: Returns the max common divisor of two
 * numbers.
 *
 * @param a: The first number.
 * @param b: The second number.
 *
 * @return: The max common divisor of the two
 * parameters.
 */
int maxCommonDivisor(int a,int b)
{
    while(a^b)
    {
        if(a > b)
        {
            a += (~b + 1);
        }
        else
        {
            b -= a;
        }
    }
    return a;
}

int main(int argc, char ** argv)
{
    int result = maxCommonDivisor(8, 4);
    printf("%d\n", result);
    return 0;
}
