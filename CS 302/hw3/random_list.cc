
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <time.h>
#include <math.h>

int toInt( std::string str )
{
	int value;
	std::istringstream iss( str );
	iss >> value;
	return value;
}


// arg_1: amount of values
// arg_2: max value
// arg_3: output file
int main( int argc, char **argv )
{
	std::ofstream file;
	file.open( *( argv + 3 ) );

	int mag = toInt( *( argv + 2 ) );
	int len = toInt( *( argv + 1 ) );
	
	srand( time( 0 ) );
	int size = pow( 10, mag - 1 );
	for ( int i = 0; i < len - 1; i++ )
		file << rand() % size << std::endl;
	file << rand() % size;

	return 0;
}
