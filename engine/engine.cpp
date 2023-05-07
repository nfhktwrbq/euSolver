// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <math.h>
#include <format>
#include "engine.h"
#include "global_defs.h"

Engine::Engine(vector<Shape*> * shapes, vector<Point> * start_points, vector<Point> * finding_points)
{
    this->shapes_ = shapes;
    this->finding_points_ = finding_points;
    this->start_points_ = start_points;
    this->is_solved_ = false;

    this->points_to_find_ =  *finding_points;
}

bool Engine::chekc_intersections(vector<Point> & candidates)
{
    for (Point candidate_point : candidates)
    {

        this->points_to_find_.erase(remove_if(this->points_to_find_.begin(), this->points_to_find_.end(),
                            [candidate_point](Point point)
                            {
                                return fabs(point.x - candidate_point.x) + fabs(point.y - candidate_point.y) < GD_EPSILON;
                            }),
        this->points_to_find_.end());
    }
    if (this->points_to_find_.size() == 0)
    {
        this->is_solved_ = true;
    }
    return this->is_solved_;
}

void Engine::permutate_points(vector<Point> & points, vector<pair<Point, Point>> & permutated_points)
{
    for (auto it_0 = points.begin(); it_0 != points.end(); ++it_0)
    {
        int index_0 = std::distance(points.begin(), it_0);
        for (auto it_1 = points.begin(); it_1 != points.end(); ++it_1)
        {
            int index_1 = std::distance(points.begin(), it_1);
            if (index_1 == index_0)
            {
                continue;
            }
            permutated_points.push_back({*it_0, *it_1});
        }
    }
}

bool Engine::solve(vector<Point> * intersections, vector<Shape*>::iterator shape_it)
{
    vector<pair<Point, Point>> permutated_points;

    vector<Point> current_intersections = *intersections;
    this->permutate_points(current_intersections, permutated_points);
    auto cur_shape = shape_it;

    for (pair<Point, Point> point_pair : permutated_points)
    {
        DebugOutput() << std::format("Cur point pair x_0: {:.2f}, y_0: {:.2f}; x_1: {:.2f}, y_1: {:.2f}\n",
                                     point_pair.first.x, point_pair.first.y, point_pair.second.x, point_pair.second.y);
        (*cur_shape)->define_with_points(point_pair.first, point_pair.second);

        while (shape_it != this->shapes_->begin())
        {
            shape_it--;
            (*cur_shape)->get_intersections(*shape_it, current_intersections);
        }
        shape_it = cur_shape;

        if (this->chekc_intersections(current_intersections))
        {
            break;
        }

        if (*cur_shape != this->shapes_->back())
        {
            cur_shape++;
            this->solve(&current_intersections, cur_shape);
        }
    }

    return this->is_solved_;
}

