
# secant: secant method
#	f: function, approximating x such that f(x) = 0 
#	[x_0, x_1]: interval containing root, i.e. f(x_0) * f(x_1) < 0
#	n: iterations
function secant( f, x_0, x_1, n )
	if n == 0
		return x_0
	elseif n == 1
		return x_1
	elseif n == 2
		return x_1 - f( x_1 ) * ( x_1 - x_0 ) / ( f( x_1 ) - f( x_0 ) )
	end
	x_i = secant( f, x_0, x_1, n - 1 )
	x_j = secant( f, x_0, x_1, n - 2 )
	return x_i - f( x_i ) * ( x_i - x_j ) / ( f( x_i ) - f( x_j ) )
end

f( x ) = sin( x ) - x / 2
print( secant( f, pi / 2, pi, 6 ) )