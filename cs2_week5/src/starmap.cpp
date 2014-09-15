/**
* @file starmap.cpp
* @author Ben Yuan <<byuan@caltech.edu>>
* @version 1.0
* @date 2012-2014
* @copyright see License section
*
* @brief Defines a starmap and its associated capabilities.
*
* @section License
* Copyright (c) 2012-2014 California Institute of Technology.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The views and conclusions contained in the software and documentation are those
* of the authors and should not be interpreted as representing official policies,
* either expressed or implied, of the California Institute of Technology.
*
*/

#include "starmap.hpp"
#include <math.h>
#include <iostream>

/**
 * @brief Calculates the shortest path to the destination star.
 *
 * This calculates the shortest path to the destination star based on
 * the metrics provided in the CostSpec.
 *
 * @attention This is a student-written function.
 * Student may implement any shortest-path algorithm.
 * Remember: if implementing A*, don't overestimate the distance to goal.
 *
 * @param[in] src the origin point from which to find a path.
 * @param[in] dest the destination to find a path to.
 * @param[in] costs a cost specification for this calculation.
 *
 * @return a list of stars from the origin to the destination inclusive,
 * along the shortest path available.
 */
std::list<Star*> Starmap::shortestPath(Star * src, Star * dest, CostSpec costs)
{
    /*
     * Initialize all distances to zero.
     */
    Star *curr_star = src;
    std::map<int, Star *>::iterator i;
    std::vector<Star *> curr_edges;
    std::map<int, Star *> unvisited;
    std::list<Star *> shortest_path;
    double cost_base;
    double cost;
    double min_cost;
    double security;
    Star *new_star;
    // Reset values
    for (i = stars.begin(); i != stars.end(); i++)
    {
        int id = i->first;
        Star *star = i->second;
        star->cost = INFINITY;
        star->previous = NULL;
        star->visited = false;
        unvisited[id] = star;
    }
    curr_star->cost = 0;

    // Continue the algorithm until the destination is reached
    while (curr_star->getID() != dest->getID())
    {
        min_cost = INFINITY;
        curr_edges = curr_star->edges;
        std::vector<Star *>::iterator i;
        // Go through all neighboring stars
        for (i = curr_edges.begin(); i != curr_edges.end(); i++)
        {
            cost_base = costs.costPerNormalEdge;
            Star *star = *i;
            std::vector<Star *>::iterator j;
            if (costs.MSTEnabled)
            {
                // Check if an MST edge exists, if they are enabled
                for (j = curr_star->mst_edges.begin();
                        j != curr_star->mst_edges.end(); j++)
                {
                    Star *mst_star = *j;
                    if (star->getID() == mst_star->getID())
                    {
                        cost_base = costs.costPerMSTEdge;
                    }
                }
            }
            // Take security into account when calculating cost
            security = star->getSecStat();
            if (security >= .5)
            {
                cost = cost_base * costs.highSecCostMult;
            }
            else
            {
                cost = cost_base * costs.lowSecCostMult;
            }
            cost += curr_star->cost;

            // Set the cost of the neighboring star
            if (cost < star->cost && star->visited == false)
            {
                star->cost = cost;
                star->previous = curr_star;
            }
        }

        // Find the unvisited star with the smallest tentative distance
        unvisited.erase(curr_star->getID());
        std::map<int, Star *>::iterator k;
        for (k = unvisited.begin(); k != unvisited.end(); k++)
        {
            Star *star = k->second;
            if (star -> cost < min_cost)
            {
                min_cost = star->cost;
                new_star = star;
            }

        }

        // Mark current star as visited, proceed to cheapest neighbor
        curr_star->visited = true;
        curr_star = new_star;
    }

    // Construct the path
    while (curr_star != NULL)
    {
        shortest_path.push_back(curr_star);
        curr_star = curr_star->previous;
    }

    return shortest_path;

}

/**
 * @brief Calculates the minimum spanning tree of this starmap.
 *
 * This calculates the minimum spanning tree using the Cartesian metric,
 * optionally constrained to existing edges.
 *
 * The result is not passed by a return value. Instead, the mst_edges member
 * of every star is populated with the appropriate edges such that they
 * collectively define the MST.
 *
 * @attention This is a student-written function.
 * Student may implement any spanning-tree algorithm.
 * Prim's algorithm only works on fully connected subgraphs,
 * so you'll need a starting star within New Eden (and outside
 * Jove and CCP space) if you're not ignoring edges.
 *
 * @param[in] ignore_edges whether or not to pretend that every pair of stars
 *                         is connected by an edge.
 *
 */
