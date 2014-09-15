/*
 * SeamCarveApp.cpp
 * Defines the SeamCarveApp main application class.
 *
 * Copyright 2014 Ellen Price <eprice@caltech.edu>
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
 *
 */

#include "SeamCarveApp.h"

#define get(obj, x, y)      (obj[(x) + w0 * (y)])
#define min(x, y)           ((x) < (y) ? (x) : (y))

/**
 * @brief Initializes the application class.
 */
SeamCarveApp::SeamCarveApp()
{
    /* Do SDL initialization. */
    screen = NULL;
    image = NULL;
    energy = NULL;
    trace = NULL;
    nseams = 0;
    running = true;
}


/**
 * @brief Deinitializes the application class.
 */
SeamCarveApp::~SeamCarveApp()
{
    free(smap);
}


/**
 * @brief This is the main application loop; it runs until program exit.
 */
int SeamCarveApp::OnExecute()
{
    SDL_Event Event;

    if(OnInit() == false)
    {
        return -1;
    }

    OnRender();

    while (running)
    {
        while(SDL_PollEvent(&Event))
        {
            OnEvent(&Event);
            OnRender();
        }
    }

    OnCleanup();

    return 0;
}


/**
 * @brief This code is run on application start and should perform all
 * initialization for SDL.
 */
