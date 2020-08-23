
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>

void splitStr( const std::string& str, std::vector< std::string >& words )
{
	std::istringstream iss( str );
	std::copy( std::istream_iterator< std::string >( iss ), std::istream_iterator< std::string >(), std::back_inserter( words ) );
}

// make_xref assumes each line is distinguished via index of input vector
void make_xref( std::vector< std::string >& input, std::map< std::string, std::vector< int > >& map )
{
	for ( unsigned int i = 0; i < input.size(); ++i )
	{
		std::vector< std::string > words;
		splitStr( input[ i ], words );
		for ( unsigned int j = 0; j < words.size(); ++j )
			map[ words[ j ] ].push_back( i + 1 );
	}
}

void print_xref( std::ostream& out, std::map< std::string, std::vector< int > >& map )
{
	typename std::map< std::string, std::vector< int > >::iterator end = map.end();
	for ( typename std::map< std::string, std::vector< int > >::iterator it = map.begin(); it != end; ++it )
	{
		out << it->first << ' ';
		unsigned end_v = it->second.size();
		for ( unsigned int i = 0; i < end_v - 1; ++i )
			out << it->second[ i ] << ", ";
		out << it->second[ end_v - 1 ] << '.' << std::endl;
	}
}

int main()
{
	std::map< std::string, std::vector< int > > map;
	std::vector< std::string > input = { "foo bar tag\n", "buz tag bam\n", "tag foo ham\n" };
	make_xref( input, map );
	print_xref( std::cout, map );
	return 0;
}
