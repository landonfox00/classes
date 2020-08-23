
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <time.h>

int toInt( std::string str )
{
	int value;
	std::istringstream iss( str );
	iss >> value;
	return value;
}

bool check( int len, int* values )
{
	bool* checks = new bool[ 201 ];
	for ( int i = 0; i < len; i++ )
	{
		if ( checks[ values[ i ] ] )
		{
			std::cout << values[ i ] << std::endl;
			return false;
		}
		checks[ values[ i ] ] = true;
	}
	delete checks;
	return true;
}

int main( int argc, char **argv )
{
	std::ofstream file;
	file.open( *( argv + 3 ) );

	int max = toInt( *( argv + 2 ) );
	int len = toInt( *( argv + 1 ) );
	int* values = new int[ len ];
	
	srand( time( 0 ) );
	for ( int i = 0; i < len; i++ )
	{
		values[ i ] = rand() % max;
		int j = 0;
		while ( j < i )
		{
			if ( values[ j ] == values[ i ] )
			{
				values[ i ] = rand() % max;
				j = 0;
				continue;
			}
			j++;
		}
	}

	std::cout << "passed: " << check( len, values ) << std::endl;

	for ( int i = 0; i < len - 1; i++ )
		file << values[ i ] << std::endl;
	file << values[ len - 1 ];

	delete values;

	return 0;
}
