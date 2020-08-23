
#include <iostream>

int largest( int* array, int start, int end )
{
	if ( start == end )
		return start;
	int mid = ( start + end ) / 2;
	int left = largest( array, start, mid );
	int right = largest( array, mid + 1, end );
	if ( array[ left ] > array[ right ] )
		return left;
	return right;
}

int main()
{
	int array[] = { 1, 4, 9, 3, 4, 9, 5, 6, 9, 3, 7 };
	std::cout << "Largest item of { 1, 4, 9, 3, 4, 9, 5, 6, 9, 3, 7 } is index:" << std::endl
		<< largest( array, 0, 10 ) << std::endl;
	return 0;
}
