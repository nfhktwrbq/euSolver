// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#include <format>
#include "dot.h"
#include "line.h"
#include "circle.h"
#include "intersection.h"

Line::Line()
{

}

Line::Line(real_t k, real_t b)
{
    this->k_ = k;
    this->b_ = b;
}

Line::Line(Point & point_0, Point & point_1)
{
    this->define_with_points(point_0, point_1);
}

Line::~Line()
{

}

real_t Line::get_k(void) const
{
    return this->k_;
}

real_t Line::get_b(void) const
{
    return this->b_;
}

void Line::define_with_points(Point & point_0, Point & point_1)
{
    DebugOutput() << std::format("Line defined: x_0 {:.2f}, y_0: {:.2f}; x_1: {:.2f}, y_1: {:.2f}\n",
                                 point_0.x, point_0.y, point_1.x, point_1.y);
    this->k_ = (point_1.y - point_0.y) / (point_1.x - point_0.x);
    this->b_ = point_1.y - this->k_ * point_1.x;
}

void Line::get_intersections(Shape * shape, vector<Point>& intersections) const
{
    vector<pair<real_t, real_t>> * result = nullptr;

    if (Dot * dot = dynamic_cast<Dot*>(shape); dot != nullptr)
    {
        auto dot_pair = dot->get_dot();
        Intersection::dot_line_intersection(dot_pair.first, dot_pair.second, this->k_, this->b_, intersections);
    }
    else if (Line * line = dynamic_cast<Line*>(shape); line != nullptr)
    {
        Intersection::line_line_intersection(this->k_, this->b_, line->get_k(), line->get_b(), intersections);
    }
    else if (Circle * circle = dynamic_cast<Circle*>(shape); circle != nullptr)
    {
        Intersection::line_circle_intersection(this->k_, this->b_, circle->get_xc(), circle->get_yc(), circle->get_r(), intersections);
    }
}

