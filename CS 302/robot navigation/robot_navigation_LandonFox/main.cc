
#include <vector>
#include <iostream>

#include "robot.h"

#define SIZE 1000
#define LOWER_BOUND 250
#define UPPER_BOUND 500

int main()
{
	std::vector< std::vector< bool > > occupied_map( SIZE );
	for ( int i = 0; i < SIZE; ++i )
	{
		for ( int j = 0; j < SIZE; ++j )
			occupied_map[ i ].push_back( i >= LOWER_BOUND && i <= UPPER_BOUND && j >= LOWER_BOUND && j <= UPPER_BOUND );
	}
	std::vector< std::vector< int > > coordinates;
	coordinates.push_back( {   1,   1, 3 } );
	coordinates.push_back( { 148, 157, 3 } );
	coordinates.push_back( { 274,  77, 3 } );
	coordinates.push_back( { 422,  70, 3 } );
	coordinates.push_back( { 529,  73, 3 } );
	coordinates.push_back( { 679,  99, 3 } );
	coordinates.push_back( { 607, 378, 0 } );
	coordinates.push_back( { 435, 658, 2 } );
	coordinates.push_back( { 216, 683, 0 } );
	coordinates.push_back( { 500, 700, 2 } );

	Robot robot( occupied_map, SIZE, SIZE );

	for ( int i = 0; i < 10; ++i )
	{
		robot.Move( coordinates[ i ][ 0 ], coordinates[ i ][ 1 ], coordinates[ i ][ 2 ] );
		robot.Scan();
	}

	robot.DisplayMap( "map.txt" );
}
