/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The bubble sort, quick sort, merge sort, and in-place quicksort
 * algorithms (implementation).
 *
 */
#include "sorter.h"
#include <stdio.h>
#include <stdlib.h>
std::vector<int> aux;

int main(int argc, char* argv[])
{
    // Set up buffers and data input
    std::string line;
    char *filename;
    int sort_type;

    // Ensure that at most one type of sort and at least a filename are specified.
    if (argc > 3 || argc < 2)
    {
        usage();
    }

    // default sort is bubble sort
    sort_type = BUBBLE_SORT;

    // Figure out which sort to use
    for (int i = 1; i < argc; ++i)
    {
        char *arg = argv[i];
        if (strcmp(arg, "-b") == 0) { sort_type = BUBBLE_SORT; }
        else if (strcmp(arg, "-q") == 0) { sort_type = QUICK_SORT; }
        else if (strcmp(arg, "-m") == 0) { sort_type = MERGE_SORT; }
        else if (strcmp(arg, "-qi") == 0) { sort_type = QUICK_SORT_INPLACE; }
        else { filename = argv[i]; }
    }

    // Read the file and fill our vector of integers
    // THIS FUNCTION IS STUDENT IMPLEMENTED
    std::vector<int> nums;
    readFile(filename, nums);
    for (int i = 0; i < (int) nums.size(); i++)
    {
        aux.push_back(nums[i]);
    }

    switch (sort_type)
    {
        case BUBBLE_SORT:
        print_vector(bubbleSort(nums));
        break;

        case QUICK_SORT:
        print_vector(quickSort(nums));
        break;

        case MERGE_SORT:
        print_vector(mergeSort(nums, 0, (int) nums.size() - 1));
        break;

        case QUICK_SORT_INPLACE:
        print_vector(quicksort_inplace(nums, 0, (int) nums.size() - 1));
        break;

        default:
        usage();
        break;
    }
    return 0;
}

/**
 * Usage    Prints out a usage statement and exits.
 */
void usage()
{
    fprintf(stderr, "%s", usage_string);
    exit(1);
}

/**
 * The bubble sort will loop through the array, switching adjacent elements
 * if they are out of order. Each time through the loop, the last switch
 * is kept track of. This loop through the array is run until the last switch
 * occurs at the 0th index.
 *
 * int temp, last
 * int remaining = list.length
 * WHILE remaining > 0
 *     last = 0
 *     FOR int i = 0; i < remaining; i++
 *         IF list[i] > list[i + 1]
 *              switch(list[i], list[i + 1]
 *              last = i
 *         ENDIF
 *     remaining = last
 */

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to sorter.h if you write a helper function!
 */

/**
 * @brief: Sorts a vector using buble sort.
 *
 * @param list: The list (passed by reference) to be sorted.
 *
 * @return: Returns the sorted list.
 */
std::vector<int> bubbleSort(std::vector<int> &list)
{
    int i, last;
    int remaining = list.size() - 1;
    while (remaining > 0)
    {
        last = 0;
        for (i = 0; i < remaining; i++)
        {
            if (list[i] > list[i + 1])
            {
                swap(list, i, i + 1);
                last = i;
            }
        }
        remaining = last;
    }
    return list;
}

/**
 * We will implement quick sort by picking the pivot to be the
 * first element. Then we will go through the other elements, putting
 * the elements lesser than the pivot in a new vector and the elements
 * greater than the pivot in a new vector. Then we will recursively quicksort
 * these two vectors. Finally we will join the lesser vector, the pivot,
 * and the greater vector, and return that.
 *
 * IF list.size() <= 1
 *     return list
 * ENDIF
 * pivot = list[0]
 * new vector lesser, greater, joint
 * FOR (elements past 0 in list)
 *     IF (element <= pivot)
 *         lesser.add(element)
 *     ELSE
 *         greater.add(element)
 *     ENDIF
 * RETURN concatenate(quicksort(lesser), pivot, quicksort(greater))
 */

/**
 * @brief: Sorts a list using quicksort (not in place).
 *
 * @param list: The list to quicksort.
 *
 * @return: Returns list (having been sorted)
 */
std::vector<int> quickSort(std::vector<int> &list)
{
    if (list.size() <= 1)
    {
        return list;
    }
    int pivot = list[0];
    std::vector<int> lesser;
    std::vector<int> greater;
    std::vector<int> joint;
    for (int i = 1; i < (int) list.size(); i++)
    {
        if (list[i] <= pivot)
        {
            lesser.push_back(list[i]);
        }
        else
        {
            greater.push_back(list[i]);
        }
    }
    lesser = quickSort(lesser);
    greater = quickSort(greater);
    joint = lesser;
    joint.push_back(pivot);
    joint.insert(joint.end(), greater.begin(), greater.end());

    return joint;
}

