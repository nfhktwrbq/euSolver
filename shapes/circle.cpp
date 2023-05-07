// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#include <format>
#include <math.h>

#include "dot.h"
#include "line.h"
#include "circle.h"
#include "intersection.h"

Circle::Circle(void)
{

}

Circle::Circle(real_t xc, real_t yc, real_t r)
{
    this->xc_ = xc;
    this->yc_ = yc;
    this->r_ = r;
}

Circle::Circle(Point point_0, Point point_1)
{
    this->define_with_points(point_0, point_1);
}

Circle::~Circle()
{

}

real_t Circle::get_xc() const
{
    return this->xc_;
}

real_t Circle::get_yc() const
{
    return this->yc_;
}

real_t Circle::get_r() const
{
    return this->r_;
}

void Circle::define_with_points(Point & point_0, Point & point_1)
{
    DebugOutput() << std::format("Circle defined: x_0 {:.2f}, y_0: {:.2f}; x_1: {:.2f}, y_1: {:.2f}\n",
                                 point_0.x, point_0.y, point_1.x, point_1.y);
    this->xc_ = point_0.x;
    this->yc_ = point_0.y;
    this->r_ = sqrt((point_0.x - point_1.x) * (point_0.x - point_1.x) + (point_0.y - point_1.y) * (point_0.y - point_1.y));
}

void Circle::get_intersections(Shape * shape, vector<Point>& intersections) const
{

    if (Dot * dot = dynamic_cast<Dot*>(shape); dot != nullptr)
    {
        auto dot_pair = dot->get_dot();
        Intersection::dot_circle_intersection(dot_pair.first, dot_pair.second, this->xc_, this->yc_, this->r_, intersections);
    }
    else if (Line * line = dynamic_cast<Line*>(shape); line != nullptr)
    {
        Intersection::line_circle_intersection(line->get_k(), line->get_b(), this->xc_, this->yc_, this->r_, intersections);
    }
    else if (Circle * circle = dynamic_cast<Circle*>(shape); circle != nullptr)
    {
        Intersection::circle_circle_intersection(this->xc_, this->yc_, this->r_, circle->get_xc(), circle->get_yc(), circle->get_r(), intersections);
    }
}


