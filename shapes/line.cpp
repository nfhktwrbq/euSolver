// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#include <math.h>
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

Line::Line(Point point_0, Point point_1)
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

real_t Line::get_x(void) const
{
    return this->x0_;
}

real_t Line::get_y(void) const
{
    return this->y0_;
}

void Line::define_with_points(Point & point_0, Point & point_1)
{
    if (!this->is_anchored_)
    {
        DebugOutput() << std::format("Line defined: x_0 {:.2f}, y_0: {:.2f}; x_1: {:.2f}, y_1: {:.2f}\n",
                                     point_0.x, point_0.y, point_1.x, point_1.y);
        this->k_ = (point_1.y - point_0.y) / (point_1.x - point_0.x);
        this->b_ = point_1.y - this->k_ * point_1.x;
        this->x0_ = point_0.x;
        this->y0_ = point_0.y;
        this->x1_ = point_1.x;
        this->y1_ = point_1.y;
    }
}

void Line::get_intersections(Shape * shape, vector<Point>& intersections) const
{
    vector<pair<real_t, real_t>> * result = nullptr;

    if (Dot * dot = dynamic_cast<Dot*>(shape); dot != nullptr)
    {
        Intersection::dot_line_intersection(*dot, *this, intersections);
    }
    else if (Line * line = dynamic_cast<Line*>(shape); line != nullptr)
    {
        Intersection::line_line_intersection(*this, *line, intersections);
    }
    else if (Circle * circle = dynamic_cast<Circle*>(shape); circle != nullptr)
    {
        Intersection::line_circle_intersection(*this, *circle, intersections);
    }
}

void Line::print(void) const
{
    cout << std::format("Line: x0 {:.6f}, y0: {:.6f}, x1 {:.6f}, y1: {:.6f}, k {:.2f}, b: {:.2f}\n", this->x0_, this->y0_, this->x1_, this->y1_, this->k_, this->b_);

}

bool Line::equals(Shape * shape) const
{
    bool result = false;

    if (Line * line = dynamic_cast<Line*>(shape); line != nullptr)
    {
        if (isinf(line->get_k()) && isinf(this->k_))
        {
            if (fabs(line->get_x() - this->get_x()) < GD_EPSILON)
            {
                result = true;
            }
        }
        if (!isinf(line->get_k()) && !isinf(this->k_))
        {
            if (fabs(line->get_k() - this->k_) < GD_EPSILON && fabs(line->get_b() - this->b_) < GD_EPSILON)
            {
                result = true;
            }
        }
    }

    return result;
}
