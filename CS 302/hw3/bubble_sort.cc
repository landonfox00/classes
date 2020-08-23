
#include <ctime>

#include "bubble_sort.h"

// constructor, inherits parent constructor: Sort
template < typename T >
BubbleSort< T >::BubbleSort( int item_count, std::string input_file ) : Sort< T >( item_count, input_file ) {}

// destructor, inherits parent constructor: Sort
template < typename T >
BubbleSort< T >::~BubbleSort() {}

// bubble sort
template < typename T >
void BubbleSort< T >::SortList()
{
	// record initial time
	this->time_init_ = std::clock();
	for ( int i = 0; i < this->kItemCount - 1; i++ )
	{
		for ( int j = 0; j < this->kItemCount - i - 1; j++ )
		{
			T left = this->list_[ j ];
			T right = this->list_[ j + 1 ];
			// if right term is less than left, swap
			if ( right < left )
			{
				this->list_[ j ] = right;
				this->list_[ j + 1 ] = left;
				this->swap_count_++;
			}
			// else, left and right are in appropiate positions
			// left is either less than or equal than right
			this->compar_count_++;
		}
	}
	// record final time
	this->time_ = ( double ) ( std::clock() - this->time_init_ ) / CLOCKS_PER_SEC;
}
