
#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <utility>

#include "graph_node.h"
#include "graph.h"

template < class Data >
class Polygon : public Graph< std::pair< int, int >, Data, int >
{
public:
	Polygon();
	Polygon( std::vector< std::pair< int, int > > coords );
	virtual ~Polygon();

	std::vector< std::pair< int, int > > get_coords();
	std::pair< int, int > get_left_coord( std::pair< int, int > coord );
	std::pair< int, int > get_right_coord( std::pair< int, int > coord );

	bool IsCoordConcave( std::pair< int, int > coord );
	static bool IsConcave( std::pair< int, int > left, std::pair< int, int > coord, std::pair< int, int > right );

	bool Add( std::pair< int, int > start, std::pair< int, int > end );

private:
	std::vector< std::pair< int, int > > coords_;
};

#include "polygon.cc"

#endif
