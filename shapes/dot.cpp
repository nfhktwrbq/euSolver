// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#include <math.h>
#include <format>
#include "dot.h"
#include "line.h"
#include "circle.h"
#include "intersection.h"

using namespace std;

Dot::Dot(void)
{

}

Dot::Dot(real_t x, real_t y)
{
    this->x_ = x;
    this->y_ = y;
}

Dot::~Dot()
{

}

Point Dot::get_point(void) const
{
    return Point(this->x_, this->y_);
}

void Dot::define_with_points(const Point & point_0, const Point & point_1)
{
    (void) point_1;
    this->x_ = point_0.x;
    this->y_ = point_0.y;
}

void Dot::get_intersections(Shape * shape, vector<Point>& intersections) const
{
    vector<pair<real_t, real_t>> * result = nullptr;

    if (Dot * dot = dynamic_cast<Dot*>(shape); dot != nullptr)
    {
        auto dot_pair = dot->get_point();
        Intersection::dot_dot_intersection(this->x_, this->y_, dot_pair.x, dot_pair.y, intersections);
    }
    else if (Line * line = dynamic_cast<Line*>(shape); line != nullptr)
    {
        Intersection::dot_line_intersection(*this, *line, intersections);
    }
    else if (Circle * circle = dynamic_cast<Circle*>(shape); circle != nullptr)
    {
        Intersection::dot_circle_intersection(*this, *circle, intersections);
    }
}

void Dot::print(void) const
{
    cout << std::format("Dot: x {:.2f}, y: {:.2f}\n", this->x_, this->y_);
}

bool Dot::equals(Shape * shape) const
{
    bool result = false;

    if (Dot * dot = dynamic_cast<Dot*>(shape); dot != nullptr)
    {
        auto dot_pair = dot->get_point();
        if (fabs(dot_pair.x - this->x_) < GD_EPSILON && fabs(dot_pair.y - this->y_) < GD_EPSILON)
        {
            result = true;
        }
    }

    return result;
}