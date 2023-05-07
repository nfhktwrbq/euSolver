// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include "shape.h"

using namespace std;

/**
 * @todo write docs
 */
class Engine
{
public:
    Engine(vector<Shape*> * shapes, vector<Point> * start_points, vector<Point> * finding_points);

    bool solve(vector<Point> * intersections, vector<Shape*>::iterator shape_it);
private:
    vector<Shape*> * shapes_;
    vector<Point> * finding_points_;
    vector<Point> * start_points_;
    vector<Point> points_to_find_;
    bool is_solved_;

    bool chekc_intersections(vector<Point> & candidates);
    void permutate_points(vector<Point> & points, vector<pair<Point, Point>> & permutated_points);
};

#endif // ENGINE_H
