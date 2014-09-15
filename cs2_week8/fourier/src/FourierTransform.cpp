/**
 * @file FourierTransform.cpp
 * @author Justin Johnson, revised by Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Functions for the FourierTransform namespace.
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

#include "FourierTransform.hpp"
#include <math.h>

#define ndx(obj,i,j,n)      (obj[(i)+(j)*n])


/**
 * @brief Computes the discrete Fourier transform of the input data using
 * naive iteration.
 *
 * @attention This is a student-implemented function.
 *
 * @param input The complex numbers to be transformed.
 *
 * @param n The length of the input array.
 *
 * @return An array of complex numbers containing the discrete Fourier
 * transform of the input data.
 */
ComplexNumber *FourierTransform::slow_transform(ComplexNumber *input, int n)
{
    ComplexNumber **special_matrix = new ComplexNumber*[n];
    ComplexNumber *output = new ComplexNumber[n];
    ComplexNumber insert;
    ComplexNumber result;
    // blahhhhhh
    for (int i = 0; i < n; i++)
    {
        special_matrix[i] = new ComplexNumber[n];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            insert = ComplexNumber::getRootOfUnity(n, i * j) * (1 / pow(n, .5));
            special_matrix[i][j] = insert;
        }
    }

    for (int i = 0; i < n; i++)
    {
        result = ComplexNumber::fromReal(0);
        for (int j = 0; j < n; j++)
        {
            result = result + special_matrix[j][i] * input[i];
            output[i] = insert;
        }
    }

    return output;
}


/**
 * @brief Computes the discrete Fourier transform of the input data using
 * recursion.
 *
 * @attention This is a student-implemented function.
 *
 * @param input The complex numbers to be transformed.
 *
 * @param n The length of the input array.
 *
 * @return An array of complex numbers containing the discrete Fourier
 * transform of the input data.
 */
ComplexNumber *FourierTransform::fast_transform(ComplexNumber *input, int n)
{
    ComplexNumber *output = new ComplexNumber[n];
    return output;
}


/**
 * The standard one-dimensional forward Fourier transform with real input.
 *
 * @param input An array of real numbers to transform.
 *
 * @param n The length of the input array.
 *
 * @return The Fourier transform of the input.
 */
ComplexNumber *FourierTransform::transform(double *input, int n)
{
    ComplexNumber *complex = new ComplexNumber[n];

    for (int i = 0; i < n; i++)
        complex[i] = ComplexNumber::fromReal(input[i]);

    return transform(complex, n);
}


/**
 * @brief Performs a two-dimensional (forward) Fourier transform on
 * complex data.
 *
 * @param input A rectangular array of complex numbers to tranform, of
 * size n*m.
 *
 * @param n The width of the input array.
 *
 * @param m The height of the input array.
 *
 * @return The Fourier transform of the input.
 */
ComplexNumber *FourierTransform::transform(ComplexNumber *input, int n, int m)
{
    int height = m;
    int width = n;

    ComplexNumber *step1 = new ComplexNumber[height*width];
    ComplexNumber *row = new ComplexNumber[width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            row[j] = ndx(input, j, i, n);
        }

        ComplexNumber *rowtrans = transform(row, width);

        for (int j = 0; j < width; j++)
        {
            ndx(step1, j, i, n) = rowtrans[j];
        }

        delete[] rowtrans;
    }

    delete[] row;

    ComplexNumber *step2 = new ComplexNumber[height*width];
    ComplexNumber *column = new ComplexNumber[height];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            column[j] = ndx(step1, i, j, n);
        }

        ComplexNumber *coltrans = transform(column, height);

        for (int j = 0; j < height; j++)
        {
            ndx(step2, i, j, n) = coltrans[j];
        }

        delete[] coltrans;
    }

    delete[] column;
    delete[] step1;
    return step2;
}


/**
 * @brief Performs a two-dimensional (forward) Fourier transform on
 * real data.
 *
 * @param input A rectangular array of complex numbers to tranform, of
 * size n*m.
 *
 * @param n The width of the input array.
 *
 * @param m The height of the input array.
 *
 * @return The Fourier transform of the input.
 */
ComplexNumber *FourierTransform::transform(double *input, int n, int m)
{
    ComplexNumber *complex = new ComplexNumber[n*m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ndx(complex, j, i, n) = ComplexNumber::fromReal(ndx(input, j, i, n));

    return transform(complex, n, m);
}


/**
 * @brief Computes the inverse discrete Fourier transform of the input
 * data.
 *
 * @param input The complex numbers to be transformed.
 *
 * @param n The length of the input array.
 *
 * @return An array of complex numbers containing the inverse discrete
 * Fourier transform of the input data.
 */
ComplexNumber *FourierTransform::inverseTransform(ComplexNumber *input, int n)
{
    ComplexNumber *output = new ComplexNumber[n];

    for (int i = 0; i < n; i++)
        output[i] = input[i].conj();

    ComplexNumber *trans = transform(output, n);

    for (int i = 0; i < n; i++)
        output[i] = trans[i].conj() * (1. / n);

    delete[] trans;
    return output;
}


/**
 * @brief Performs a two-dimensional inverse Fourier transform on
 * complex data.
 *
 * @param input A rectangular array of complex numbers to tranform, of
 * size n*m.
 *
 * @param n The width of the input array.
 *
 * @param m The height of the input array.
 *
 * @return The inverse Fourier transform of the input.
 */
ComplexNumber *FourierTransform::inverseTransform(ComplexNumber *input,
    int n, int m)
{
    int height = m;
    int width = n;

    ComplexNumber *output = new ComplexNumber[width*height];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            ndx(output, j, i, n) = ndx(input, j, i, n).conj();
        }
    }

    ComplexNumber *trans = transform(output, n, m);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            ndx(output, j, i, n) = ndx(trans, j, i, n).conj() * (1. / (height * width));
        }
    }

    delete[] trans;
    return output;
}
