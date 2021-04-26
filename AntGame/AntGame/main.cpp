#include "Fauna.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <stdio.h>
#include <iostream>

int main(int argc, char **argv)
{
    // Testing that boost works
    boost::geometry::model::d2::point_xy<int> p1(1, 1), p2(2, 2);
    std::cout << "Distance p1-p2 is: " << boost::geometry::distance(p1, p2) << std::endl;
	
	Ant a("Steve", p1);
	a.PrintName();
 
	return 0;
}
