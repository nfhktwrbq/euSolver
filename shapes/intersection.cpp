// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#include "intersection.h"
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

void Intersection::dot_line_intersection(real_t x, real_t y, real_t k, real_t b, vector<Point>& intersections)
{
    vector<pair<real_t, real_t>> * result = nullptr;

    if (fabs(k * x + b - y) < GD_EPSILON)
    {
        DebugOutput() << std::format("Dot line intersection:\n");
        add_point_(intersections, Point(x, y));
    }
}

void Intersection::line_line_intersection(real_t a0, real_t b0, real_t c0, real_t a1, real_t b1, real_t c1, vector<Point>& intersections)
{
    double determinant = a0*b1 - a1*b0;

    vector<pair<real_t, real_t>> * result = nullptr;

    if (determinant != 0)
    {
        double x = (b1*c0 - b0*c1)/determinant;
        double y = (a0*c1 - a1*c0)/determinant;
        DebugOutput() << std::format("Line line intersection:\n");
        add_point_(intersections, Point(x, y));
    }
}

void Intersection::line_line_intersection(real_t k0, real_t b0, real_t k1, real_t b1, vector<Point>& intersections)
{
    vector<pair<real_t, real_t>> * result = nullptr;

    if (fabs(k0 - k1) > GD_EPSILON)
    {
        real_t x = (b1 - b0) / (k0 - k1);
        real_t y = k0 * x + b0;
        DebugOutput() << std::format("Line line intersection:\n");
        add_point_(intersections, Point(x, y));
    }
}

void Intersection::dot_circle_intersection(real_t x, real_t y, real_t xc, real_t yc, real_t r, vector<Point>& intersections)
{
    vector<pair<real_t, real_t>> * result = nullptr;
    if (abs((x - xc) * (x - xc) + (y - yc) * (y - yc) - r) < GD_EPSILON)
    {
        DebugOutput() << std::format("Dot circle intersection:\n");
        add_point_(intersections, Point(x, y));
    }
}

void Intersection::line_circle_intersection(real_t k, real_t b, real_t xc, real_t yc, real_t r, vector<Point>& intersections)
{
    // Решаем квадратное уравнение для нахождения точек пересечения
    real_t A = 1.0 + k * k;
    real_t B = -2.0 * xc + 2.0 * k * (b - yc);
    real_t C = xc * xc + (b - yc) * (b - yc) - r * r;

    real_t D = B * B - 4.0 * A * C;

    vector<pair<real_t, real_t>> * result = nullptr;

    if (D < 0.0)
    {

    }
    else if (D == 0.0)
    {
        // Одна точка пересечения
        real_t x = -B / (2.0 * A);
        real_t y = k * x + b;
        DebugOutput() << std::format("Line circle touch:\n");
        add_point_(intersections, Point(x, y));
    } else
    {
        // Две точки пересечения
        real_t x0 = (-B + sqrt(D)) / (2.0 * A);
        real_t y0 = k * x0 + b;

        real_t x1 = (-B - sqrt(D)) / (2.0 * A);
        real_t y1 = k * x1 + b;

        DebugOutput() << std::format("Line circle intersection:\n");
        add_point_(intersections, Point(x0, y0));
        add_point_(intersections, Point(x1, y1));
    }
}

void Intersection::circle_circle_intersection(real_t xc0, real_t yc0, real_t r0, real_t xc1, real_t yc1, real_t r1, vector<Point>&  intersections)
{
    // Находим расстояние между центрами окружностей
    real_t d = sqrt((xc1 - xc0) * (xc1 - xc0) + (yc1 - yc0) * (yc1 - yc0));

    // Проверяем, пересекаются ли окружности
    if (d > r0 + r1) {
        return; // Окружности не пересекаются
    }

    if (d == 0)
    {
        return;
    }

    // Находим координаты точек пересечения
    real_t a = (r0 * r0 - r1 * r1 + d * d) / (2.0 * d);
    real_t h = std::sqrt(r0 * r0 - a * a);
    real_t x2 = xc0 + a * (xc1 - xc0) / d;
    real_t y2 = yc0 + a * (yc1 - yc0) / d;

    real_t x3 = x2 + h * (yc1 - yc0) / d;
    real_t y3 = y2 - h * (xc1 - xc0) / d;

    real_t x4 = x2 - h * (yc1 - yc0) / d;
    real_t y4 = y2 + h * (xc1 - xc0) / d;

    // Добавляем точки пересечения в вектор
    if (fabs(x3 -x4) + fabs(y3 - y4) < GD_EPSILON)
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
