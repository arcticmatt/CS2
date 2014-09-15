/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (implementation).
 *
 */
#include "HullAlgorithms.h"
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

/**
 * @brief: Tells if the path drawn from point1 to point2 to point3 is a
 * left turn. Does this using cross products.
 *
 * @param point1: Starting point.
 * @param point2: Middle point.
 * @param point3: End point.
 *
 * @return: 1 if a left turn, 0 if not.
 */
int leftTurn(Tuple *point1, Tuple *point2, Tuple *point3)
{
    int x1 = point2->x - point1->x;
    int y1 = point2->y - point1->y;
    int x2 = point3->x - point1->x;
    int y2 = point3->y - point1->y;

    /*
     * Calculate the cross product of the line from point1 to point2 and the
     * line from point1 to point3.
     */
    int cross = (x1 * y2 - y1 * x2);

    if (cross > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to HullAlgorithms.h if you write a helper function!
 *
 * Our reference implementation has four helper functions and the function(s)
 * copied over from angleSort.cpp.
 */

/**
 * Gift wrap works in the following way. First find the leftmost point. Then,
 * from that point, find the point with which it makes a line with the property
 * that there are no points to the left of it. Set that point to the current
 * point, and keep doing this until you wrap around.
 *
 * FOR each point
 *     IF point.x < leftmost
 *         leftmost = point.x
 *         leftmost_index = i
 *     ENDIF
 * add_to_hull(points[leftmost_index])
 * current_index = leftmost_index
 *
 * DO
 *     test_point = -1
 *     FOR each point except current point
 *         IF test_point == -1
 *             test_point = i
 *         ENDIF
 *
 *         int cross = points[i] x test_point
 *
 *         IF cross < 0
 *             test_point = i
 *         ENDIF
 *     current_index = test_point
 *     add_to_hull(points[current_index])
 * WHILE
 *     current_index != leftmost
 */

/**
 * @brief: Adds the points that make up the convex hull, in order.
 * Does this using the gift wrap algorithm.
 *
 * @param points: All the points, which will be gift wrapped.
 * @param app: The convex hull app which we will add points to.
 */
void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app)
{
    int leftmost = 999;
    int leftmost_index = 0;
    int current_index;
    int test_point;

    /**
     * Find the leftmost point.
     */
    for (unsigned int i = 0; i < points.size(); i++)
    {
        if (points[i]->x < leftmost)
        {
            leftmost = points[i]->x;
            leftmost_index = i;
        }
    }
    app->add_to_hull(points[leftmost_index]);
    current_index = leftmost_index;

    /**
     * Loop through all the points on the edges until the starting
     * point is reached.
     */
    do
    {
        test_point = -1;
        for (unsigned int i = 0; i < points.size(); i++)
        {
            if ((int) i != current_index)
            {
                if (test_point == -1)
                {
                    test_point = i;
                }

                int isLeftTurn = leftTurn(points[current_index], points[i],
                        points[test_point]);

                /*
                 * If the current point and the test point make a right turn,
                 * set the test point equal to i. Once the for loop is done,
                 * there will be no points to the left of the line made by
                 * the points at current_index and test_point.
                 */
                if (!isLeftTurn)
                {
                    test_point = i;
                }
            }
        }
        current_index = test_point;
        app->add_to_hull(points[current_index]);


    } while (current_index != leftmost_index);
}

/**
 * To start the Graham scan algorithm, we must find the bottom most point.
 * We then sort all the points by the angles they make relative to the bottom
 * most point. Then we consider these points one by one, seeing if they,
 * along with the previous two points, make a left turn. If they do, the
 * point is added to a list of hull points. If not, then the last hull point
 * is popped, and this keeps happening until a left turn occurs.
 * This process is repeated until all the points have been iterated through.
 *
 * FOR each point
 *     IF point.y < bottom_most
 *         bottom_most = point.y
 *         bottom_most_index = i
 *     ENDIF
 *
 * swap bottom most point with 0 index
 * store bottom most point
 * erase bottom most point from points vector
 *
 * FOR each point
 *     angle = find angle to bottom most point
 *     add angle to angles vector
 *
 * re-insert bottom most point to points vector
 *
 * make new vector to hold hull points
 * push first three points in point (including bottom most)
 *
 * FOR the third point onwards
 *     WHILE top two points on hull points vector and current point
 *     don't make a left turn
 *         remove top point from hull points
 *     push current point onto hull points vector
 *
 * add all the hull points to the app
 */
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app)
{
    int bottom_most = 999;
    int bottom_most_index = 0;
    double angle;
    int num_points = points.size();
    vector<double> angles;
    vector<Tuple*> hull_points;

    /*
     * Find the bottom most point.
     */
    for (int i = 0; i < num_points; i++)
    {
        if (points[i]->y < bottom_most)
        {
            bottom_most = points[i]->y;
            bottom_most_index = i;
        }
    }
    /*
     * Move the bottom point to the 0 index, store it, then erase it
     * from the points vector. We do this so that the quicksort with
     * the angles and points works right (otherwise there would be one
     * more point than there would be angles).
     */
    swap(points, 0, bottom_most_index);
    Tuple *bottom_point = points[0];
    points.erase(points.begin());

    /*
     * Find out all the angles each point makes with the bottom most point,
     * and push these angles to a vecor.
     */
    for (int i = 0; i < num_points; i++)
    {
        angle = bottom_point->angle_wrt_pt(points[i]);
        angles.push_back(angle);
    }
    sort(points, angles, 0, points.size() - 1);

    // Re-insert the bottom most point into the points vector.
    points.insert(points.begin(), bottom_point);

    /*
     * Make a new vector to hold all the points on the hull, and push
     * the bottom most point and the points that make the smallest angle
     * onto the vector.
     */
    hull_points.push_back(points[0]);
    hull_points.push_back(points[1]);
    hull_points.push_back(points[2]);

    for (int i = 3; i < num_points; i++)
    {
        /*
         * While the second to top, top, and points[i] make a right turn,
         * remove the top point from the hull_points vector.
         */
        while (!leftTurn(hull_points[hull_points.size() - 2],
                    hull_points[hull_points.size() - 1], points[i]))
        {
            hull_points.pop_back();
        }
        // Push the point on that makes a left turn.
        hull_points.push_back(points[i]);
    }

    /*
     * Add all the hull points to app.
     */
    for (unsigned int i = 0; i < hull_points.size(); i++)
    {
        app->add_to_hull(hull_points[i]);
    }
    app->add_to_hull(points[0]);


    delete bottom_point;
}




