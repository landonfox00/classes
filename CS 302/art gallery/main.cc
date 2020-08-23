
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <math.h>

#include "polygon.h"
#include "precond_violated_exception.h"

typename std::vector< std::pair< int, int > >::iterator get_left( std::vector< std::pair< int, int > >& coords, std::pair< int, int > coord )
{
	std::vector< std::pair< int, int > >::iterator begin = coords.begin(), end = coords.end();
	std::vector< std::pair< int, int > >::iterator it = std::find( begin, end, coord );
	if ( it == begin )
		return end - 1;
	return it - 1;
}

std::pair< int, int > get_left_coord( std::vector< std::pair< int, int > >& coords, std::pair< int, int > coord )
{
	return *get_left( coords, coord );
}

typename std::vector< std::pair< int, int > >::iterator get_right( std::vector< std::pair< int, int > >& coords, std::pair< int, int > coord )
{
	std::vector< std::pair< int, int > >::iterator begin = coords.begin(), end = coords.end();
	std::vector< std::pair< int, int > >::iterator it = std::find( begin, end, coord );
	if ( it == end )
		return begin;
	return it + 1;
}

std::pair< int, int > get_right_coord( std::vector< std::pair< int, int > >& coords, std::pair< int, int > coord )
{
	return *get_right( coords, coord );
}

double TriangleArea( int x_1, int y_1, int x_2, int y_2, int x_3, int y_3 )
{
	return std::abs( ( x_1 * ( y_2 - y_3 ) + x_2 * ( y_3 - y_1 ) + x_3 * ( y_1 - y_2 ) ) / 2.0 );
}

bool IsInsideEar( int x_1, int y_1, int x_2, int y_2, int x_3, int y_3, int x, int y )
{
	double A  = TriangleArea( x_1, y_1, x_2, y_2, x_3, y_3 );
	double A1 = TriangleArea( x, y, x_2, y_2, x_3, y_3 );
	double A2 = TriangleArea( x_1, y_1, x, y, x_3, y_3 );
	double A3 = TriangleArea( x_1, y_1, x_2, y_2, x, y );
	return A == A1 + A2 + A3;
}

bool IsAnyInsideEar( Polygon< int >& polygon, int x_1, int y_1, int x_2, int y_2, int x_3, int y_3 )
{
	std::vector< std::pair< int, int > > coords = polygon.get_coords();
	for ( unsigned int i = 0; i < coords.size(); ++i )
	{
		int x = coords[ i ].first;
		int y = coords[ i ].second;
		if ( ( x != x_1 || y != y_1 ) && ( x != x_2 || y != y_2 ) && ( x != x_3 || y != y_3 ) && IsInsideEar( x_1, y_1, x_2, y_2, x_3, y_3, x, y ) )
			return true;
	}
	return false;
}

std::pair< int, int > FindEar( Polygon< int >& polygon, std::vector< std::pair< int, int > >& coords, typename std::vector< std::pair< int, int > >::iterator start ) throw ( PrecondViolatedException )
{
	if ( coords.size() < 3 )
		throw PrecondViolatedException( "No ear can be found of a subsection of a polygon consisting of 2 or less verticies" );
	bool flag = true;
	for ( typename std::vector< std::pair< int, int > >::iterator it = start; it != start || flag; it + 1 == coords.end() ? it = coords.begin() : ++it )
	{
		flag = false;
		std::pair< int, int > left = get_left_coord( coords, *it );
		std::pair< int, int > right = get_right_coord( coords, *it );
		if ( !polygon.IsAdjacent( left, right ) && !polygon.IsAdjacent( right, left ) && polygon.IsConcave( left, *it, right ) && !IsAnyInsideEar( polygon, left.first, left.second, it->first, it->second, right.first, right.second ) )
			return *it;
	}
	throw PrecondViolatedException( "No ear can be found of the given polygon" );
}

void Triangulate( Polygon< int >& polygon, std::vector< std::pair< int, int > >& coords, typename std::vector< std::pair< int, int > >::iterator prev_right, void Visit( Polygon< int >&, std::vector< std::pair< int, int > >& ) )
{
	if ( coords.size() > 3 )
	{
		std::vector< std::pair< int, int > > coords_cp( coords );
		std::pair< int, int > ear = FindEar( polygon, coords, prev_right );
		std::pair< int, int > left = get_left_coord( coords_cp, ear );
		std::pair< int, int > right = get_right_coord( coords_cp, ear );
		coords_cp.erase( std::find( coords_cp.begin(), coords_cp.end(), ear ) );
		polygon.Add( left, right );
		Triangulate( polygon, coords_cp, std::find( coords_cp.begin(), coords_cp.end(), right ), Visit );
		Visit( polygon, coords );
	}
}

