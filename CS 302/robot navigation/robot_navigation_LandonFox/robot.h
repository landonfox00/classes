
#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include "occupancy_map.h"

#define DEGREE_INCR 15
#define MAGNITUDE 50

class Robot
{
public:
	Robot( std::vector< std::vector< bool > > occupied_map, int map_x_dim, int map_y_dim );

	bool Move( int x, int y, int orientation );

	void Scan();

	void DisplayMap( std::string filename );

private:
	OccupancyMap< int > map_;
	int x_, y_, orientation_;
};

#include "robot.cc"

#endif
