// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#ifndef CIRCLE_H
#define CIRCLE_H

using namespace std;

#include <vector>
#include <utility>
#include "shape.h"
#include "global_defs.h"

/**
 * @todo write docs
 */
class Circle : public Shape
{
public:

    Circle(void);
    Circle(real_t xc, real_t yc, real_t r);
    Circle(Point point_0, Point point_1);
    ~Circle();

    real_t get_xc() const;
    real_t get_yc() const;
    real_t get_r() const;

    virtual void define_with_points(Point & point_0, Point & point_1);
    virtual void get_intersections(Shape * shape, vector<Point>& intersections) const;

private:
    real_t r_;
    real_t yc_;
    real_t xc_;
};

#endif // CIRCLE_H