void Starmap::generateMST(bool ignore_edges)
{
    /*
     * Clean up existing MST
     */
    std::map<int, Star *>::iterator i;
    std::map<int, Star *> mst;
    std::vector<Star *> all_stars; // Used when ignoring edges
    // Reset MST edges for all stars in map
    for (i = stars.begin(); i != stars.end(); i++)
    {
        int id = i->first;
        Star *star = i->second;
        star->mst_edges.clear();
        all_stars.push_back(star);
    }

    double min_dist = INFINITY;
    double dist;
    std::vector<Star *> curr_edges;
    Star *add_to_star;
    Star *add_star;
    Star *starting_star = stars[30000142];
    Star *curr_star;
    int add_id;
    mst[30000142] = starting_star;

    // Go until the MST spans all stars
    while (mst.size() < stars.size())
    {
        min_dist = INFINITY;
        std::map<int, Star *>::iterator j;
        // Go through each star in the MST and find the unvisited neighbor
        // that is cheapest to visit
        for (j = mst.begin(); j != mst.end(); j++)
        {
            curr_star = j->second;
            if (!ignore_edges)
            {
                curr_edges = curr_star->edges;
            }
            else
            {
                curr_edges = all_stars;
            }
            std::vector<Star *>::iterator i;
            // Find the cheapest neighboring star
            for (i = curr_edges.begin(); i != curr_edges.end(); i++)
            {
                Star *star = *i;
                dist = curr_star->cartesianDistanceTo(star);
                if (dist < min_dist && mst.count(star->getID()) != 1)
                {
                    add_id = star->getID();
                    min_dist = dist;
                    add_star = star;
                    add_to_star = curr_star;
                }
            }
        }
        // Add the mst edges to the star you are adding and the star
        // that is being added to, and add to the mst map
        add_to_star->mst_edges.push_back(add_star);
        add_star->mst_edges.push_back(add_to_star);
        mst[add_id] = add_star;
    }
}

/**
 * @brief Marks a path on the starmap.
 *
 * @param path A list of stars that should be connected by the renderer.
 */
void Starmap::markPath(std::list<Star*> path)
{
    std::map<int, Star *>::iterator f;
    for(f = this->stars.begin(); f != this->stars.end(); f++)
    {
        f->second->path_next = NULL;
    }

    std::list<Star*>::iterator i, j;
    for(i = path.begin(); i != path.end(); i++)
    {
        j = i;
        j++;
        if(j != path.end())
        {
            Star * u = *i;
            Star * v = *j;
            u->path_next = v;
        }
    }
}

/**
 * @brief Loads starmap data from the local database.
 *
 * This queries the local copy of the star database and loads all the
 * relevant information into this starmap object.
 */
