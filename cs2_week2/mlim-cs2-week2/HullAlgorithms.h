/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (header file).
 *
 */

#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include "ConvexHullApp.h"
#include "structs.h"

using namespace std;

void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app);
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app);
void swap(vector<double> &list, int first_index, int second_index);
void swap(vector<Tuple*> &list, int first_index, int second_index);
void sort(vector<Tuple*> &points, vector<double> &angles, int left, int right);
int leftTurn(Tuple *point1, Tuple *point2, Tuple *point3);
