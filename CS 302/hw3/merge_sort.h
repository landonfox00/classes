
#ifndef MERGESORT_H
#define MERGESORT_H

#include "sort.h"

template < typename T >
class MergeSort : public Sort< T >
{
public:
	MergeSort( int item_count, std::string input_file );
	~MergeSort();

	void SortList();

private:
	void MergeSortList( int first, int last );
	void MergeList( int first, int mid, int last );
};

#include "merge_sort.cc"

#endif
