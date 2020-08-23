
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "sort.h"
#include "bubble_sort.h"
#include "merge_sort.h"

// prompts user menu and returns user's input
char Prompt()
{
	std::string input;
	std::cout << "\tA) Average all"					   	   << std::endl;
	std::cout << "\tB) Bubble sort, 1,000   unsorted items" << std::endl;
	std::cout << "\tC) Bubble sort, 10,000  unsorted items" << std::endl;
	std::cout << "\tD) Bubble sort, 100,000 unsorted items" << std::endl;
	std::cout << "\tE) Bubble sort, 1,000   sorted items"   << std::endl;
	std::cout << "\tF) Bubble sort, 10,000  sorted items"   << std::endl;
	std::cout << "\tG) Bubble sort, 100,000 sorted items"   << std::endl;
	std::cout << "\tH) Merge sort,  1,000   unsorted items" << std::endl;
	std::cout << "\tI) Merge sort,  10,000  unsorted items" << std::endl;
	std::cout << "\tJ) Merge sort,  100,000 unsorted items" << std::endl;
	std::cout << "\tK) Merge sort,  1,000   sorted items"   << std::endl;
	std::cout << "\tL) Merge sort,  10,000  sorted items"   << std::endl;
	std::cout << "\tM) Merge sort,  100,000 sorted items"   << std::endl;
	std::cout << "Enter selection or 'X' to exit: ";
	std::getline( std::cin, input );
	return std::toupper(input[ 0 ]);
}

// helper function, returns a given int in string format
std::string ToStr( int i )
{
	std::stringstream ss;
	ss << i;
	return ss.str();
}

// creates and outputs a BubbleSort object, sorts list, and outputs its information
// default input file: ( "sorted" or "unsorted" )( item_count )( ".txt" )
// default output file: ( "bubble_" )( input_filename )
BubbleSort< int >* OutputBubble( int item_count, bool sorted )
{
	std::string sort_str = ( sorted ? "sorted" : "unsorted" );
	std::cout << "Bubble sort, " << item_count << ", " << sort_str << " items" << std::endl;
	std::string filename = sort_str + ToStr( item_count ) + ".txt";
	BubbleSort< int > *bs = new BubbleSort< int >( item_count, filename );
	bs->SortList();
	bs->Output( "bubble_" + filename );
	std::cout << std::endl;
	return bs;
}

// creates and outputs a BubbleSort object, sorts list, and outputs its information
// default input file: ( "sorted" or "unsorted" )( item_count )( ".txt" )
// default output file: ( "merge_" )( input_filename )
MergeSort< int >* OutputMerge( int item_count, bool sorted )
{
	std::string sort_str = ( sorted ? "sorted" : "unsorted" );
	std::cout << "Merge sort, " << item_count << ", " << sort_str << " items" << std::endl;
	std::string filename = sort_str + ToStr( item_count ) + ".txt";
	MergeSort< int > *ms = new MergeSort< int >( item_count, filename );
	ms->SortList();
	ms->Output( "merge_" + filename );
	std::cout << std::endl;
	return ms;
}

// typedef of all functions regarding variations of item count and sorted input
typedef Sort< int >* ( *SortFn )();

// B) Bubble sort, 1,000 unsorted items
Sort< int >* BubbleUnsorted3()
{
	return OutputBubble( 1000, false );
}

// C) Bubble sort, 10,000 unsorted items
Sort< int >* BubbleUnsorted4()
{
	return OutputBubble( 10000, false );
}

// D) Bubble sort, 100,000 unsorted items
Sort< int >* BubbleUnsorted5()
{
	return OutputBubble( 100000, false );
}

// E) Bubble sort, 1,000 sorted items
Sort< int >* BubbleSorted3()
{
	return OutputBubble( 1000, true );
}

// F) Bubble sort, 10,000 sorted items
Sort< int >* BubbleSorted4()
{
	return OutputBubble( 10000, true );
}

// G) Bubble sort, 100,000 sorted items
Sort< int >* BubbleSorted5()
{
	return OutputBubble( 100000, true );
}

