// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#include <format>
#include <cstdint>
#include "engine.h"
#include "dot.h"
#include "line.h"
#include "circle.h"
#include "test_engine.h"

TestEngine::TestEngine()
{

}

TestEngine::~TestEngine()
{

}

bool TestEngine::run(void)
{
    bool result = false;
#if 0
    vector<Shape*> shapes_vector = {
            new Circle(),
            new Circle(),
            new Line(),
            new Line(),
    };
    Point p1(50, 50);
    Point p2(50, -50);
    vector<Shape*> finding_shapes = {new Line(p1, p2), new Line(1.792050808, 0),};
    vector<Point> start_points = {Point(0, 0), Point(100, 0)};
#endif

#if 1
    vector<Shape*> shapes_vector =
            {
                    new Circle(Point(-100, 0), Point(0, 0)),
                    new Circle(Point(-33, 74.23610981),  Point(0, 0)),
                    new Circle(Point(0, 0), Point(-110.219999998, 99.476387148)),
                    new Circle(Point(-0.000000005, 148.472219622), Point(0, 0)),
                    new Line(Point(-128.580713952, 74.236109807), Point(0, 0)),
                    new Line(),
                    new Line(),
    };

    shapes_vector[0]->drop_anchor();
    shapes_vector[1]->drop_anchor();
    shapes_vector[2]->drop_anchor();
    shapes_vector[3]->drop_anchor();
    shapes_vector[4]->drop_anchor();
//    shapes_vector[5]->drop_anchor();

    Point p1(-150, 50);
    Point p2(-150, -50);
    vector<Shape*> finding_shapes = {new Line(0.577350269, 0), new Line(-0.577350269, 0), new Line(p1, p2)};
//    vector<Shape*> finding_shapes = {new Line(-0.577350269, 0), new Line(0.577350269, 0)};
//    vector<Shape*> finding_shapes = {new Dot(-150, 86.60254038), new Dot(-150, -86.60254038)};
    vector<Point> start_points = {Point(0, 0)};
//    shapes_vector[0]->get_intersections(shapes_vector[1], start_points);
//    shapes_vector[0]->get_intersections(shapes_vector[2], start_points);
    shapes_vector[2]->get_intersections(shapes_vector[3], start_points);

    for (auto p: start_points)
    {
        cout << std::format("Intersect: x {:.9f}, y: {:.9f}\n", p.x, p.y);
    }
#endif

#if 0
    vector<Shape*> shapes_vector =
            {
                    new Circle(Point(0, 0), Point(100, 0)),
                    new Circle(Point(100, 0), Point(0, 0)),
                    new Circle(Point(50, 86.60254038), Point(50, -86.60254038)),
//                    new Circle(Point(50, -86.60254038), Point(0, 0)),
//                    new Circle(Point(145.742710, -57.735027), Point(50, 86.60254038)),
//                    new Circle(Point(200, 0), Point(-22.871356, -18.120678)),
//                    new Circle(Point(0, 100), Point(0, 0)),
                    new Circle(),
                    new Circle(),
                    new Circle(),
                    new Circle(),
            };


    vector<Shape*> finding_shapes = {new Dot(0, 100),new Dot(100, 100)};
    vector<Point> start_points = {Point(0, 0), Point(100, 0)};

    shapes_vector[0]->drop_anchor();
    shapes_vector[1]->drop_anchor();
    shapes_vector[2]->drop_anchor();
//    shapes_vector[3]->drop_anchor();
//    shapes_vector[4]->drop_anchor();
//    shapes_vector[5]->drop_anchor();
//    shapes_vector[6]->drop_anchor();
#endif

    Engine engine(&shapes_vector, &start_points, &finding_shapes);

    vector<Shape*>::iterator shape_it = shapes_vector.begin();

    if (engine.solve(&start_points, shape_it))
    {
        cout << "\nSolution:\n";
        for (const auto i : shapes_vector)
        {
            cout << (*i);
        }
        result = true;
    }
    return result;
}


