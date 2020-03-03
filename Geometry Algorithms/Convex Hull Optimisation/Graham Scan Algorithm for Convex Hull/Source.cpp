# include <iostream>
# include <stdio.h>
# include <algorithm>
# include <stack>
using namespace std;

struct Point
{
	int x, y;

	// Comparing Y cooridnates first and then X coordinates;
	bool operator<(const Point& b)const
	{
		if (y != b.y)
			return y < b.y;
	
		return x < b.x;
	}
};
// Point having the least y coordinate, used for sorting other points
// according to polar angle about this point
Point pivot;



// Returns -1 if a->b->c-> form a counter clockwise turn,
// +1 for a clockwise turn, 0 if the points are colinear.
int direction(Point a, Point b, Point c)
{
	int area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	if (area > 0)
		return -1;
	if (area < 0)
		return 1;
	return 0;
}


//Returns square of Euclidean distance between 2 points.
int sqrDist(Point a, Point b)
{
	int dx = (a.x - b.x);
	int dy = (a.y - b.y);
	return (dx * dx) + (dy * dy);
}



