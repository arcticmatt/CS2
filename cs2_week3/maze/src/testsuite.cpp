/**
 * @file testsuite.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Performs tests of the CoordinateQueue and CoordinateStack classes.
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
#include "CoordinateQueue.h"
#include <stdio.h>

int main()
{
    /* Do your testing here. */
    printf("Testing the stack\n");
    CoordinateStack stack;
    for (int i = 0; i < 10; i++)
    {
        stackitem *item = new stackitem();
        coordinate *coord = new coordinate();
        coord->x = i;
        coord->y = i;
        item->c = coord;
        stack.push(item);
        printf("Push... x: %d, y: %d\n", item->c->x, item->c->y);
    }
    for (int i = 0; i < 10; i++)
    {
        stackitem *item = stack.pop();
        printf("Pop... x: %d, y: %d\n", item->c->x, item->c->y);
        delete item->c;
        delete item;
    }
    stack.pop();

    printf("\nTesting the queue\n");
    CoordinateQueue queue;
    for (int i = 0; i < 10; i++)
    {
        queueitem *item = new queueitem();
        coordinate *coord = new coordinate();
        coord->x = i;
        coord->y = i;
        item->c = coord;
        queue.enqueue(item);
        printf("Enqueue... x: %d, y: %d\n", item->c->x, item->c->y);
    }
    for (int i = 0; i < 10; i++)
    {
        queueitem *item = queue.dequeue();
        printf("Dequeue... x: %d, y: %d\n", item->c->x, item->c->y);
        delete item->c;
        delete item;
    }
    queue.dequeue();

    return 0;
}