void Starmap::loadStarmapFromDB()
{
    // First let's prepare all the relevant SQL stuff
    sqlite3 * db;
    int rc;
    int s_count = 0, e_count = 0;

    rc = sqlite3_open("map.db", &db);
    REQUIRE(rc == 0, "Can't open map database: %s", sqlite3_errmsg(db));

    INFO("Loading stars...");

    // We first load in all the stars
    sqlite3_stmt * ppstmt;
    const char * unused;
    // prepare the relevant SQL statement
    sqlite3_prepare_v2(db,
#if DATASET_FULL
    "SELECT solarSystemID, solarSystemName, x, y, z, security FROM solarSystems WHERE 1",
#else
    "SELECT solarSystemID, solarSystemName, x, y, z, security FROM solarSystems WHERE "
    "regionID = \"10000002\" OR regionID = \"10000016\" OR regionID = \"10000023\" OR regionID = \"10000033\"",
#endif
    -1,
    &ppstmt,
    &unused);

    // now step through it all the times
    while((rc = sqlite3_step(ppstmt)) == SQLITE_ROW)
    {
        // and create a bunch of stars
        int __id = sqlite3_column_int(ppstmt, 0);
        const unsigned char * __name = sqlite3_column_text(ppstmt, 1);
        double __x = sqlite3_column_double(ppstmt, 2) / 1e16;
        double __y = sqlite3_column_double(ppstmt, 3) / 1e16;
        double __z = sqlite3_column_double(ppstmt, 4) / 1e16;
        double __sec = sqlite3_column_double(ppstmt, 5);

        std::string __name_str((const char *)__name);

        Star * s = new Star(__id, __name_str, __x, __y, __z, __sec);
        this->addStar(s);
        //DEBUG("Added star %s (%d)", __name, __id);
        s_count++;
    }

    REQUIRE(rc == SQLITE_DONE, "Error reading stars: %s", sqlite3_errmsg(db));
    sqlite3_finalize(ppstmt);
    // Now all the stars are loaded yay

    // Now load all of the edges

    INFO("Loading edges...");

    sqlite3_prepare_v2(db,
#if DATASET_FULL
    "SELECT fromSolarSystemID, toSolarSystemID FROM solarSystemJumpn WHERE 1",
#else
    "SELECT fromSolarSystemID, toSolarSystemID FROM solarSystemJumpn WHERE "
    "(fromRegionID = \"10000002\" OR fromRegionID = \"10000016\" OR fromRegionID = \"10000023\" OR fromRegionID = \"10000033\")"
    "AND (toRegionID = \"10000002\" OR toRegionID = \"10000016\" OR toRegionID = \"10000023\" OR toRegionID = \"10000033\")",
#endif
    -1,
    &ppstmt,
    &unused);

    while((rc = sqlite3_step(ppstmt)) == SQLITE_ROW)
    {
        int from_id = sqlite3_column_int(ppstmt, 0);
        int to_id = sqlite3_column_int(ppstmt, 1);

        Star * p = this->stars[from_id];
        Star * q = this->stars[to_id];

        p->addEdgeTo(q);
        //DEBUG("Added link from star %s (%d) to star %s (%d)",
              //p->getName().c_str(), from_id, q->getName().c_str(), to_id);
        e_count++;
    }

    REQUIRE(rc == SQLITE_DONE, "Error reading edges: %s", sqlite3_errmsg(db));
    sqlite3_finalize(ppstmt);


    // We are now loaded yay

    sqlite3_close(db);
    INFO("%d stars, %d edges", s_count, e_count);
    INFO("Starmap loaded with %d stars", this->stars.size());

    // Select Itamo and Jakanerva by default just because

    this->selected_star = this->stars[30000119];
    this->selected_star_2 = this->stars[30000148];

}

/**
 * @brief Renders all the stars in this starmap.
 */

