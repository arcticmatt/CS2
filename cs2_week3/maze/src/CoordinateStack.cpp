/**
 * @file CoordinateStack.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Functions for stack class that stores coordinates.
 *
 * @section License
 * Copyright (c) 2013-2014 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include "CoordinateStack.h"

#define ANIMATION_DELAY     (25)

/**
 * @brief Initializes the stack.
 *
 * @param[in] app Reference to the MazeSolverApp; needed
 * to render moves.
 */
#ifndef TESTSUITE
CoordinateStack::CoordinateStack(class MazeSolverApp *app)
{
    this->app = app;
    init();
}
#else
CoordinateStack::CoordinateStack()
{
    init();
}
#endif


/**
 * @brief Initializes the stack (student-implemented).
 */
void CoordinateStack::init()
{
    top = NULL;
}


/**
 * @brief Deinitializes the stack.
 */
CoordinateStack::~CoordinateStack()
{
    deinit();
}


/**
 * @brief Deletes all items in the stack (student-implemented).
 */
void CoordinateStack::deinit()
{
    while (!is_empty())
    {
        stackitem *item = pop();
        delete item->c;
        delete item;
    }
}


/**
 * @brief Pushes an item onto the stack.
 *
 * @param[in] s Pointer to the item to be added.
 */
void CoordinateStack::push(stackitem *s)
{
    /* Do the operation. */
    do_push(s);

//#ifndef TESTSUITE
    // Update the display.
    //SDL_Delay(ANIMATION_DELAY);
    //this->app->OnRender();
//#endif
}


/**
 * @brief Do the actual push operation (student-implemented).
 *
 * @param[in] s Pointer to the item to be added.
 */
void CoordinateStack::do_push(stackitem *s)
{
    stackitem * prev_top = top;
    top = s;
    top->next = prev_top;
}


/**
 * @brief Pops an item off the stack.
 *
 * @return Pointer to the popped item.
 */
stackitem *CoordinateStack::pop()
{
    /* Do the operation. */
    stackitem *res = do_pop();

//#ifndef TESTSUITE
    //Update the display.
    //SDL_Delay(ANIMATION_DELAY);
    //this->app->OnRender();
//#endif

    return res;
}


/**
 * @brief Do the actual pop operation (student-implemented).
 *
 * @return Pointer to the popped item.
 */
stackitem *CoordinateStack::do_pop()
{
    if (!is_empty())
    {
        stackitem * prev_top = top;
        top = top->next;
        return prev_top;
    }
    printf("invalid pop\n");
    return NULL;
}


/**
 * @brief Returns the top item of the stack without removing it.
 *
 * @return Pointer to the first stack item.
 */
stackitem *CoordinateStack::peek()
{
    return top;
}


/**
 * @brief Returns true if stack is empty, false otherwise.
 *
 * @return Boolean indicating whether the stack is empty.
 */
bool CoordinateStack::is_empty()
{
    if (top == NULL)
    {
        return true;
    }
    return false;
}
