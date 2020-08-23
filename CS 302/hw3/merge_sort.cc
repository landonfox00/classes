
#include <ctime>

#include "merge_sort.h"

// constructor, inherits parent constructor: Sort
template < typename T >
MergeSort< T >::MergeSort( int item_count, std::string input_file ) : Sort< T >( item_count, input_file ) {}

// destructor, inherits parent constructor: Sort
template < typename T >
MergeSort< T >::~MergeSort() {}

// merge sort
template < typename T >
void MergeSort< T >::SortList()
{
	// record initial time
	this->time_init_ = std::clock();
	this->MergeSortList( 0, this->kItemCount - 1 );
	// record final time
	this->time_ = ( double ) ( std::clock() - this->time_init_ ) / CLOCKS_PER_SEC;
}

// recursive list seperation
// calls MergeList once all items in list are seperated
template < typename T >
void MergeSort< T >::MergeSortList( int first, int last )
{
	if ( first < last )
	{
		int mid = ( first + last ) / 2;
		this->MergeSortList( first, mid );
		this->MergeSortList( mid + 1, last );
		this->MergeList( first, mid, last );
	}
}

// merges left and right ordered list into one ordered list
template < typename T >
void MergeSort< T >::MergeList( int first, int mid, int last )
{
	int i_left = first;			// index of initial value in left list
	int i_right = mid + 1;		// index of initial value in right list
	int last_left = mid;		// index of final value in left list
	int last_right = last;		// index of final value in right list
	int len = last - first + 1;	// length of final merged list
	T temp_arr[ len ]; 			// holds ordered list
	bool left_has_item  = true; // always has at least one item
	bool right_has_item = true; // always has at least one item

	// an item will be appended to tempArr every loop
	for ( int i = 0; i < len; i++ )
	{
		T left  = this->list_[ i_left  ];
		T right = this->list_[ i_right ];
		// can append left item only if left has an item, and
		// either right list is empty or left value is ordered first
		bool can_append_left = ( left_has_item && ( !right_has_item || ( left < right ) ) );
		if ( can_append_left )
		{
			temp_arr[ i ] = left;
			i_left++;
		}
		// if cannot append left then must append right
		// if right is less than left or right equals left or there is no left
		else
		{
			temp_arr[ i ] = right;
			i_right++;
		}

		left_has_item  = ( i_left  <= last_left );
		right_has_item = ( i_right <= last_right );
		this->compar_count_ += 3;	// comparisons can_append_left, left_has_item, and right_has_item
		this->swap_count_++;		// swaps once per loop
	}

	// place all items into original list from temp_arr
	for ( int i = 0; i < len; i++ )
		this->list_[ first + i ] = temp_arr[ i ];
}
