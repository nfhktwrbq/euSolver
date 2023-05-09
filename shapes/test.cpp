#include "test.h"

#include <vector>
#include <iostream>

#include "global_defs.h"
#include "shape.h"
#include "line.h"

using namespace std;

void test_intersection(void)
{
    Line line0(Point(2,3), Point(20,30));
    Line line1(Point(2,3), Point(20,30));
    Line line2(Point(2,3), Point(20,30));

    vector<Point> intersections;

    line0.get_intersections(&line1, intersections);

    cout << intersections.size() << endl;

    line0.get_intersections(&line2, intersections);

    cout << intersections.size() << endl;

    for (Point p : intersections)
    {
        cout << p.x << " " << p.y << std::endl;
    }
}
