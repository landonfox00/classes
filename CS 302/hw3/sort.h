
#ifndef SORT_H
#define SORT_H

#include <ctime>

// typename T requires use of comparison operator '<' and must be able to be read from file
template < typename T >
class Sort
{
public:
	Sort( int item_count, std::string input_file );
	virtual ~Sort();

	virtual void SortList() = 0;

	bool IsSorted();

	void OutputSorted();
	void OutputPerf();
	void OutputList( std::string output_file );
	void Output( std::string output_file );

	long get_item_count() const;
	long double get_time();
	unsigned long long get_compar_count();
	unsigned long long get_swap_count();

protected:
	const long kItemCount;				// item count for items in list
	std::string filename_;				// filename of list source
	T *list_;							// pointer to array of items to be sorted

	std::clock_t time_init_;			// initial time of alogrithm start
	long double time_;					// total time algorithm sorting process
	unsigned long long compar_count_;	// comparison count during sort
	unsigned long long swap_count_;		// swap count during sort

private:
	void OccupyList();
};

#include "sort.cc"

#endif
