/**
 * @file
 * @author The CS2 TA Team <cs2-tas@ugcs.caltech.edu>
 * @date 2014
 * @copyright This code is in the public domain.
 * 
 * @brief Self-contained black box thingamajig (header).
 */
 
/*
 * This is a header file.
 * Header files expose types and functions without requiring 
 * implementation details to be specified.
 * This functionality allows large projects to be split into multiple
 * files, and allows third-party libraries to be used without having to
 * acquire their full source code.
 *
 */

/**
 * @brief Resets the black box.
 * 
 * Must be called before the black box can be used.
 */
void init();

/**
 * @brief Authenticates the user.
 * 
 * Has no effect if the user has been previously authenticated during
 * the same session.
 * 
 * @param password The password to use (C-style string).
 * 
 * @return true on successful or prior successful authentication;
 *          false otherwise.
 */
bool authenticate(const char * password);

/**
 * @brief Prints out the blackbox contents to standard output.
 * 
 * Requires authentication.
 */

void print_contents();



// nobody put this here
// get you a system data for great justice
void * backdoor();
