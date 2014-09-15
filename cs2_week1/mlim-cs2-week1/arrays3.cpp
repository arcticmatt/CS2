/**
 * @file
 * @author The CS2 TA Team <cs2-tas@ugcs.caltech.edu>
 * @date 2014
 * @copyright This code is in the public domain.
 *
 * @brief Another array example with pointers.
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>

#define TEST_SIZE 60

/**
 * @brief: Finds the maximum value of an array of integers.
 *
 * @param arr[]: The array.
 * @param length: The length of the array.
 *
 * @return: The max of the array.
 */
int findArrayMax(int *arr, int length)
{
    int max = 0;
    for (int i = 0; i < length; i++)
    {
        if (*arr > max)
        {
            max = *arr;
        }
        arr++;
    }
    return max;
}

/**
 * @brief Finds the arithmetic mean of an array of integers.
 *
 * @param arr[]: The array.
 * @param length: the length of the array.
 *
 * @return: The mean of the array.
 */
double findArrayMean(int *arr, int length)
{
    double sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += *arr;
        arr++;
    }
    return sum / length;
}

/**
 * @brief Fill an array of integers with an ascending sequence.
 *
 * @param arr[]: The array.
 * @param length: The length of the array.
 * @param sequence_start: The number which will start the ascending sequence.
 *
 * @return: Void.
 */
void fillArrayAscending(int arr[], int length, int sequence_start)
{
    for (int i = 0; i < length; i++)
    {
        *arr = sequence_start;
        arr++;
        sequence_start++;
    }
}

/**
 * @brief Sets up and runs an array example.
 */
int main(int argc, char ** argv)
{
    int * test_values;
    int real_size;

    // seed the PRNG
    srand(time(NULL));

    // determine a real size
    real_size = TEST_SIZE - (rand() % 20);

    /* ANSWER:
     * Dynamically allocate array of exactly the right size.
     */
    test_values = new int[real_size];

    // initialize the meaningful part of the test array to random numbers
    // all of which are less than one million
    for(int i = 0; i < real_size; i++)
    {
        *(test_values+i) = rand() % 1000000;
    }

    int max = findArrayMax(test_values, real_size);
    double mean = findArrayMean(test_values, real_size);
    fillArrayAscending(test_values, real_size, 5);
    printf("Max: %d, mean: %g\n", max, mean);
    for (int i = 0; i < real_size; i++) {
        printf("%d\n", test_values[i]);
    }
    printf("\n");

    delete[] test_values;
    return 0;
}
