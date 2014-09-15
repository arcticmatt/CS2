/**
 * @file CoordinateQueue.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Functions for queue class that stores coordinates.
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

#include "CoordinateQueue.h"

#define ANIMATION_DELAY     (25)


/**
 * @brief Initializes the queue.
 *
 * @param[in] app Reference to the MazeSolverApp; needed
 * to render moves.
 */
#ifndef TESTSUITE
CoordinateQueue::CoordinateQueue(class MazeSolverApp *app)
{
    this->app = app;
    init();
}
#else
CoordinateQueue::CoordinateQueue()
{
    init();
}
#endif


/**
 * @brief Initializes the queue (student-implemented).
 */
void CoordinateQueue::init()
{
    front = NULL;
    rear = NULL;
}


/**
 * @brief Deinitializes the queue.
 */
CoordinateQueue::~CoordinateQueue()
{
    deinit();
}


/**
 * @brief Deletes all items in the queue (student-implemented).
 */
void CoordinateQueue::deinit()
{
    while (!is_empty())
    {
        queueitem *item = dequeue();
        delete item->c;
        delete item;
    }
}


/**
 * @brief Enqueues an item by adding it to the bottom of the
 * queue.
 *
 * @param[in] q Pointer to the item to be added.
 */
void CoordinateQueue::enqueue(queueitem *q)
{
    /* Do the operation. */
    do_enqueue(q);

//#ifndef TESTSUITE
    /* Update the display, if necessary. */
    //SDL_Delay(ANIMATION_DELAY);
    //this->app->OnRender();
//#endif
}


/**
 * @brief Do the actual enqueue operation (student-implemented).
 *
 * @param[in] q Pointer to the item to be added.
 */
void CoordinateQueue::do_enqueue(queueitem *q)
{
    if (front == NULL)
    {
        // Initialize an empty queue
        front = q;
        front->parent = NULL;
        front->next = NULL;
        rear = front;
    }
    else
    {
        queueitem *rear_prev = rear;
        rear = q;
        rear->next = NULL;
        rear->parent = rear_prev;
        rear_prev->next = rear;
    }
}


/**
 * @brief Dequeues and item by removing it from the top.
 *
 * @return Pointer to the dequeued item.
 */
queueitem *CoordinateQueue::dequeue()
{
    queueitem *res;

    /* Do the operation. */
    res = do_dequeue();
    return res;
}


/**
 * @brief Do the actual dequeue operation (student-implemented).
 *
 * @return Pointer to the dequeued item.
 */
queueitem *CoordinateQueue::do_dequeue()
{
    // Only dequeue the front node if it is not null
    if (front != NULL)
    {
        queueitem *front_prev = front;
        // Set front to front-> next (may be null)
        front = front->next;
        if (front != NULL)
        {
            front->parent = NULL;
        }
        return front_prev;
    }
    printf("Invalid dequeue\n");
    return NULL;
}

/**
 * @brief: Dequeue the entire queue, deleting all the items in the process.
 */
void CoordinateQueue::dequeue_all()
{
    while (!is_empty())
    {
        delete dequeue();
    }
}


/**
 * @brief Returns the item at the front of the queue without
 * removing it.
 *
 * @return Pointer to the first queue item.
 */
queueitem *CoordinateQueue::peek()
{
    return front;
}

/**
 * @brief Returns the item at the rear of the queue without
 * removing it.
 *
 * @return Pointer to the last queue item.
 */
queueitem *CoordinateQueue::peek_last()
{
    return rear;
}


/**
 * @brief Returns true is the queue is empty, false otherwise.
 *
 * @return Boolean indicating whether the queue is empty.
 */
bool CoordinateQueue::is_empty()
{
    if (front == NULL)
    {
        return true;
    }
    return false;
}
