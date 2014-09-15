/**
 * @file QuadtreeNode.h
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Common structures for use by quadtrees.
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

#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <vector>

using namespace std;

struct coordinate
{
    float x, y;

    coordinate(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    coordinate(coordinate *c)
    {
        this->x = c->x;
        this->y = c->y;
    }

    bool operator==(const coordinate &param)
    {
        if ((this->x == param.x) && (this->y == param.y))
            return true;
        else
            return false;
    }
};


struct rect
{
    coordinate *ul;
    coordinate *br;

    rect(coordinate *ul, coordinate *br)
    {
        this->ul = ul;
        this->br = br;
    }

    rect(rect *r)
    {
        this->ul->x = r->ul->x;
        this->ul->y = r->ul->y;
        this->br->x = r->br->x;
        this->br->y = r->br->y;
    }

    bool operator==(const rect &param)
    {
        if ((this->ul->x == param.ul->x) && (this->ul->y == param.ul->y) &&
        (this->br->x == param.br->x) && (this->br->y == param.br->y))
            return true;
        else
            return false;
    }
};


struct query
{
    vector<coordinate*> points;
    vector<rect*> boxes;

    query(vector<coordinate*> points, vector<rect*> boxes)
    {
        this->points = points;
        this->boxes = boxes;
    }
};

#endif