/**
 * We want to recursively split the list in half, then half again, the half
 * again, etc, sort the last splits, then merge all the lists.
 * IF lo < hi
 *     mid = (lo + hi) / 2
 *     mergesort(lo, mid)
 *     mergesort(mid + 1, hi);
 *     merge(lo, mid, hi);
 * ENDIF
 */

/**
 * @brief: Sorts a list using mergesort.
 *
 * @param lo: The lowest index of the list (usually 0).
 * @param hi: The largest index of the list (usually list.size() - 1)
 */
std::vector<int> mergeSort(std::vector<int> &list, int lo, int hi)
{
    if (lo < hi)
    {
        int mid = (lo + hi) / 2;
        mergeSort(list, lo, mid);
        mergeSort(list, mid + 1, hi);
        merge(list, lo, mid, hi);
    }
    return list;
}

/**
 * @brief: Merges (in place) an array. This means that it takes
 * the elements from lo through mid as one "array" and elements from
 * mid+1 through hi as another, and merges them so that the final array from
 * lo through hi is sorted.
 *
 * @param lo: The index where we will begin our merge.
 * @param mid: The index which splits our merge section into two.
 * @param hi: The index where we will end our merge.
 */
void merge(std::vector<int> &list, int lo, int mid, int hi)
{
    /**
     * Copy the contents of list into the helper array aux.
     */
    for (int i = lo; i <= hi; i++)
    {
        aux[i] = list[i];
    }

    int mid_plus = mid + 1;
    int insert = lo;
    /**
     * Pick the smallest value from each half and insert it into
     * list. Keep doing this until you finish with the first half or
     * the second half.
     */
    while (lo <= mid && mid_plus <= hi)
    {
        if (aux[lo] <= aux[mid_plus])
        {
            list[insert] = aux[lo];
            insert++;
            lo++;
        }
        else {
            list[insert] = aux[mid_plus];
            insert++;
            mid_plus++;
        }
    }

    /**
     * Copy remaining elements from the first half to
     * list. We don't need to do that for the second half
     * because if they are remaining, then they are already in place.
     */
    while (lo <= mid)
    {
        list[insert] = aux[lo];
        insert++;
        lo++;
    }
}

/**
 * We quicksort in place by recursively sorting smaller and smaller
 * subarrays. The meat of this is in the partition function.
 *
 * IF left < right
 *     pivot_index = right
 *     new_pivot_index = partition(list, left, right, pivot_index)
 *     quicksort_inplace(list, left, new_pivot_index - 1);
 *     quick_sort_inplace(list, new_pivot_index + 1, right);
 * ENDIF
 *
 * RETURN list
 */

/**
 * quicksort_inplace:  In-place version of the quicksort algorithm. Requires
 *              O(1) instead of O(N) space, same time complexity. Each call of
 *              the method partitions the list around the pivot (an item taken
 *              from the middle of the array) with items left of the pivot
 *              smaller than it and items to its right larger than it. Then the
 *              method recursively sorts the left and right portions of the list
 *              until it reaches its base case: a list of length 1 is already
 *              sorted.
 *
 * @param list: pointer to integer array to be sorted
 * @param left: Leftmost index of the array/subarray to be quicksorted.
 * @param right: Rightmost index of the array/subarray to be quicksorted.
 *
 * @returns:    Nothing, the array is sorted IN-PLACE.
 */
std::vector<int> quicksort_inplace(std::vector<int> &list, int left, int right)
{
    if (left < right)
    {
        int pivot_index = right;
        int new_pivot_index = partition(list, left, right, pivot_index);
        quicksort_inplace(list, left, new_pivot_index - 1);
        quicksort_inplace(list, new_pivot_index + 1, right);
    }
    return list;
}

/**
 * @brief: Partitions a subarray of a vector. Given a pivot index, it moves
 * that index to the end of the subarray. It then moves all the elements
 * less than the pivot to the front, the elements larger than the pivot to
 * the end (before the pivot), and finally moves the pivot in between the two.
 * It returns the final location of the pivot to be used as a new right
 * or left parameter.
 *
 * @param list: The vector to be partitioned.
 * @param left: The leftmost index of the subarray to be partitioned.
 * @param right: The rightmost index of the subarray to be partitioned.
 * @param pivot_index: The index of the pivot.
 *
 * @return: The final location of the pivot.
 */
int partition(std::vector<int> &list, int left, int right, int pivot_index)
{
    int pivot = list[pivot_index];
    int insert = left;
    // Moves pivot to rightmost index
    swap(list, pivot_index, right);
    for (int i = left; i < right; i++)
    {
        if (list[i] <= pivot)
        {
            swap(list, i, insert);
            insert++;
        }
    }
    swap(list, insert, right);
    return insert;
}

/**
 * @brief: Swaps two elements in a vector.
 *
 * @param first_index: The index of the first element to be sorted.
 * @param second_index: The index of the second element to be sorted.
 */
void swap(std::vector<int> &list, int first_index, int second_index)
{
    int temp = list[first_index];
    list[first_index] = list[second_index];
    list[second_index] = temp;
}

