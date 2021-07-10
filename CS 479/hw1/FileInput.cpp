
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "FileInput.h"

std::vector< std::vector< double > > read_csv( std::string filename )
{
	std::vector< std::vector< double > > inputs;
	std::ifstream file( filename );
	
	if ( !file.is_open() )
		throw std::runtime_error( filename + " could not be opened" );

	std::string line;
	std::vector< double > input;
	while ( std::getline( file, line ) )
	{
		unsigned int i = line.find( ',' );
		input.push_back( std::stod( line.substr( 0, i ) ) );
		input.push_back( std::stod( line.substr( i + 1, line.length() ) ) );
		inputs.push_back( input );
		input.clear();
	}

	return inputs;
}
