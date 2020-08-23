
#include <vector>

#include "robot.h"

Robot::Robot( std::vector< std::vector< bool > > occupied_map, int map_x_dim, int map_y_dim )
	: map_( occupied_map, map_x_dim, map_x_dim ), x_(), y_(), orientation_() { }

bool Robot::Move( int x, int y, int orientation )
{
	bool can_move = this->map_.Add( x, y );
	if ( can_move )
	{
		this->x_ = x;
		this->y_ = y;
		this->orientation_ = ( orientation + 2 ) % 4;
	}
	return can_move;
}

void Robot::Scan()
{
	int degree_f = 90 * this->orientation_ + 90;
	for ( int deg = 90 * this->orientation_ - 90; deg <= degree_f; deg += DEGREE_INCR )
		this->map_.Scan( this->x_, this->y_, deg, MAGNITUDE );
}

void Robot::DisplayMap( std::string filename )
{
	this->map_.Output( filename );
}
