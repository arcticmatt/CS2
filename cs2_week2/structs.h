#ifndef __STRUCTS_H__
#define __STRUCTS_H__
#include <cmath>
#include <cstdio>

struct Tuple
{
    int x;
    int y;

    Tuple(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void printTuple()
    {
        printf("(%d, %d)\n", x, y);
    }
    /**
     * angle_wrt_x_axis
     * @return (double) angle that this point makes with respect to positive x
     * axis.
     */
    double angle_wrt_x_axis()
    {
        return atan2((double) this->y, (double) this->x);
    }

    /**
     * angle_wrt_pt: Computes the angle that the line joining this point to the
     *                 passed point makes with respect to the horizontal line
     *                 going through the passed point.
     * 
     * @param  pt   Pointer to point through which we draw a horizontal line and
     *              compute angle relative to.
     * @return      Angle that the two points make relative to x axis defined by
     *              passed point.
     */
    double angle_wrt_pt(Tuple *pt)
    {
        double dy = (double) this->y - (double) pt->y;
        double dx = (double) this->x - (double) pt->x;
        return atan2(dy, dx);
    }
};

#endif
