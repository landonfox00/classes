
#include <stdio.h>

#define MIN( x, y ) ( x > y ? y : x )
#define MAX( x, y ) ( x > y ? x : y )

void print_2d_array( int n, int m, int array[ n ][ m ] )
{
	for ( int i = 0; i < n; ++i )
	{
		for ( int j = 0; j < m; ++j )
			printf( "%d, ", array[ i ][ j ] );
		printf( "\n" );
	}
	printf( "\n" );
}

int f( int j )
{
	if ( j == 1 )
		return 1;
	if ( j == 2 )
		return 2;
	if ( j == 3 )
		return 4;
	if ( j == 4 )
		return 8;
	return 0;
}


/*
 *	problem 1b
 */

int opt_b( int i, int j, int n, int x[ n ], int c[ n ][ n ], int ( *f )( int ) )
{
	if ( i <= n && j <= n )
	{
		if ( !c[ i - 1 ][ j - 1 ] )
			c[ i - 1 ][ j - 1 ] = MAX( MIN( x[ i - 1 ], f( j ) ) + opt_b( i + 1, 1, n, x, c, f ), opt_b( i + 1, j + 1, n, x, c, f ) );
		return c[ i - 1 ][ j - 1 ];
	}
	return 0;
}

int opt_val_b( int n, int x[ n ], int count[ n ][ n ] )
{
	for ( int i = 0; i < n; ++i )
	{
		for ( int j = 0; j < n; ++j )
			count[ i ][ j ] = 0;
	}
	return opt_b( 1, 1, n, x, count, f );
}


/*
 *	problem 1c
 */

int opt_c( int i, int j, int n, int x[ n ], int c[ n ][ n ], int t[ n ][ n ], int ( *f )( int ) )
{
	if ( i <= n && j <= n )
	{
		if ( !c[ i - 1 ][ j - 1 ] )
		{
			int u = MIN( x[ i - 1 ], f( j ) ) + opt_c( i + 1, 1, n, x, c, t, f );
			int v = opt_c( i + 1, j + 1, n, x, c, t, f );
			c[ i - 1 ][ j - 1 ] = MAX( u, v );
			t[ i - 1 ][ j - 1 ] = u > v ? i : t[ i ][ j ];
		}
		return c[ i - 1 ][ j - 1 ];
	}
	return 0;
}

int opt_val_c( int n, int x[ n ], int count[ n ][ n ], int time[ n ][ n ] )
{
	for ( int i = 0; i < n; ++i )
	{
		for ( int j = 0; j < n; ++j )
		{
			count[ i ][ j ] = 0;
			time[ i ][ j ] = 0;
		}
	}
	return opt_c( 1, 1, n, x, count, time, f );
}


/*
 *	problem 1d
 */

void opt_sol( int i, int j, int n, int t[ n ][ n ] )
{
	if ( i <= n && t[ i - 1 ][ j - 1 ] )
	{
		printf( "%d, ", t[ i - 1 ][ j - 1 ] );
		opt_sol( t[ i - 1 ][ j - 1 ] + 1, 1, n, t );
	}
}


/*
 * 	main
 */

int main()
{
	int count[ 4 ][ 4 ];
	int time[ 4 ][ 4 ];
	int x[ 4 ] = { 1, 10, 10, 1 };

	// problem 1b
	printf( "1a) optimal value: %d\n", opt_val_b( 4, x, count ) );
	printf( "table of values for subproblems:\n" );
	print_2d_array( 4, 4, count );

	// problem 1c
	opt_val_c( 4, x, count, time );
	printf( "1b) table of times:\n" );
	print_2d_array( 4, 4, time );

	// problem 1d
	printf( "1c) optimal seconds to shoot lazer: " );
	opt_sol( 1, 1, 4, time );
	printf( "\n" );

	return 0;
}
