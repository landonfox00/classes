
#include <iostream>
#include <fstream>
#include <ctime>

#include "sort.h"

// constructor, initialization of data members and occupies list with items in input file
template < typename T >
Sort< T >::Sort( int item_count, std::string input_file )
	: kItemCount( item_count ), filename_( input_file ), list_( 0 ), time_init_(), time_( 0.0 ), compar_count_( 0 ), swap_count_( 0 )
{
	this->list_ = new T[ kItemCount ];
	this->OccupyList();
}

// deconstructor, deletes pointer to list
template < typename T >
Sort< T >::~Sort()
{
	delete this->list_;
}

// returns true if list is sorted properly
// list is considered properly sorted if all items are less than previous
template < typename T >
bool Sort< T >::IsSorted()
{
	int curr_value = 0;
	for ( int i = 0; i < this->kItemCount; i++ )
	{
		int value = this->list_[ i ];
		if ( value < curr_value )
			return false;
		curr_value = value;
	}
	return true;
}

// outputs results from sort to std::cout
template < typename T >
void Sort< T >::OutputSorted()
{
	std::cout << "Sorted correctly: " << ( this->IsSorted() ? "true" : "false" ) << std::endl;
}

// outputs performace of sort: time, comparisons, and swaps, to std::cout
template < typename T >
void Sort< T >::OutputPerf()
{
	std::cout << "Performance: time=" << this->time_ << ", comparisons=" << this->compar_count_ << ", swapCount=" << this->swap_count_ << std::endl;
}

// outputs list to output_file
template < typename T >
void Sort< T >::OutputList( std::string output_file )
{
	std::ofstream file;
	file.open( output_file.c_str() );
	for ( int i = 0; i < this->kItemCount - 1; i++ )
		file << this->list_[ i ] << std::endl;
	file << this->list_[ this->kItemCount - 1 ];
}

// collection of OutputSorted, OutputPerf, and OutputList to output all information regarding sort
template < typename T >
void Sort< T >::Output( std::string output_file )
{
	this->OutputSorted();
	this->OutputPerf();
	this->OutputList( output_file );
}

// accessor for item_count_
template < typename T >
long Sort< T >::get_item_count() const
{
	return this->kItemCount;
}

// accessor for time_
template < typename T >
long double Sort< T >::get_time()
{
	return this->time_;
}

// accessor for compar_count_
template < typename T >
unsigned long long Sort< T >::get_compar_count()
{
	return this->compar_count_;
}

// accessor for swap_count_
template < typename T >
unsigned long long Sort< T >::get_swap_count()
{
	return this->swap_count_;
}

// fills list with items from input source filename_
template < typename T >
void Sort< T >::OccupyList()
{
	std::ifstream file( this->filename_.c_str() );
	for ( int i = 0; i < this->kItemCount; i++ )
		file >> this->list_[ i ];
}
