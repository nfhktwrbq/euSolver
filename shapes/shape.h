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
    virtual void define_with_points(const Point & point_0, const Point & point_1) = 0;
    virtual void get_intersections(Shape * shape, vector<Point>& intersections) const = 0;
    virtual bool equals(Shape * shape) const = 0;
    virtual void print(void) const = 0;
    virtual void drop_anchor(void);
    virtual bool is_anchored(void);

protected:
    bool is_anchored_ = false;
};

std::ostream& operator<<(std::ostream& os, const Shape& shape);

#endif // SHAPE_H
