
module Bisection

	export bisect

	# bisect: performs the bisection method returning approximated value
	#	n: number of decimal places of accuracy
	#	[a, b]: closed interval
	#	s: sequence
	#	f: bisection condition (divergence of the sequence)
	function bisect( n, a, b, s, f )
		# c: midpoint
		c = 0
		# ceil( n * log2( 10 ) ) is the number of iterations required for
		# 	n decimals of accuracy
		for i in 1:ceil( n * log2( 10 ) )
			c = ( a + b ) / 2
			f_a = f( a, s ); f_c = f( c, s )
			# if ( s_a conv and s_c div ) or ( s_a div and s_c conv ), then look
			# 	to left subinterval
			if !f_a && f_c || f_a && !f_c
				b = c
			# otherwise, look to right subinterval
			else
				a = c
			end
		end
		# return approximated value
		return c
	end

end
