// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#include <math.h>
#include <format>
#include "dot.h"
#include "line.h"
#include "circle.h"
#include "intersection.h"

Line::Line(void)
{

}

Line::Line(Point point_0, Point point_1)
{
    this->define_with_points(point_0, point_1);
}

Line::~Line()
{

}

void Line::get_points(Point & point_0, Point & point_1) const
{
    point_0 = this->p0_;
    point_1 = this->p1_;
}

void Line::define_with_points(const Point & point_0, const Point & point_1)
{
    if (!this->is_anchored_)
    {
        DebugOutput() << std::format("Line defined: x_0 {:.2f}, y_0: {:.2f}; x_1: {:.2f}, y_1: {:.2f}\n",
                                     point_0.x, point_0.y, point_1.x, point_1.y);
        this->p0_ = point_0;
        this->p1_ = point_1;
        this->a = point_0.y - point_1.y;
        this->b = point_1.x - point_0.x;
        this->c = point_0.x*point_1.y - point_1.x*point_0.y;
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
    cout << std::format("Line: x0 {:.6f}, y0: {:.6f}, x1 {:.6f}, y1: {:.6f}\n", this->p0_.x, this->p0_.y, this->p1_.x, this->p1_.y);

}

bool Line::equals(Shape * shape) const
{
    bool result = false;

    if (Line * line = dynamic_cast<Line*>(shape); line != nullptr)
    {
        if (fabs(line->a * this->b - this->a * line->b) < GD_EPSILON)
        {
            if (fabs(line->a * this->c - this->a * line->c) < GD_EPSILON &&
            fabs(line->b * this->c - this->b * line->c) < GD_EPSILON)
            {
                result = true;
            }
        }
    }

    return result;
}