int GetNonAdjColor( Polygon< int >& polygon, std::vector< std::pair< int, int > >& coords, std::pair< int, int > coord )
{
	std::vector< int > colors = { 1, 2, 3 };
	for ( unsigned int i = 0; i < coords.size(); ++i )
	{
		std::vector< int >::iterator color = std::find( colors.begin(), colors.end(), polygon.get_node( coords[ i ] ).get_data() );
		if ( color != colors.end() && ( polygon.IsAdjacent( coord, coords[ i ] ) || polygon.IsAdjacent( coords[ i ], coord ) ) )
			colors.erase( color );
	}
	return colors[ 0 ];
}

void Color( Polygon< int >& polygon, std::vector< std::pair< int, int > >& coords )
{
	if ( coords.size() > 3 )
	{
		for ( unsigned int i = 0; i < coords.size(); ++i )
		{
			GraphNode< int >& node = polygon.get_node( coords[ i ] );
			if ( node.get_data() == 0 )
				node.set_data( GetNonAdjColor( polygon, coords, coords[ i ] ) );
		}
	}
	else
	{
		for ( unsigned int i = 0; i < coords.size(); ++i )
			polygon.get_node( coords[ i ] ).set_data( i + 1 );
	}
}

int FindLeastColor( Polygon< int >& polygon )
{
	std::vector< std::pair< int, int > > coords = polygon.get_coords();
	std::vector< unsigned int > color_count( 3 );
	for ( unsigned int i = 0; i < coords.size(); ++i )
		color_count[ polygon.get_node( coords[ i ] ).get_data() - 1 ]++;
	unsigned int min = coords.size();
	int min_color;
	for ( unsigned int i = 0; i < color_count.size(); ++i )
	{
		if ( color_count[ i ] < min )
		{
			min = color_count[ i ];
			min_color = i + 1;
		}
	}
	return min_color;
}

std::vector< std::pair< int, int > > FindGuardPositions( Polygon< int >& polygon )
{
	int color = FindLeastColor( polygon );
	std::vector< std::pair< int, int > > coords = polygon.get_coords();
	std::vector< std::pair< int, int > > positions;
	for ( unsigned int i = 0; i < coords.size(); ++i )
	{
		if ( polygon.get_node( coords[ i ] ).get_data() == color )
			positions.push_back( coords[ i ] );
	}
	return positions;
}

int main()
{
	// Polygon requires points in counterclockwise order
	Polygon< int > polygon;
	polygon.Add( std::pair< int, int >( 6, 5 ), std::pair< int, int >( 5, 9 ) );
	polygon.Add( std::pair< int, int >( 5, 9 ), std::pair< int, int >( 3, 6 ) );
	polygon.Add( std::pair< int, int >( 3, 6 ), std::pair< int, int >( 4, 5 ) );
	polygon.Add( std::pair< int, int >( 4, 5 ), std::pair< int, int >( 5, 3 ) );
	polygon.Add( std::pair< int, int >( 5, 3 ), std::pair< int, int >( 8, 2 ) );
	polygon.Add( std::pair< int, int >( 8, 2 ), std::pair< int, int >( 9, 6 ) );
	polygon.Add( std::pair< int, int >( 9, 6 ), std::pair< int, int >( 6, 5 ) );

	std::vector< std::pair< int, int > > coords = polygon.get_coords();
	Triangulate( polygon, coords, coords.begin(), Color );
	coords = polygon.get_coords();

	// for ( unsigned int i = 0; i < coords.size(); ++i )
	// {
	// 	for ( unsigned int j = 0; j < coords.size(); ++j )
	// 	{
	// 		int c_1 = polygon.get_node( coords[ i ] ).get_data();
	// 		int c_2 = polygon.get_node( coords[ j ] ).get_data();
	// 		if ( polygon.IsAdjacent( coords[ i ], coords[ j ] ) )
	// 			std::cout << c_1 << ": ( " << coords[ i ].first << ", " << coords[ i ].second << " ) -> " << c_2 << ": ( " << coords[ j ].first << ", " << coords[ j ].second << " )" << std::endl;
	// 	}
	// }

	std::vector< std::pair< int, int > > positions = FindGuardPositions( polygon );
	for ( unsigned int i = 0; i < positions.size(); ++i )
		std::cout << "Guard " << i + 1 << " position: ( " << positions[ i ].first << ", " << positions[ i ].second << " )" << std::endl;

	return 0;
}
