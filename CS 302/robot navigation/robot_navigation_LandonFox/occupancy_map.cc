
#include <vector>
#include <utility>
#include <memory>
#include <math.h>
#include <fstream>
#include <iomanip>

#include "graph_node.h"
#include "graph.h"
#include "occupancy_map.h"

template < class T >
OccupancyMap< T >::OccupancyMap( std::vector< std::vector< bool > > occupied, int x_dim, int y_dim )
	: occupied_( occupied ), x_dim_( x_dim ), y_dim_( y_dim ) { }

template < class T >
bool OccupancyMap< T >::Add( int x, int y )
{
	if ( !this->IsInMap( x, y ) || this->occupied_[ x ][ y ] )
		return false;
	std::pair< int, int > node( x, y );
	for ( int i = -1; i <= 1; ++i )
	{
		for ( int j = -1; j <= 1; ++j )
		{
			int x_1 = x + i;
			int y_1 = y + j;
			if ( !this->IsInMap( x_1, y_1 ) || ( i == 0 && j == 0 ) )
				continue;
			std::pair< int, int > adj( x_1, y_1 );
			if ( this->nodes_.count( adj ) == 0 )
				continue;
			Graph< std::pair< T, T >, double, double >::Add( node, adj, ( abs( i + j ) % 2 ) ? 1 : sqrt( 2 ) );
		}
	}
	return true;
}

template < class T >
void OccupancyMap< T >::Scan( int x, int y, int degree, int magnitude )
{
	double x_1 = magnitude * cos( 0.017452 * degree ) + x;
	double y_1 = magnitude * sin( 0.017452 * degree ) + y;
	double x_last = x, y_last = y;
	double dx = abs( x_1 - x );
	double dy = abs( y_1 - y );
	double n = dx + dy + 1;
	int x_inc = ( x_1 > x ) ? 1 : -1;
	int y_inc = ( y_1 > y ) ? 1 : -1;
	int error = dx - dy;
	dx *= 2;
	dy *= 2;
	for ( ; n > 0 && this->IsInMap( x, y ) && !this->occupied_[ x_last ][ y_last ]; --n )
	{
		x_last = x;
		y_last = y;
		this->ScanNode( x, y );
		if ( error > 0 )
		{
			x += x_inc;
			error -= dy;
		}
		else
		{
			y += y_inc;
			error += dx;
		}
	}
}

template < class T >
void OccupancyMap< T >::ScanNode( int x, int y )
{
	GraphNode< double > &node = this->nodes_[ std::pair< int, int >( x, y ) ];
	double log_odd;
	if ( this->occupied_[ x ][ y ] )
		log_odd = 0.9;
	else
		log_odd = -0.7;
	node.set_data( node.get_data() + log_odd );
}

template < class T >
void OccupancyMap< T >::Output( std::string filename )
{
	std::ofstream file;
	file.open( filename );
	file << "Dimensions: [ " << this->x_dim_ << " ][ " << this->y_dim_ << " ]" << std::endl;
	file << std::setw( 12 ) << 0;
	for ( int x = 1; x < this->x_dim_; ++x )
		file << std::setw( 6 ) << x;
	file << std::endl;
	for ( int y = 0; y < this->y_dim_; ++y )
	{
		file << std::setw( 2 * ( int ) log10( this->y_dim_ ) ) << y;
		for ( int x = 0; x < this->x_dim_; ++x )
		{
			std::pair< int, int> node( y, x );
			if ( this->nodes_.count( node ) > 0 )
				file << std::setw( 6 ) << this->nodes_[ node ].get_data();
			else
				file << std::setw( 6 ) << "0.0";
		}
		file << std::endl;
	}
}

template < class T >
bool OccupancyMap< T >::IsInMap( int x, int y )
{
	return x >= 0 && x < this->x_dim_ && y >= 0 && y < this->y_dim_;
}

template < class T >
int OccupancyMap< T >::get_x_dim()
{
	return this->x_dim_;
}

template < class T >
int OccupancyMap< T >::get_y_dim()
{
	return this->y_dim_;
}
