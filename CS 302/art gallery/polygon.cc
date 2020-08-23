
#include <vector>
#include <utility>
#include <iterator>
#include <algorithm>
#include <math.h>

#include "graph_node.h"
#include "graph.h"
#include "polygon.h"

template < class Data >
Polygon< Data >::Polygon()
	: Graph< std::pair< int, int >, Data, int >(), coords_() { }

template < class Data >
Polygon< Data >::Polygon( std::vector< std::pair< int, int > > coords )
	: Graph< std::pair< int, int >, Data, int >(), coords_()
{
	for ( int i = 0; i < coords.size() - 1; ++i )
		this->Add( coords[ i ], coords[ i + 1 ] );
}

template < class Data >
Polygon< Data >::~Polygon() { }

template < class Data >
std::vector< std::pair< int, int > > Polygon< Data >::get_coords()
{
	return this->coords_;
}

template < class Data >
std::pair< int, int > Polygon< Data >::get_left_coord( std::pair< int, int > coord )
{
	std::vector< std::pair< int, int > >::iterator begin = this->coords_.begin(), end = this->coords_.end();
	std::vector< std::pair< int, int > >::iterator it = std::find( begin, end, coord );
	if ( it == begin )
		return *end;
	return *( it - 1 );
}

template < class Data >
std::pair< int, int > Polygon< Data >::get_right_coord( std::pair< int, int > coord )
{
	std::vector< std::pair< int, int > >::iterator begin = this->coords_.begin(), end = this->coords_.end();
	std::vector< std::pair< int, int > >::iterator it = std::find( begin, end, coord );
	if ( it == end )
		return *begin;
	return *( it + 1 );
}

template < class Data >
bool Polygon< Data >::IsCoordConcave( std::pair< int, int > coord )
{
	std::pair< int, int > left = this->get_left_node( coord );
	std::pair< int, int > right = this->get_right_node( coord );
	return this->IsConcave( left, coord, right );
}

template < class Data >
bool Polygon< Data >::IsConcave( std::pair< int, int > left, std::pair< int, int > coord, std::pair< int, int > right )
{
	int x_1 = left.first,  x_2 = coord.first,  x_3 = right.first;
	int y_1 = left.second, y_2 = coord.second, y_3 = right.second;
	int u_1 = x_2 - x_1, u_2 = y_2 - y_1;
	int v_1 = x_3 - x_2, v_2 = y_3 - y_2;
	return u_1 * v_2 - u_2 * v_1 > 0;
}

template < class Data >
bool Polygon< Data >::Add( std::pair< int, int > start, std::pair< int, int > end )
{
	// double distance = sqrt( pow( end.first - start.first, 2 ) + pow( end.second - start.second, 2 ) );
	Graph< std::pair< int, int >, Data, int >::Add( start, end );
	if ( std::find( this->coords_.begin(), this->coords_.end(), start ) == this->coords_.end() )
		this->coords_.push_back( start );
	if ( std::find( this->coords_.begin(), this->coords_.end(), end ) == this->coords_.end() )
		this->coords_.push_back( end );
	return true;
}
