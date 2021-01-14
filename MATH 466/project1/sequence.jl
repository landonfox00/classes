
module Sequence

	export x, x_even, x_odd, output

	# x_init: global initial value of sequence.
	# 	used to varify if initial value has changed
	x_init = 1
	# x_values: used to store all values of sequence.
	# 	nth value of x_values is the nth term of sequence
	x_values = []

	# x: returns the nth term of sequence with initial condition x_1
	#	also stores all terms into x_values
	function x( x_1, n )
		global x_init, x_values
		# if initial value changes, remove all perviously computed values
		# 	to avoid conflicts
		if x_init != x_1
			x_init = x_1
			x_values = []
		end
		len = length( x_values )
		# if length of x_values exceeds n, then nth term already lies in x_values
		if len >= n
			return x_values[ n ]
		end
		# if x_values is empty, append initial value
		if len == 0
			push!( x_values, x_1 )
			len = 1
		end
		# let recursive helper return computed value
		return x_helper( n, len )
	end

	# x_helper: recursive helper to x function
	# 	computes nth term and stores all into x_values
	function x_helper( n, len )
		# base case: if length of x_values is equal to n, then return the value
		if n == len
			return x_values[ n ]
		end
		# value does not exist in x_values, compute (len + 1)th term and repeat
		push!( x_values, ( 1 + 1/x_values[ len ] )^len )
		return x_helper( n, len + 1 )
	end

	# x_even: returns (2n)th term of sequence
	x_even( x_1, n ) = x( x_1, 2 * n )

	# x_odd: returns (2n-1)th term of sequence
	x_odd( x_1, n ) = x( x_1, 2 * n - 1 )

	# output: prints n terms of sequence with initial condition x_1
	function output( x_1, n )
		x( x_1, n )
		for i in 1:n
			println( i, " : ", x_values[ i ] )
		end
	end

end
