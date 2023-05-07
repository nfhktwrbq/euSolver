// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

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
    Shape * circle0 = new Circle();
    Shape * circle1 = new Circle();
    Shape * line0 = new Line();
    Shape * line1 = new Line();

    vector<Shape*> shapes_vector = {circle0, circle1, line0, line1};
    vector<Point> finding_points = {Point(1, 1)};
    vector<Point> start_points = {Point(0, 0), Point(2, 2)};

    Engine engine(&shapes_vector, &start_points, &finding_points);

    vector<Shape*>::iterator shape_it = shapes_vector.begin();

    return engine.solve(&start_points, shape_it);
}


