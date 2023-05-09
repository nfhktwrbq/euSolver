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
    Line(Point point_0, Point point_1);

    /**
     * Destructor
     */
    ~Line();

    virtual void get_points(Point & point_0, Point & point_1) const;

    virtual void define_with_points(const Point & point_0, const Point & point_1);
    virtual void get_intersections(Shape * shape, vector<Point>& intersections) const;
    virtual void print(void) const;
    virtual bool equals(Shape * shape) const;

    real_t a;
    real_t b;
    real_t c;
private:

    Point p0_;
    Point p1_;

};

#endif // LINE_H
