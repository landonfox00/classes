
#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "sort.h"

template < typename T >
class BubbleSort : public Sort< T >
{
public:
	BubbleSort( int item_count, std::string input_file );
	~BubbleSort();

	void SortList();
};

#include "bubble_sort.cc"

#endif
