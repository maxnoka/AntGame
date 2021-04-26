#ifndef FAUNA_H
#define FAUNA_H

#include <string>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>


using Position = boost::geometry::model::d2::point_xy<int>;

class Ant
{
public:
	Ant(std::string Name, Position spawnPoint); //birth of ant
	
	
	//member variable
	std::string m_name;
	int m_age;
	Position m_position;
	
	
	void PrintName();
};


#endif // FAUNA_H
