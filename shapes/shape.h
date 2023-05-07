// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "global_defs.h"

using namespace std;

/**
 * @todo write docs
 */
class Shape
{
public:
    virtual void define_with_points(Point & point_0, Point & point_1) = 0;
    virtual void get_intersections(Shape * shape, vector<Point>& intersections) const = 0 ;
};

#endif // SHAPE_H