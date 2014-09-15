/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input (implementation).
 *
 */

#include "fileio.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

/**
 * readFile     Reads the integers in file and fills nums with these integers.
 * @param file  File containing integers, one per line.
 * @param nums  Vector to fill with the integers in file.
 *
 * Notice that the vector is passed by reference, so you should fill the vector
 * and not return anything from this function.
 */
void readFile(char const *file, std::vector<int> &nums)
{
    string line;
    int value;
    ifstream myfile (file);
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            value = atoi(line.c_str());
            nums.push_back(value);
        }
        myfile.close();
    }
    return;
}
