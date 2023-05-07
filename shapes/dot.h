// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#ifndef DOT_H
#define DOT_H

#include <utility>
#include "global_defs.h"
#include "shape.h"

using namespace std;
/**
 * @todo write docs
 */
class Dot: public Shape
{
public:
    /**
     * Default constructor
     */
    Dot();
    Dot(real_t x, real_t y);

    /**
     * Destructor
     */
    ~Dot();

    pair<real_t, real_t> get_dot(void) const;
    virtual void define_with_points(Point & point_0, Point & point_1);
    virtual void get_intersections(Shape * shape, vector<Point>& intersections) const;
    virtual void print(void) const;
    virtual bool equals(Shape * shape) const;

private:
     real_t y_;
     real_t x_;
};

#endif // DOT_H
