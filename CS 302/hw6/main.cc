
#include <iostream>
#include <cstdlib>
#include <time.h>

#include "./llrbt_online/TwoThree/LeftLeaningRedBlack.h"
#include "./llrbt_online/TwoThree/VoidRef.h"

void OccupyRand( int len, int* array )
{
	for ( int i = 0; i < len; ++i )
		array[ i ] = rand() % 100 + 1;
}

void Visit( LLTB_t* node )
{
	std::cout << "(" << ( node->IsRed   ? 'R' : 'B' ) << ", " << node->Ref.Key << ") ";
}

int main()
{
	srand( time( 0 ) );
	int len = 10;
	int* values = new int[ len ];
	OccupyRand( len, values );

	LeftLeaningRedBlack llrbt;
	for ( int i = 0; i < len; ++i )
	{
		VoidRef_t ref;
		ref.Key = values[ i ];
		llrbt.Insert( ref );
		LLTB_t* node = llrbt.get_node( values[ i ] );
		LLTB_t* parent = llrbt.get_parent( values[ i ] );
		std::cout << "Insert value: " << values[ i ] << std::endl;
		std::cout << "Node color: "   << ( node->IsRed   ? 'R' : 'B' ) << std::endl;
		if ( parent != NULL )
		{
			std::cout << "Parent value: " << parent->Ref.Key << std::endl;
			std::cout << "Parent color: " << ( parent->IsRed ? 'R' : 'B' ) << std::endl;
		}
		std::cout << "In-order traversal: ";
		llrbt.Traverse( Visit );
	}

	std::cout << "Delete 4th value: " << values[ 3 ] << std::endl;
	llrbt.Delete( values[ 3 ] );
	std::cout << "In-order traversal: ";
	llrbt.Traverse( Visit );

	delete values;
}