bool SeamCarveApp::OnInit()
{
    SDL_Surface *temp;

    /* Initialize *all* the things! */
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    /* Load bitmap and set size of main screen. */
    temp = SDL_LoadBMP(IMG_NAME);

    if (temp == NULL)
    {
        return false;
    }

    screen = SDL_SetVideoMode(temp->w, temp->h, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if(screen == NULL)
    {
        return false;
    }

    image = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    /* Create the energy surface. */
    energy = SDL_CreateRGBSurface(SDL_SWSURFACE, image->w, image->h, 32,
            0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

    if (energy == NULL)
    {
        return false;
    }

    /* Create the seam trace surface. */
    trace = SDL_CreateRGBSurface(SDL_SWSURFACE, image->w, image->h, 32,
            0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

    if (trace == NULL)
    {
        return false;
    }

    /* Create a saliency map for student implementation. */
    smap = (unsigned int *) malloc(sizeof(unsigned int) * image->w * image->h);

    /* This is necessary to receive Unicode keycodes. */
    SDL_EnableUNICODE(1);

    /* Display the image by default. */
    cursurf = image;
    ComputeSaliencyMap();

    return true;
}


/**
 * @brief This function is called on keypresses, clicks, etc. The
 * parameter `event` describes the event that occurred.
 */
void SeamCarveApp::OnEvent(SDL_Event* event)
{
    if(event->type == SDL_QUIT)
    {
        running = false;
    }
    else if (event->type == SDL_KEYDOWN)
    {
        if (event->key.keysym.unicode == 'q')
        {
            running = false;
        }
        else if (event->key.keysym.unicode == 'e')
        {
            /* Display energy surface. */
            cursurf = energy;
        }
        else if (event->key.keysym.unicode == 'i')
        {
            /* Display image surface. */
            cursurf = image;
        }
        else if (event->key.keysym.unicode == 'f')
        {
            /* Find and highlight seam without carving it. */
            SeamHighlight();
        }
        else if (event->key.keysym.unicode == ' ')
        {
            /* Carve a seam and compute a new saliency map. */
            SeamCarve();
            ComputeSaliencyMap();
        }
    }
}


/**
 * @brief This function renders everything; it is only called once on
 * startup and then to animate solver moves.
 */
void SeamCarveApp::OnRender()
{
    SDL_Rect src, dest;

    src.x = 0;
    src.y = 0;
    src.w = image->w;
    src.h = image->h;

    dest.x = 0;
    dest.y = 0;
    dest.w = image->w;
    dest.h = image->h;

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_BlitSurface(cursurf, &src, screen, &dest);
    SDL_BlitSurface(trace, &src, screen, &dest);
    SDL_Flip(screen);
}


/**
 * @brief This function performs all cleanup needed by SDL.
 */
void SeamCarveApp::OnCleanup()
{
    SDL_Quit();
}


/**
 * @brief Computes the saliency map of the image already loaded into the
 * SDL surface `image`.
 */
void SeamCarveApp::ComputeSaliencyMap()
{
    int i, j;
    int w = image->w - nseams, h = image->h, w0 = image->w;
    unsigned int r, g, b, avg;

    sRGB32 *xmap = (sRGB32 *) malloc(sizeof(sRGB32) * w0 * h);
    sRGB32 *ymap = (sRGB32 *) malloc(sizeof(sRGB32) * w0 * h);

    SDL_LockSurface(image);
    SDL_LockSurface(energy);

    uRGB32 *pix = (uRGB32 *) image->pixels;
    uRGB32 *epix = (uRGB32 *) energy->pixels;

    for (i = 0; i < w; i++)
    {
        for (j = 0; j < h; j++)
        {
            if ((i == 0) && (j == 0))
            {
                /* Upper left corner */
                get(xmap, i, j).r = -2 * get(pix, 1, 0).r + -1 * get(pix, 1, 1).r;
                get(xmap, i, j).g = -2 * get(pix, 1, 0).g + -1 * get(pix, 1, 1).g;
                get(xmap, i, j).b = -2 * get(pix, 1, 0).b + -1 * get(pix, 1, 1).b;

                get(ymap, i, j).r = -2 * get(pix, 0, 1).r + -1 * get(pix, 1, 1).r;
                get(ymap, i, j).g = -2 * get(pix, 0, 1).g + -1 * get(pix, 1, 1).g;
                get(ymap, i, j).b = -2 * get(pix, 0, 1).b + -1 * get(pix, 1, 1).b;
            }
            else if ((i == w - 1) && (j == 0))
            {
                /* Upper right corner */
                get(xmap, i, j).r = 2 * get(pix, w - 2, 0).r + 1 * get(pix, w - 2, 1).r;
                get(xmap, i, j).g = 2 * get(pix, w - 2, 0).g + 1 * get(pix, w - 2, 1).g;
                get(xmap, i, j).b = 2 * get(pix, w - 2, 0).b + 1 * get(pix, w - 2, 1).b;

                get(ymap, i, j).r = -1 * get(pix, w - 2, 1).r + -2 * get(pix, w - 2, 0).r;
                get(ymap, i, j).g = -1 * get(pix, w - 2, 1).g + -2 * get(pix, w - 2, 0).g;
                get(ymap, i, j).b = -1 * get(pix, w - 2, 1).b + -2 * get(pix, w - 2, 0).b;
            }
            else if ((i == 0) && (j == h - 1))
            {
                /* Lower left corner */
                get(xmap, i, j).r = -1 * get(pix, 1, h - 2).r + -2 * get(pix, 1, h - 1).r;
                get(xmap, i, j).g = -1 * get(pix, 1, h - 2).g + -2 * get(pix, 1, h - 1).g;
                get(xmap, i, j).b = -1 * get(pix, 1, h - 2).b + -2 * get(pix, 1, h - 1).b;

                get(ymap, i, j).r = 2 * get(pix, 0, h - 2).r + 1 * get(pix, 1, h - 2).r;
                get(ymap, i, j).g = 2 * get(pix, 0, h - 2).g + 1 * get(pix, 1, h - 2).g;
                get(ymap, i, j).b = 2 * get(pix, 0, h - 2).b + 1 * get(pix, 1, h - 2).b;
            }
            else if ((i == w - 1) && (j == h - 1))
            {
                /* Lower right corner */
                get(xmap, i, j).r = 1 * get(pix, w - 2, h - 2).r + 2 * get(pix, w - 2, h - 1).r;
                get(xmap, i, j).g = 1 * get(pix, w - 2, h - 2).g + 2 * get(pix, w - 2, h - 1).g;
                get(xmap, i, j).b = 1 * get(pix, w - 2, h - 2).b + 2 * get(pix, w - 2, h - 1).b;

                get(ymap, i, j).r = 1 * get(pix, w - 2, h - 2).r + 2 * get(pix, w - 1, h - 2).r;
                get(ymap, i, j).g = 1 * get(pix, w - 2, h - 2).g + 2 * get(pix, w - 1, h - 2).g;
                get(ymap, i, j).b = 1 * get(pix, w - 2, h - 2).b + 2 * get(pix, w - 1, h - 2).b;
            }
            else if (i == 0)
            {
                /* Left edge, not corner */
                get(xmap, i, j).r = -1 * get(pix, 0, j - 1).r - 2 * get(pix, 0, j).r - 1 * get(pix, 0, j + 1).r;
                get(xmap, i, j).g = -1 * get(pix, 0, j - 1).g - 2 * get(pix, 0, j).g - 1 * get(pix, 0, j + 1).g;
                get(xmap, i, j).b = -1 * get(pix, 0, j - 1).b - 2 * get(pix, 0, j).b - 1 * get(pix, 0, j + 1).b;

                get(ymap, i, j).r = 1 * get(pix, 0, j - 1).r - 1 * get(pix, 0, j + 1).r;
                get(ymap, i, j).g = 1 * get(pix, 0, j - 1).g - 1 * get(pix, 0, j + 1).g;
                get(ymap, i, j).b = 1 * get(pix, 0, j - 1).b - 1 * get(pix, 0, j + 1).b;
            }
            else if (j == 0)
            {
                /* Top edge, not corner */
                get(xmap, i, j).r = 1 * get(pix, i - 1, 0).r - 1 * get(pix, i + 1, 0).r;
                get(xmap, i, j).g = 1 * get(pix, i - 1, 0).g - 1 * get(pix, i + 1, 0).g;
                get(xmap, i, j).b = 1 * get(pix, i - 1, 0).b - 1 * get(pix, i + 1, 0).b;

                get(ymap, i, j).r = -1 * get(pix, i - 1, 0).r - 2 * get(pix, i, 0).r - 1 * get(pix, i + 1, 0).r;
                get(ymap, i, j).g = -1 * get(pix, i - 1, 0).g - 2 * get(pix, i, 0).g - 1 * get(pix, i + 1, 0).g;
                get(ymap, i, j).b = -1 * get(pix, i - 1, 0).b - 2 * get(pix, i, 0).b - 1 * get(pix, i + 1, 0).b;
            }
            else if (i == w - 1)
            {
                /* Right edge, not corner */
                get(xmap, i, j).r = 1 * get(pix, w - 1, j - 1).r + 2 * get(pix, w - 1, j).r + 1 * get(pix, w - 1, j + 1).r;
                get(xmap, i, j).g = 1 * get(pix, w - 1, j - 1).g + 2 * get(pix, w - 1, j).g + 1 * get(pix, w - 1, j + 1).g;
                get(xmap, i, j).b = 1 * get(pix, w - 1, j - 1).b + 2 * get(pix, w - 1, j).b + 1 * get(pix, w - 1, j + 1).b;

                get(ymap, i, j).r = 1 * get(pix, w - 1, j - 1).r - 1 * get(pix, w - 1, j + 1).r;
                get(ymap, i, j).g = 1 * get(pix, w - 1, j - 1).g - 1 * get(pix, w - 1, j + 1).g;
                get(ymap, i, j).b = 1 * get(pix, w - 1, j - 1).b - 1 * get(pix, w - 1, j + 1).b;
            }
            else if (j == h - 1)
            {
                /* Bottom edge, not corner */
                get(xmap, i, j).r = 1 * get(pix, i - 1, h - 1).r - 1 * get(pix, i + 1, h - 1).r;
                get(xmap, i, j).g = 1 * get(pix, i - 1, h - 1).g - 1 * get(pix, i + 1, h - 1).g;
                get(xmap, i, j).b = 1 * get(pix, i - 1, h - 1).b - 1 * get(pix, i + 1, h - 1).b;

                get(ymap, i, j).r = 1 * get(pix, i - 1, h - 1).r + 2 * get(pix, i, h - 1).r + 1 * get(pix, i + 1, h - 1).r;
                get(ymap, i, j).g = 1 * get(pix, i - 1, h - 1).g + 2 * get(pix, i, h - 1).g + 1 * get(pix, i + 1, h - 1).g;
                get(ymap, i, j).b = 1 * get(pix, i - 1, h - 1).b + 2 * get(pix, i, h - 1).b + 1 * get(pix, i + 1, h - 1).b;
            }
            else
            {
                /* All other pixels */
                get(xmap, i, j).r = 1 * get(pix, i - 1, j - 1).r + 2 * get(pix, i - 1, j).r + 1 * get(pix, i - 1, j + 1).r
                    - 1 * get(pix, i + 1, j - 1).r - 2 * get(pix, i + 1, j).r - 1 * get(pix, i + 1, j + 1).r;
                get(xmap, i, j).g = 1 * get(pix, i - 1, j - 1).g + 2 * get(pix, i - 1, j).g + 1 * get(pix, i - 1, j + 1).g
                    - 1 * get(pix, i + 1, j - 1).g - 2 * get(pix, i + 1, j).g - 1 * get(pix, i + 1, j + 1).g;
                get(xmap, i, j).b = 1 * get(pix, i - 1, j - 1).b + 2 * get(pix, i - 1, j).b + 1 * get(pix, i - 1, j + 1).b
                    - 1 * get(pix, i + 1, j - 1).b - 2 * get(pix, i + 1, j).b - 1 * get(pix, i + 1, j + 1).b;

                get(ymap, i, j).r = 1 * get(pix, i - 1, j - 1).r + 2 * get(pix, i, j - 1).r + 1 * get(pix, i + 1, j - 1).r
                    - 1 * get(pix, i - 1, j + 1).r - 2 * get(pix, i, j + 1).r - 1 * get(pix, i + 1, j + 1).r;
                get(ymap, i, j).g = 1 * get(pix, i - 1, j - 1).g + 2 * get(pix, i, j - 1).g + 1 * get(pix, i + 1, j - 1).g
                    - 1 * get(pix, i - 1, j + 1).g - 2 * get(pix, i, j + 1).g - 1 * get(pix, i + 1, j + 1).g;
                get(ymap, i, j).b = 1 * get(pix, i - 1, j - 1).b + 2 * get(pix, i, j - 1).b + 1 * get(pix, i + 1, j - 1).b
                    - 1 * get(pix, i - 1, j + 1).b - 2 * get(pix, i, j + 1).b - 1 * get(pix, i + 1, j + 1).b;
            }
        }
    }

    for (i = 0; i < w; i++)
    {
        for (j = 0; j < h; j++)
        {
            r = sqrt(get(xmap, i, j).r * get(xmap, i, j).r + get(ymap, i, j).r * get(ymap, i, j).r);
            g = sqrt(get(xmap, i, j).g * get(xmap, i, j).g + get(ymap, i, j).g * get(ymap, i, j).g);
            b = sqrt(get(xmap, i, j).b * get(xmap, i, j).b + get(ymap, i, j).b * get(ymap, i, j).b);
            avg = int((r + g + b) / 3);

            get(epix, i, j).r = avg;
            get(epix, i, j).g = avg;
            get(epix, i, j).b = avg;
            get(epix, i, j).a = 0xff;

            get(smap, i, j) = avg;
        }
    }

    SDL_UnlockSurface(energy);
    SDL_UnlockSurface(image);
    free(xmap);
    free(ymap);
}


/**
 * @brief Find a seam and then carve it from the image.
 */
void SeamCarveApp::SeamCarve()
{
    int i, j;
    int w = image->w - nseams, h = image->h, w0 = image->w;
    unsigned int *seam = DoSeamCarve(smap, w, image->w, h);

    SDL_LockSurface(image);
    SDL_LockSurface(trace);
    SDL_LockSurface(energy);

    uRGB32 *pix = (uRGB32 *) image->pixels;
    uRGB32 *pix2 = (uRGB32 *) trace->pixels;
    uRGB32 *pix3 = (uRGB32 *) energy->pixels;

    /* For each pixel in the seam... */
    for (j = 0; j < h; j++)
    {
        /* For each pixel to the right... */
        for (i = seam[j] + 1; i < w; i++)
        {
            get(pix, i-1, j).r = get(pix, i, j).r;
            get(pix, i-1, j).g = get(pix, i, j).g;
            get(pix, i-1, j).b = get(pix, i, j).b;
        }
    }

    /* Black out the last column on image and energy surfaces. */
    for (j = 0; j < h; j++)
    {
        get(pix, w-1, j).r = 0;
        get(pix, w-1, j).g = 0;
        get(pix, w-1, j).b = 0;

        get(pix3, w-1, j).r = 0;
        get(pix3, w-1, j).g = 0;
        get(pix3, w-1, j).b = 0;
    }

    /* "Clear" the trace surface (by setting alpha to 0 for all pixels). */
    for (i = 0; i < w0; i++)
    {
        for (j = 0; j < h; j++)
        {
            get(pix2, i, j).a = 0;
        }
    }

    SDL_UnlockSurface(image);
    SDL_UnlockSurface(trace);
    SDL_UnlockSurface(energy);
    free(seam);

    /* Update the seam count. */
    nseams++;
}


/**
 * @brief Find a seam, but do not carve it; highlight in yellow.
 */
void SeamCarveApp::SeamHighlight()
{
    int i, j;
    int w = image->w - nseams, h = image->h, w0 = image->w;
    unsigned int *seam = DoSeamCarve(smap, w, image->w, h);

    SDL_LockSurface(trace);
    uRGB32 *pix = (uRGB32 *) trace->pixels;

    /* "Clear" the surface (by setting alpha to 0 for all pixels). */
    for (i = 0; i < w0; i++)
    {
        for (j = 0; j < h; j++)
        {
            get(pix, i, j).a = 0;
        }
    }

    /* For each pixel in the seam... */
    for (j = 0; j < h; j++)
    {
        /* ...color yellow and set alpha to 255. */
        get(pix, seam[j], j).r = 255;
        get(pix, seam[j], j).g = 255;
        get(pix, seam[j], j).b = 0;
        get(pix, seam[j], j).a = 255;
    }

    SDL_UnlockSurface(trace);
    free(seam);
}

unsigned int getMin(unsigned int num1, unsigned int num2, unsigned int num3)
{
    if (num1 <= num2 && num1 <= num3)
    {
        return num1;
    }
    else if (num2 <= num1 && num2 <= num3)
    {
        return num2;
    }
    return num3;
}

unsigned int getMin(unsigned int num1, unsigned int num2)
{
    if (num1 <= num2)
    {
        return num1;
    }
    return num2;
}
/**
 * @brief Function that finds a vertical seam and returns it.
 *
 * @param[in] smap 2-d array of width `w0` and height `h` with relative
 * energies of each pixel. NOTE: You should only use data in `smap` on
 * the dimensions width = `w`, height = `h`; see comments in function
 *
 * @param[in] w Current width of image (and width of valid `smap` data)
 *
 * @param[in] w0 Width of original image; needed for addressing (see below)
 *
 * @param[in] h Height of image (and height of `smap` array)
 *
 * @return 1-d array of size `h` containing the x-coordinate of each
 * pixel in the seam, starting at the top
 */
unsigned int *DoSeamCarve(unsigned int *smap, int w, int w0, int h)
{
    /*
     * The energy array `smap` is technically single-dimensional, so you
     * cannot index it as a 2-D array. To overcome this, you are provided
     * its full width `w0` and height `h`; the formula for addressing
     * a single element in `smap` is then:
     *     smap[x + w0 * y]
     * Valid data is only stored on the width `w`, however (because the
     * image gets smaller each time you carve a seam). So you should use
     * `w0` to address `smap`, but you should never look at its contents
     * for x > `w` - 1.
     *
     * If you find the notation above a bit tedious, you can also
     * use the provided macro, `get`, as follows:
     *     get(smap, x, y) = q;
     *     p = get(smap, x, y);
     * If you look at the definiton of `get`, you will see that they
     * are equivalent.
     */

    int insert_min;
    int row_min;
    int row_min_index;
    int insert_seam;
    int curr_elem;
    unsigned int *seam = (unsigned int *) malloc(sizeof(unsigned int) * h);
    unsigned int *cost_table = (unsigned int *) malloc(sizeof(unsigned int)
            * w0 * h);

    /*
     * Copy the first row of the smap into the cost table.
     */
    for (int i = 0; i < w; i++)
    {
        get(cost_table, i, 0) = get(smap, i, 0);
    }

    /*
     * Make the cost table. Basically, each index of the cost table is
     * calculated by summing the corresponding value at that index in the
     * smap with the minimum values of the 3 (or 2) values above it.
     */
    for (int i = 1; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (j == 0)
            {
                // Edge case: left edge
                insert_min = getMin(get(cost_table, j, i - 1),
                        get(cost_table, j + 1, i - 1));
                get(cost_table, j, i) = get(smap, j, i) + insert_min;
            }
            else if (j == w - 1)
            {
                // Edge case: right edge
                insert_min = getMin(get(cost_table, j - 1, i - 1),
                        get(cost_table, j, i - 1));
                get(cost_table, j, i) = get(smap, j, i) + insert_min;
            }
            else
            {
                insert_min = getMin(get(cost_table, j - 1, i - 1),
                        get(cost_table, j, i - 1),
                        get(cost_table, j + 1, i - 1));
                get(cost_table, j, i) = get(smap, j, i) + insert_min;
            }
        }
    }

    // Traverse bottom row of cost table, finding the index of the min
    row_min_index = 0;
    row_min = get(cost_table, row_min_index, h - 1);
    for (int i = 0; i < w; i++)
    {
        curr_elem = get(cost_table, i, h - 1);
        if (curr_elem < row_min)
        {
            row_min = curr_elem;
            row_min_index = i;
        }
    }

    /*
     * Find the path to the top, starting at the minimum value of the
     * bottom row, and store all the x indices in seam.
     */
    seam[h - 1] = row_min_index;
    for (int i = h - 2; i >= 0; i--)
    {
            if (row_min_index == 0)
            {
                if (get(cost_table, row_min_index, i)
                        < get(cost_table, row_min_index + 1, i))
                {
                    insert_seam = row_min_index;
                }
                else
                {
                    insert_seam = row_min_index + 1;
                }
            }
            else if (row_min_index == w - 1)
            {
                if (get(cost_table, row_min_index, i)
                        < get(cost_table, row_min_index - 1, i))
                {
                    insert_seam = row_min_index;
                }
                else
                {
                    insert_seam = row_min_index - 1;
                }

            }
            else
            {
                if (get(cost_table, row_min_index - 1, i)
                        < get(cost_table, row_min_index, i)
                        && get(cost_table, row_min_index - 1, i)
                        < get(cost_table, row_min_index + 1, i))
                {
                    insert_seam = row_min_index - 1;
                }
                else if (get(cost_table, row_min_index, i)
                        < get(cost_table, row_min_index + 1, i)
                        && get(cost_table, row_min_index, i)
                        < get(cost_table, row_min_index - 1, i))

                {
                    insert_seam = row_min_index;
                }
                else if (get(cost_table, row_min_index + 1, i)
                        < get(cost_table, row_min_index, i)
                        && get(cost_table, row_min_index + 1, i)
                        < get(cost_table, row_min_index - 1, i))
                {
                    insert_seam = row_min_index + 1;
                }
            }
            seam[i] = insert_seam;
            row_min_index = insert_seam;
    }

    printf("Seam carved\n");
    return seam;
}




/**
 * @brief Spawn the application class.
 */
int main(int argc, char* argv[])
{
    SeamCarveApp app;
    return app.OnExecute();
}
