// SPDX-FileCopyrightText: 2023 <copyright holder> <email>
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <math.h>
#include <format>
#include "engine.h"
#include "global_defs.h"
#include "dot.h"

Engine::Engine(vector<Shape*> * shapes, vector<Point> * start_points, vector<Shape*> * finding_shapes)
{
    this->shapes_ = shapes;
    this->start_points_ = start_points;
    this->is_solved_ = false;
    this->shapes_to_find_ = finding_shapes;
}

bool Engine::chekc_intersections(vector<Point> & candidates, vector<Shape*>::iterator cur_shape_it)
{
    for (const auto& shape_to_find : *this->shapes_to_find_)
    {
        bool is_found = false;
        if (Dot * dot_to_find = dynamic_cast<Dot*>(shape_to_find); dot_to_find != nullptr)
        {
            for (const auto &candidate_point: candidates)
            {
                Dot candidate_dot = Dot(candidate_point.x, candidate_point.y);
                if (dot_to_find->equals(&candidate_dot))
                {
                    is_found = true;
                    break;
                }
            }
        }
        else
        {
            for (vector<Shape*>::iterator candidate_shape = this->shapes_->begin(); candidate_shape <= cur_shape_it; ++candidate_shape)
            {
                if (shape_to_find->equals(*candidate_shape))
                {
                    is_found = true;
                    break;
                }
            }
        }
        if (!is_found) {
            return false;
        }
    }

    for (const auto& p : candidates) {
        cout << std::format("x: {:.6f}, y: {:.6f}\n", p.x, p.y);
    }
    for (const auto& s : *this->shapes_) {
        cout << *s;
    }

    this->is_solved_ = true;
    return true;
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

bool Engine::is_already_exist(vector<Shape*>::iterator shape_it) const
{
    bool result = false;
    auto cur_shape = shape_it;

    while (shape_it != this->shapes_->begin())
    {
        shape_it--;
        if ((*cur_shape)->equals(*shape_it))
        {
            result = true;
            break;
        }
    }

    return result;
}

void Engine::concat_points(vector<Point> * old_intersections, vector<Point> * new_intersections) const
{
    vector<Point>  tmp_intersections;
    for (auto it_old = old_intersections->begin(); it_old != old_intersections->end(); ++it_old)
    {
        bool is_unique = true;
        for (auto it_new = new_intersections->begin(); it_new != new_intersections->end(); ++it_new)
        {
            if (std::abs(it_old->x - it_new->x) < GD_EPSILON && std::abs(it_old->y - it_new->y) < GD_EPSILON)
            {
                is_unique = false;
            }
        }
        if (is_unique)
        {
            tmp_intersections.push_back(*it_old);
        }
    }

    new_intersections->insert(new_intersections->end(), tmp_intersections.begin(), tmp_intersections.end() );
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

        if (this->is_already_exist(cur_shape))
        {
            continue;
        }

        vector<Point> new_intersections;
        while (shape_it != this->shapes_->begin())
        {
            shape_it--;
            (*cur_shape)->get_intersections(*shape_it, new_intersections);
        }
        shape_it = cur_shape;

//        new_intersections.insert( new_intersections.end(), current_intersections.begin(), current_intersections.end() );
        this->concat_points(&current_intersections, &new_intersections);

        if (*cur_shape != this->shapes_->back())
        {
            auto shape_for_solve = cur_shape + 1;
            if (this->solve(&new_intersections, shape_for_solve))
            {
                break;
            }
        }

        if (this->chekc_intersections(new_intersections, cur_shape))
        {
            break;
        }

        if ((*cur_shape)->is_anchored())
        {
            break;
        }
    }

    return this->is_solved_;
}

