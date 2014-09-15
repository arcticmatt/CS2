/**
 * @file 
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input.
 * 
 */

#include "fileio.h"

int main(int argc, char const *argv[])
{
    // Read the file input and print out its contents.
    // Assume file contains one integer per line.
    std::vector<int> v;
    readFile(argv[1], v);
    print_vector(v);
    return 0;
}
