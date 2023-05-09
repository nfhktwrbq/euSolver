// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <utility>
#include <vector>
#include "global_defs.h"
#include "line.h"
#include "dot.h"
#include "circle.h"

using namespace std;


/**
 * @todo write docs
 */
class Intersection
{
    public:
        static void dot_dot_intersection(real_t x0, real_t  y0, real_t x1, real_t y1, vector<Point>& intersections);
        static void dot_circle_intersection(const Dot & dot, const Circle & circle, vector<Point>& intersections);
        static void circle_circle_intersection(const Circle & circle0, const Circle & circle1, vector<Point>& intersections);
        static void line_line_intersection(const Line& line0, const Line& line1, vector<Point>& intersections);
        static void dot_line_intersection(const Dot& dot, const Line& line, vector<Point>& intersections);
        static void line_circle_intersection(const Line& line, const Circle& circle, vector<Point>& intersections);

    private:
        static void add_point_(vector<Point>& intersections, const Point& p);
};

#endif // INTERSECTION_H
