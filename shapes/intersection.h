// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <utility>
#include <vector>
#include "global_defs.h"

using namespace std;


/**
 * @todo write docs
 */
class Intersection
{
    public:
        static void dot_dot_intersection(real_t x0, real_t  y0, real_t x1, real_t y1, vector<Point>& intersections);
        static void line_line_intersection(real_t a0, real_t b0, real_t c0, real_t a1, real_t b1, real_t c1, vector<Point>& intersections);
        static void line_line_intersection(real_t k0, real_t b0, real_t k1, real_t b1, vector<Point>& intersections);
        static void dot_line_intersection(real_t x, real_t y, real_t k, real_t b, vector<Point>& intersections);
        static void dot_circle_intersection(real_t x, real_t y, real_t xc, real_t yc, real_t r, vector<Point>& intersections);
        static void line_circle_intersection(real_t k, real_t b, real_t xc, real_t yc, real_t r, vector<Point>& intersections);
        static void circle_circle_intersection(real_t xc0, real_t yc0, real_t r0, real_t xc1, real_t yc1, real_t r1, vector<Point>& intersections);

    private:
        static void add_point_(vector<Point>& intersections, const Point& p);
};

#endif // INTERSECTION_H