/**
 * @file DepthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements depth-first search.
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

#include "DepthFirstSolver.h"

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
DepthFirstSolver::DepthFirstSolver(class MazeSolverApp *app)
{
    stack = new CoordinateStack(app);
    init();
}


/**
 * @brief Initializes the solver (student-implemented).
 */
void DepthFirstSolver::init()
{
    // Add (0, 0) item to stack
    stackitem *item = new stackitem();
    coordinate *coord = new coordinate();
    coord->x = 0;
    coord->y = 0;
    item->c = coord;
    stack->push(item);

    // Initalize all values of visited to false
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            visited[i][j] = false;
        }
    }
}


/**
 * @brief Deinitializes the solver.
 */
DepthFirstSolver::~DepthFirstSolver()
{
    deinit();
}


/**
 * @brief Deinitializes the solver (student-implemented).
 */
void DepthFirstSolver::deinit()
{
    delete stack;
}


/**
 * @brief Solves the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void DepthFirstSolver::solve(MazeGrid *maze)
{
    while (!stack->is_empty())
    {
        /*
         * Get the current stackitem, and create a new stack item
         * with the same coordinates as the current stackitem.
         */
        stackitem *current = stack->peek();
        stackitem *next = new stackitem();
        coordinate *coord = new coordinate();
        int x = current->c->x;
        int y = current->c->y;
        coord->x = x;
        coord->y = y;
        next->c = coord;

        visited[x][y] = true;

        // Return is end coordinate found
        if (x == WIDTH - 1 && y == HEIGHT - 1)
        {
            return;
        }

        /*
         * If there is a possible move, increment/decrement the coords
         * of the next stackitem as necessary and push it onto the stack.
         * Only do this for one possible move. This makes it so that we
         * tranverse one path at a time.
         */
        int poss_moves = maze->get_possible_moves(x, y);
        if (poss_moves & N && !visited[x][y - 1])
        {
            next->c->y--;
            stack->push(next);
        }
        else if (poss_moves & E && !visited[x + 1][y])
        {
            next->c->x++;
            stack->push(next);
        }
        else if (poss_moves & S && !visited[x][y + 1])
        {
            next->c->y++;
            stack->push(next);
        }
        else if (poss_moves & W && !visited[x - 1][y])
        {
            next->c->x--;
            stack->push(next);
        }
        else
        {
            // If no possible moves, pop the stack and delete some pointers.
            // This backtracks through the maze.
            delete next;
            delete coord;
            stackitem * item = stack->pop();
            delete item->c;
            delete item;
        }
    }
}


/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<coordinate> DepthFirstSolver::get_path()
{
    vector<coordinate> list;
    stackitem *cur = stack->peek();

    while (cur != NULL)
    {
        coordinate c;
        c.x = cur->c->x;
        c.y = cur->c->y;

        list.push_back(c);

        cur = cur->next;
    }

    return list;
}
