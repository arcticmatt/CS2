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

    /*-------- CHANGE NOTHING BELOW THIS LINE --------*/
    int * test_values;
    int real_size;

    // seed the PRNG
    srand(time(NULL));

    // allocate the array
    test_values = new int[TEST_SIZE];

    // initialize the test array to garbage
    for(int i = 0; i < TEST_SIZE; i++)
    {
        *(test_values+i) = rand();
    }

    // determine a real size
    real_size = TEST_SIZE - (rand() % 20);

    // initialize the meaningful part of the test array to random numbers
    // all of which are less than one million
    for(int i = 0; i < real_size; i++)
    {
        *(test_values+i) = rand() % 1000000;
    }
    /*-------- CHANGE NOTHING ABOVE THIS LINE --------*/

    int reg_arr[3] = {1, 4, 5};
    int *arr = &reg_arr[0];
    int max = findArrayMax(arr, 3);
    double mean = findArrayMean(arr, 3);
    fillArrayAscending(arr, 3, 5);
    printf("Max: %d, mean: %g\n", max, mean);
    for (int i = 0; i < 3; i++) {
        printf("Index %d: %d ", i, arr[i]);
    }
    printf("\n");
}