void Starmap::render(double dist, double azm, double alt, bool pick)
{
#ifndef NO_GFX
    std::map<int, Star*>::iterator i;

    // before we draw anything we orient our viewpoint in space
    // we do transforms in OpenGL backwards because matrix math

    // and last we zoom out
    glTranslated(0, 0, dist);
    // then we rotate the whole thing
    glRotated(alt, 1, 0, 0);
    glRotated(azm, 0, 1, 0);
    // then we scale the whole thing to avoid funny render glitches
    glScaled(1e-2, 1e-2, 1e-2);
    // so first we center ourselves on our focus star
    GLdouble * focus_coords;
    if(this->focus_star != NULL)
    {
        focus_coords = this->focus_star->getCoords();
        glTranslated(-focus_coords[0], -focus_coords[1], -focus_coords[2]);
    }

    // now we're correctly oriented in space so we can draw stuff yay

    // first render all the edges
    if(!pick)
    {
        glBegin(GL_LINES);

        for(i = this->stars.begin(); i != this->stars.end(); i++)
        {
            Star * s = i->second;
            s->drawEdges();

        }

        glEnd();

        // edges should be behind everything
        // so we clear the zbuffer
        // (the effect is that everything afterwards gets rendered
        // "in front" of the edges)
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    // then render all the stars

    for(i = this->stars.begin(); i != this->stars.end(); i++)
    {
        Star * s = i->second;
        glPushName(s->getID());
        glBegin(GL_POINTS);
        s->glColor3d();
        s->glVertex3d();
        glEnd();
        glPopName();
    }

    // then we want to render the selection diamonds
    if(!pick)
    {
        if(this->selected_star != NULL)
        {
            // this one is blue
            glColor4d(0.0, 0.5, 1.0, 0.5);
            // we center it on the source star
            GLdouble * coords = this->selected_star->getCoords();
            GLdouble x = coords[0];
            GLdouble y = coords[1];
            GLdouble z = coords[2];

            // we push a new matrix onto the matrix stack
            // so we can do funny transforms on this octahedron
            // without messing up anything else
            glPushMatrix();

            // everything is backwards again because matrix math and OpenGL
            // and then we move the octahedron into place
            glTranslated(x, y, z);
            // first we scale the octahedron
            // so that it has a more-or-less constant size on the screen
            glScaled(1, 1, 1);
            glScaled(dist, dist, dist);
            // transform is set up; draw the octahedron
            glutSolidOctahedron();

            // finally we pop the matrix now that the octahedron is drawn
            // so it doesn't mess with subsequent draw calls
            glPopMatrix();
        }

        if(this->selected_star_2 != NULL)
        {
            // this one is orange
            glColor4d(1.0, 0.5, 0.0, 0.5);
            // we do more or less the same thing as above
            // (see above for the details)
            GLdouble * coords = this->selected_star_2->getCoords();
            GLdouble x = coords[0];
            GLdouble y = coords[1];
            GLdouble z = coords[2];

            glPushMatrix();
            glTranslated(x, y, z);
            glScaled(1, 1, 1);
            glScaled(dist, dist, dist);
            glutSolidOctahedron();
            glPopMatrix();
        }
    }
#endif
}

/**
 * @brief Selects the star clicked on by mouse.
 *
 * We do this by putting ourselves into GL_SELECT mode,
 * then rendering everything while constraining ourselves
 * to a tiny little box around the mouse coordinates.
 * We take note of any stars that rendered within the box,
 * and select the closest of these to the viewpoint (if any).
 *
 * This code is based on code provided by Antonio Ramirez
 * <arf@di.uminho.pt> in his tutorial on picking in OpenGL,
 * available at the following URL:\n
 * <http://www.lighthouse3d.com/opengl/picking/>\n
 * He has graciously given us permission to use the code
 * as we see fit.
 *
 */
void Starmap::mouseSelect(int which, int x, int y, double dist, double azm, double alt)
{
#ifndef NO_GFX
    GLint viewport[4];
    double ratio;
    GLint hits;
    GLuint selectBuf[4096];

    // define a select buffer
    glSelectBuffer(1024,selectBuf);

    // grab the current viewport settings
    glGetIntegerv(GL_VIEWPORT,viewport);

    // get ourselves into selection mode
    glRenderMode(GL_SELECT);

    // and prepare to use the selection functionality
    glInitNames();

    // set up the projection matrix for picking
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    // we want a small 9x9 square centered on the mouseclick
    gluPickMatrix(x,viewport[3]-y,9,9,viewport);
    ratio = (viewport[2]+0.0) / viewport[3];
    gluPerspective(45, (double)WIDTH/HEIGHT, .0001, 1000);

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    this->render(dist, azm, alt, true);

    // switch back to normal rendering mode
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glFlush();
    // in the process we see if we got any hits
    hits = glRenderMode(GL_RENDER);

    // and so we did;
    // let's see if we recognise anything
    if (hits != 0){
        GLint i, j, numberOfNames;
        GLuint names, *ptr, minZ, *ptrNames;

        ptr = (GLuint *) selectBuf;
        minZ = 0xffffffff;
        for (i = 0; i < hits; i++) {
            names = *ptr;
            ptr++;
            if (*ptr < minZ) {
                numberOfNames = names;
                minZ = *ptr;
                ptrNames = ptr+2;
            }

            ptr += names+2;
        }
        // if we recognise some star we select it
        if (numberOfNames > 0) {
            ptr = ptrNames;
            Star * u = this->stars[*ptr];
            INFO("Selecting star %s (%d), sec %.2f", u->getName().c_str(),
                    u->getID(), u->getSecStat());

            if(which == 0)
            {
                this->selected_star = u;
            }
            else if(which == 1)
            {
                this->selected_star_2 = u;
            }
            else if(which == 2)
            {
                this->setFocus(u);
            }

        }

    }
#endif
}
