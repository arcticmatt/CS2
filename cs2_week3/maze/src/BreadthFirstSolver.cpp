/**
 * @file BreadthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements breadth-first search.
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

#include "BreadthFirstSolver.h"

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
BreadthFirstSolver::BreadthFirstSolver(class MazeSolverApp *app)
{
    queue = new CoordinateQueue(app);
    init();
}


/**
 * @brief Initializes the solver (student-implemented).
 */
void BreadthFirstSolver::init()
{
    // Enqueue the (0, 0) queueitem
    queueitem *item = new queueitem();
    coordinate *coord = new coordinate();
    coord->x = 0;
    coord->y = 0;
    item->c = coord;
    queue->enqueue(item);

    // Initalize the visited array
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
BreadthFirstSolver::~BreadthFirstSolver()
{
    deinit();
}


/**
 * @brief Deinitializes the solver (student-implemented).
 */
void BreadthFirstSolver::deinit()
{
    delete queue;
}


/**
 * @brief Solve the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void BreadthFirstSolver::solve(MazeGrid *maze)
{
    // Used to mark the queueitem that ends up at the end of the maze
    queueitem *finish;

    while(!queue->is_empty())
    {
        // Get the front queueitem from the queue
        queueitem *current = queue->dequeue();
        queueitem *next;
        int x = current->c->x;
        int y = current->c->y;

        visited[x][y] = true;

        if (x == WIDTH - 1 && y == HEIGHT - 1)
        {
            finish = current;
            break;
        }

        int poss_moves = maze->get_possible_moves(x, y);

        /*
         * Enqueue all possible moves on the stack
         */
        if (poss_moves & N && !visited[x][y - 1])
        {
            next = new queueitem();
            next->c = new coordinate();
            next->c->x = x;
            next->c->y = y - 1;
            // Set the adder pointer to current (b/c it added this item)
            next->adder = current;
            queue->enqueue(next);
        }
        if (poss_moves & E && !visited[x + 1][y])
        {
            next = new queueitem();
            next->c = new coordinate();
            next->c->x = x + 1;
            next->c->y = y;
            next->adder = current;
            queue->enqueue(next);
        }
        if (poss_moves & S && !visited[x][y + 1])
        {
            next = new queueitem();
            next->c = new coordinate();
            next->c->x = x;
            next->c->y = y + 1;
            next->adder = current;
            queue->enqueue(next);
        }
        if (poss_moves & W && !visited[x - 1][y])
        {
            next = new queueitem();
            next->c = new coordinate();
            next->c->x = x - 1;
            next->c->y = y;
            next->adder = current;
            queue->enqueue(next);
        }
    }

    queue->dequeue_all();

    /*
     * Add the maze path to the queue
     */
    queue->enqueue(finish);
    while (queue->peek_last()->adder != NULL)
    {
        queueitem *add = queue->peek_last()->adder;
        queue->enqueue(add);
    }
    return;
}


/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<coordinate> BreadthFirstSolver::get_path()
{
    vector<coordinate> list;
    queueitem *cur = queue->peek_last();

    while (cur != NULL)
    {
        coordinate c;
        c.x = cur->c->x;
        c.y = cur->c->y;

        list.push_back(c);

        cur = cur->parent;
    }

    return list;
}
