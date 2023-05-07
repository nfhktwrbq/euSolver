// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

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

pair<real_t, real_t> Dot::get_dot(void) const
{
    return make_pair(this->x_, this->y_);
}

void Dot::define_with_points(Point & point_0, Point & point_1)
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
        auto dot_pair = dot->get_dot();
        Intersection::dot_dot_intersection(this->x_, this->y_, dot_pair.first, dot_pair.second, intersections);
    }
    else if (Line * line = dynamic_cast<Line*>(shape); line != nullptr)
    {
        Intersection::dot_line_intersection(this->x_, this->y_, line->get_k(), line->get_b(), intersections);
    }
    else if (Circle * circle = dynamic_cast<Circle*>(shape); circle != nullptr)
    {
        Intersection::dot_circle_intersection(this->x_, this->y_, circle->get_xc(), circle->get_yc(), circle->get_r(), intersections);
    }
}

