
#include <iostream>

void arrange_sign( int* array, int n )
{
	int k = 0;
	for ( int i = 0; i < n; ++i )
	{
		if ( array[ i ] < 0 )
		{
			int tmp = array[ k ];
			array[ k ] = array[ i ];
			array[ i ] = tmp;
			k++;
		}
	}
}

int main()
{
	int array[] = { 4, -3, 9, 8, 7, -4, -2, -1, 0, 6, -5 };
	arrange_sign( array, sizeof( array ) / sizeof( array[ 0 ] ) );
	std::cout << "Arrange signs of { 4, -3, 9, 8, 7, -4, -2, -1, 0, 6, -5 }:" << std::endl << "{ " << array[ 0 ];
	for ( int i = 1; i < sizeof( array ) / sizeof( array[ 0 ] ); ++i )
		std::cout << ", " << array[ i ];
	std::cout << " }" << std::endl;
	return 0;
}