// H) Merge sort, 1,000 unsorted items
Sort< int >* MergeUnsorted3()
{
	return OutputMerge( 1000, false );
}

// I) Merge sort, 10,000 unsorted items
Sort< int >* MergeUnsorted4()
{
	return OutputMerge( 10000, false );
}

// J) Merge sort, 100,000 unsorted items
Sort< int >* MergeUnsorted5()
{
	return OutputMerge( 100000, false );
}

// K) Merge sort, 1,000 sorted items
Sort< int >* MergeSorted3()
{
	return OutputMerge( 1000, true );
}

// L) Merge sort, 10,000 sorted items
Sort< int >* MergeSorted4()
{
	return OutputMerge( 10000, true );
}

// M) Merge sort, 100,000 sorted items
Sort< int >* MergeSorted5()
{
	return OutputMerge( 100000, true );
}

SortFn bubble_sorts[] = {
	BubbleUnsorted3,
	BubbleUnsorted4,
	BubbleUnsorted5,
	BubbleSorted3,
	BubbleSorted4,
	BubbleSorted5
};
SortFn merge_sorts[] = {
	MergeUnsorted3,
	MergeUnsorted4,
	MergeUnsorted5,
	MergeSorted3,
	MergeSorted4,
	MergeSorted5
};

// A) Average all
void AllSorts()
{
	std::cout << "Average all" << std::endl;
	long double bubble_time = 0, merge_time = 0;
	unsigned long long bubble_compars = 0, merge_compars = 0;
	unsigned long long bubble_swaps = 0,   merge_swaps = 0;
	// for each variant of the bubble and merge sorts, average the time, comparisons, and swaps
	for ( int i = 0; i < 6; i++ )
	{
		Sort< int >* bs = bubble_sorts[ i ]();
		Sort< int >* ms = merge_sorts[ i ]();
		bubble_time += bs->get_time() / 6;
		merge_time  += ms->get_time() / 6;
		bubble_compars += bs->get_compar_count() / 6;
		merge_compars  += ms->get_compar_count() / 6;
		bubble_swaps += bs->get_swap_count() / 6;
		merge_swaps  += ms->get_swap_count() / 6;
		delete bs;
		delete ms;
	}
	// output averages
	std::cout << std::setw( 10 ) << "Algorithm" << std::setw( 16 ) << "Time Avg"  << std::setw( 16 ) << "Comparisons Avg" << std::setw( 16 ) << "Swaps Avg"  << std::endl;
	std::cout << std::setw( 10 ) << "Bubble"    << std::setw( 16 ) << bubble_time << std::setw( 16 ) << bubble_compars    << std::setw( 16 ) << bubble_swaps << std::endl;
	std::cout << std::setw( 10 ) << "Merge"     << std::setw( 16 ) << merge_time  << std::setw( 16 ) << merge_compars     << std::setw( 16 ) << merge_swaps  << std::endl;
	std::cout << std::endl;
}

int main()
{
	char input;
	do
	{
		// obtain user input
		input = Prompt();
		std::cout << std::endl << input << ") ";
		// given input, perform appropiate sort variant
		switch ( input )
		{
			case 'A':
				AllSorts();
				break;
			case 'B':
				delete BubbleUnsorted3();
				break;
			case 'C':
				delete BubbleUnsorted4();
				break;
			case 'D':
				delete BubbleUnsorted5();
				break;
			case 'E':
				delete BubbleSorted3();
				break;
			case 'F':
				delete BubbleSorted4();
				break;
			case 'G':
				delete BubbleSorted5();
				break;
			case 'H':
				delete MergeUnsorted3();
				break;
			case 'I':
				delete MergeUnsorted4();
				break;
			case 'J':
				delete MergeUnsorted5();
				break;
			case 'K':
				delete MergeSorted3();
				break;
			case 'L':
				delete MergeSorted4();
				break;
			case 'M':
				delete MergeSorted5();
				break;
			case 'X':
				break;
			default:
				std::cout << "Invalid input" << std::endl;
		}
	// 'X' input exits program
	} while ( input != 'X' );
	std::cout << "Exit" << std::endl;
}
