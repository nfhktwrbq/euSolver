// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#ifndef LINE_H
#define LINE_H

using namespace std;

#include <vector>
#include <utility>
#include "shape.h"
#include "global_defs.h"

/**
 * @todo write docs
 */
class Line : public Shape
{
public:
    /**
     * Default constructor
     */
    Line(void);
    Line(real_t k, real_t b);
    Line(Point & point_0, Point & point_1);

    /**
     * Destructor
     */
    ~Line();

    real_t get_k(void) const;
    real_t get_b(void) const;

    virtual void define_with_points(Point & point_0, Point & point_1);
    virtual void get_intersections(Shape * shape, vector<Point>& intersections) const;

private:

    real_t k_;
    real_t b_;
};

#endif // LINE_H
