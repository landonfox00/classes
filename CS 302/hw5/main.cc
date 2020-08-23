
#include <algorithm>
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>

template < class T >
std::vector< T >& Occupy( std::vector< T >& v, std::string filename )
{
	std::ifstream file( filename.c_str() );
	T value;
	while ( file.good() )
	{
		file >> value;
		v.push_back( value );
	}
	return v;
}

template < class T >
T GetAvg( const std::vector< T >& v )
{
	double sum = 0;
	std::size_t len = v.size();
	for ( int i = 0; i < len; i++ )
		sum += v[ i ];
	return floor( sum / len );
}

template < class T >
void DisplayHeap( const std::vector< T >& v )
{
	std::cout << "Heap: { ";
	std::size_t len = v.size();
	for ( int i = 0; i < len - 1; i++ )
		std::cout << v[ i ] << ", ";
	std::cout << v.back() << " }" << std::endl;
}

int main()
{
	std::vector< int > v;
	Occupy< int >( v, "values.txt" );

	std::make_heap( v.begin(), v.end() );
	DisplayHeap< int >( v );

	int avg = GetAvg< int >( v );
	std::cout << std::endl << "Average: " << avg << std::endl;
	v.push_back( avg );
	std::push_heap( v.begin(), v.end() );
	std::cout << "Pushed average" << std::endl;
	DisplayHeap< int >( v );

	std::pop_heap( v.begin(), v.end() );
	v.pop_back();
	std::sort_heap( v.begin(), v.end() );
	std::cout << std::endl << "Popped max & sorted" << std::endl;
	DisplayHeap< int >( v );

}
