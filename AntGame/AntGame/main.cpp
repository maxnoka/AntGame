#include <stdio.h>
#include <iostream>
#include "foo.h"
#include "bar.h"
#include "Fauna.h"

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
using namespace boost::geometry;


int main(int argc, char **argv)
{
	printf("hello world\n");
    foo();
	
	Bar b;
	b.DoStuff();
	

    
    model::d2::point_xy<int> p1(1, 1), p2(2, 2);
	
	Ant a("Steve", p1);
	a.PrintName();
    std::cout << "Distance p1-p2 is: " << distance(p1, p2) << std::endl;
 
	return 0;
}
