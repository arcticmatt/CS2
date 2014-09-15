/**
 * @file RaytracerApp.h
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Definitions for the main application class.
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

#ifndef __RAYTRACERAPP_H__
#define __RAYTRACERAPP_H__

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include "World.h"
#include "Shader.h"
#include "XMLSceneParser.h"
#include "RaytracerBase.h"
#include "RaytracerSinglethreaded.h"
#include "RaytracerMultithreaded.h"

#define RAYTRACER_SINGLETHREADED    (0)
#define RAYTRACER_MULTITHREADED     (1)

#define SCREEN_WIDTH    (800)
#define SCREEN_HEIGHT   (600)


/**
 * @brief Encapsulates the main application class.
 */
class RaytracerApp
{
public:
    RaytracerApp();
    ~RaytracerApp();
    
    bool OnInit();
    int OnExecute();
    void OnEvent(SDL_Event *event);
    void OnRender();
    void OnCleanup();
    
    void SetMode(int mode);
    
private:
    bool running;
    SDL_Surface *surf;
    
    World *world;
    Shader *shader;
    Viewport *vp;
    RaytracerBase *raytracer;
    int mode;
};

#endif
