/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief An example of sorting (x, y) pairs by angle.
 *
 */
#include "structs.h"
#include <vector>

using namespace std;

/**
 * @brief: Swaps two elements in a double vector.
 *
 * @param first_index: The index of the first element to be sorted.
 * @param second_index: The index of the second element to be sorted.
 */
void swap(vector<double> &list, int first_index, int second_index)
{
    double temp = list[first_index];
    list[first_index] = list[second_index];
    list[second_index] = temp;
}

/**
 * @brief: Swaps two elements in a Tuple * vector.
 *
 * @param first_index: The index of the first element to be sorted.
 * @param second_index: The index of the second element to be sorted.
 */
void swap(vector<Tuple*> &list, int first_index, int second_index)
{
    Tuple *temp = list[first_index];
    list[first_index] = list[second_index];
    list[second_index] = temp;
}

/**
 * @brief: Partitions a subarray of a vector. Given a pivot index, it moves
 * that index to the end of the subarray. It then moves all the elements
 * less than the pivot to the front, the elements larger than the pivot to
 * the end (before the pivot), and finally moves the pivot in between the two.
 * It returns the final location of the pivot to be used as a new right
 * or left parameter.
 *
 * @param points: The vector to be partitioned, based off of angles.
 * @param angles: The vector to be partitioned. The partitioning of points
 * is based off of the partitioning of angles.
 * @param left: The leftmost index of the subarray to be partitioned.
 * @param right: The rightmost index of the subarray to be partitioned.
 * @param pivot_index: The index of the pivot.
 *
 * @return: The final location of the pivot.
 */
int partition(vector<Tuple*> &points, vector<double> &angles,
        int left, int right, int pivot_index)
{
    double pivot = angles[pivot_index];
    int insert = left;
    // Moves pivot to rightmost index
    swap(angles, pivot_index, right);
    swap(points, pivot_index, right);
    for (int i = left; i < right; i++)
    {
        if (angles[i] <= pivot)
        {
            swap(angles, i, insert);
            swap(points, i, insert);
            insert++;
        }
    }
    swap(angles, insert, right);
    swap(points, insert, right);
    return insert;
}

/**
 * Uses quicksort inplace to sort one array wrt to another. In this case, it
 * sorts the vector points based on the vector angles.
 *
 * @param points: Vector of points to be sorted based on their corresponding
 * angles.
 * @param angles: Angles to be sorted (points are sorted wrt to angles).
 * @param left: Leftmost index of the array/subarray to be quicksorted.
 * @param right: Rightmost index of the array/subarray to be quicksorted.
 *
 * @returns:    Nothing, the array is sorted IN-PLACE.
 */
void sort(vector<Tuple*> &points, vector<double> &angles,
        int left, int right)
{
    if (left < right)
    {
        int pivot_index = right;
        int new_pivot_index = partition(points, angles, left, right,
                pivot_index);
        sort(points, angles, left, new_pivot_index - 1);
        sort(points, angles, new_pivot_index + 1, right);
    }
}


int main(int argc, char const *argv[])
{
    vector<double> angles {4.2, 2.8, 1.4, 5.0, 3.3};
    vector<Tuple*> points;
    // Print the initial points and angles
    for (unsigned int i = 0; i < angles.size(); ++i)
    {
        points.push_back(new Tuple(i, i));
    }
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        printf("%g\n", *i);
    }

    // Now sort them with respect to angle (points[i] corresponds to angle[i])

    /** THIS IS THE ONLY LINE OF THE MAIN LOOP YOU NEED TO MODIFY. */
    sort(points, angles, 0, angles.size() - 1);
    /** REPLACE THE LINE ABOVE WITH A CALL TO YOUR SORTING FUNCTION. */

    // and print out the new points and angles
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        printf("%g\n", *i);
    }

    // Don't want to leak memory...
    // Either of the below implementations works
    // for (std::vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    // {
    //     delete (*i);
    // }
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        delete points[i];
    }
    return 0;
}
