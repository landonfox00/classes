
#ifndef OCCUPANCY_MAP_H
#define OCCUPANCY_MAP_H

#include <vector>
#include <utility>

#include "graph.h"

template < class T >
class OccupancyMap : public Graph< std::pair< T, T >, double, double >
{
public:
	OccupancyMap( std::vector< std::vector< bool > > occupied, int x_dim, int y_dim );

	bool Add( int x, int y );

	void Scan( int x, int y, int degree, int magnitude );
	void ScanNode( int x, int y );

	void Output( std::string filename );

	bool IsInMap( int x, int y );

	int get_x_dim();
	int get_y_dim();

private:
	const std::vector< std::vector< bool > > occupied_;
	int x_dim_, y_dim_;
};

#include "occupancy_map.cc"

#endif
