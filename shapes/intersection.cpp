// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#include "intersection.h"
#include "line.h"
#include <math.h>
#include <format>

void Intersection::add_point_(vector<Point>& intersections, const Point& p)
{
    for (const auto& i : intersections)
    {
        if (fabs(i.x - p.x) < GD_EPSILON && fabs(i.y - p.y) < GD_EPSILON)
        {
            // Точка уже есть в векторе, не добавляем ее
            return;
        }
    }
    // Точки нет в векторе, добавляем ее
    DebugOutput() << std::format("    x {:.2f}, y: {:.2f}\n", p.x, p.y);
    intersections.push_back(p);
}

void Intersection::dot_dot_intersection(real_t x0, real_t y0, real_t x1, real_t y1, vector<Point>& intersections)
{
    if (abs(x0 - x1) < GD_EPSILON && fabs(y0 - y1) < GD_EPSILON)
    {
        DebugOutput() << std::format("Dot dot intersection:\n");
        add_point_(intersections, Point(x0, y0));
    }
}

void Intersection::dot_line_intersection(const Dot & dot, const Line & line, vector<Point>& intersections)
{
    Point p = dot.get_point();

    if (fabs(line.a*p.x + line.b*p.y + line.c) < GD_EPSILON)
    {
        DebugOutput() << std::format("Dot line intersection:\n");
        add_point_(intersections, p);
    }
}

void Intersection::line_line_intersection(const Line& line0, const Line& line1, vector<Point>& intersections)
{
    real_t determinant = line0.a * line1.b - line1.a * line0.b;

    if (determinant > GD_EPSILON)
    {
        real_t x = (line1.b*line0.c - line0.b*line1.c)/determinant;
        real_t y = (line0.a*line1.c - line1.a*line0.c)/determinant;
        DebugOutput() << std::format("Line line intersection:\n");
        add_point_(intersections, Point(x, y));
    }
}

void Intersection::line_circle_intersection(const Line& line, const Circle& circle, vector<Point>& intersections)
{
    Point p1, p2;
    const real_t r = circle.get_r();
    const Point c(circle.get_xc(), circle.get_yc());

    line.get_points(p1, p2);
    real_t dx = p2.x - p1.x;
    real_t dy = p2.y - p1.y;
    real_t a = dx*dx + dy*dy;
    real_t b = 2*(dx*(p1.x-c.x) + dy*(p1.y-c.y));
    real_t c1 = c.x*c.x + c.y*c.y + p1.x*p1.x + p1.y*p1.y - 2*(c.x*p1.x + c.y*p1.y) - r*r;
    real_t discriminant = b*b - 4*a*c1;

    if (discriminant < -GD_EPSILON)
    {
    } else if (discriminant < GD_EPSILON)
    {
        real_t t = -b / (2*a);
        real_t x = p1.x + t*dx;
        real_t y = p1.y + t*dy;
        add_point_(intersections, Point(x, y));
    } else
    {
        real_t t1 = (-b + std::sqrt(discriminant)) / (2*a);
        real_t x1 = p1.x + t1*dx;
        real_t y1 = p1.y + t1*dy;
        real_t t2 = (-b - std::sqrt(discriminant)) / (2*a);
        real_t x2 = p1.x + t2*dx;
        real_t y2 = p1.y + t2*dy;
        add_point_(intersections, Point(x1, y1));
        add_point_(intersections, Point(x2, y2));
    }
}

void Intersection::dot_circle_intersection(const Dot & dot, const Circle & circle, vector<Point>& intersections)
{
    Point p = dot.get_point();
    real_t xc = circle.get_xc();
    real_t yc = circle.get_yc();
    real_t r = circle.get_r();
    if (sqrt((p.x - xc) * (p.x - xc) + (p.y - yc) * (p.y - yc) - r * r) < GD_EPSILON)
    {
        DebugOutput() << std::format("Dot circle intersection:\n");
        add_point_(intersections, p);
    }
}

void Intersection::circle_circle_intersection(const Circle & circle0, const Circle & circle1, vector<Point>&  intersections)
{
    real_t xc0 = circle0.get_xc();
    real_t yc0 = circle0.get_yc();
    real_t r0 = circle0.get_r();

    real_t xc1 = circle1.get_xc();
    real_t yc1 = circle1.get_yc();
    real_t r1 = circle1.get_r();

    // Находим расстояние между центрами окружностей
    real_t d = sqrt((xc1 - xc0) * (xc1 - xc0) + (yc1 - yc0) * (yc1 - yc0));

    // Проверяем, пересекаются ли окружности
    if (d > r0 + r1) {
        return; // Окружности не пересекаются
    }

    if (d < GD_EPSILON)
    {
        return;
    }

    // Находим координаты точек пересечения
    real_t a = (r0 * r0 - r1 * r1 + d * d) / (2.0 * d);
    real_t h = std::sqrt(r0 * r0 - a * a);

    if (h != h)
    {
        return;
    }

    real_t x2 = xc0 + a * (xc1 - xc0) / d;
    real_t y2 = yc0 + a * (yc1 - yc0) / d;

    real_t x3 = x2 + h * (yc1 - yc0) / d;
    real_t y3 = y2 - h * (xc1 - xc0) / d;

    real_t x4 = x2 - h * (yc1 - yc0) / d;
    real_t y4 = y2 + h * (xc1 - xc0) / d;

    // Добавляем точки пересечения в вектор
    if (fabs(x3 -x4) < GD_EPSILON && fabs(y3 - y4) < GD_EPSILON)
    {
        DebugOutput() << std::format("Circle circle touch:\n");
        add_point_(intersections, Point(x3, y3));
    }
    else
    {
        DebugOutput() << std::format("Circle circle intersection:\n");
        add_point_(intersections, Point(x3, y3));
        add_point_(intersections, Point(x4, y4));
    }
}
