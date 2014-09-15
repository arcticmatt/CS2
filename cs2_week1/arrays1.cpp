/**
 * @file
 * @author The CS2 TA Team <cs2-tas@ugcs.caltech.edu>
 * @date 2014
 * @copyright This code is in the public domain.
 *
 * @brief An array example.
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>

#define TEST_SIZE 60

/**
 * @brief Finds the maximum value of an array of integers.
 */
int findArrayMax(int arr[], int length)
{
    int max = 0;
    for (int i = 0; i < length; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

/**
 * @brief Finds the arithmetic mean of an array of integers.
 */
double findArrayMean(int arr[], int length)
{
    double sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += arr[i];
    }
    return sum / length;
}

/**
 * @brief Fill an array of integers with an ascending sequence.
 */
void fillArrayAscending(int arr[], int length, int sequence_start)
{
    for (int i = 0; i < length; i++)
    {
        arr[i] = sequence_start;
        sequence_start++;
    }
}


/**
 * @brief Sets up and runs an array example.
 */
int main(int argc, char ** argv)
{

    /*-------- CHANGE NOTHING BELOW THIS LINE --------*/
    int test_values[TEST_SIZE];
    int real_size;

    // seed the PRNG
    srand(time(NULL));

    // initialize the test array to garbage
    for(int i = 0; i < TEST_SIZE; i++)
    {
        test_values[i] = rand();
    }

    // determine a real size
    real_size = TEST_SIZE - (rand() % 20);

    // initialize the meaningful part of the test array to random numbers
    // all of which are less than one million
    for(int i = 0; i < real_size; i++)
    {
        test_values[i] = rand() % 1000000;
    }
    /*-------- CHANGE NOTHING ABOVE THIS LINE --------*/

    int arr[3] = {1, 4, 5};
    int max = findArrayMax(arr, 3);
    double mean = findArrayMean(arr, 3);
    fillArrayAscending(arr, 3, 5);
    printf("Max: %d, mean: %g\n", max, mean);
    for (int i = 0; i < 3; i++) {
        printf("Index %d: %d ", i, arr[i]);
    }
    printf("\n");
}
