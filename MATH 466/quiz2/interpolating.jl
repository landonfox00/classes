
using Plots

f( t ) = t / ( 1 + t^3 )
x = 1:5
y = f.( x )

# l: Lagrange basis function $$\ell_j(t) = \prod_{i \neq j} \frac{t - x_i}{x_j - x_i}$$
#	j: index
#	t: polynomial variable
#	x: sequence of inputs
function l( j, t )
	global x
	r = 1
	for i in 1:length( x )
		if i != j
			r *= ( t - x[ i ] ) / ( x[ j ] - x[ i ] )
		end
	end
	return r
end

# p: polynomial $$p(t) = \sum_{j \in [n]} y_j l_j(t)$$
#	t: polynomial variable
#	x: sequence of inputs
#	y: sequence of outputs
function p( t )
	global x, y
	r = 0
	for j in 1:length( x )
		r += y[ j ] * l( j, t )
	end
	return r
end

function main()
	global l, p, x, y
	print( p.( x ) )
	# x_vals = [ 0:0.1:6; ]
	# plot( x_vals, f.( x_vals ), size = [ 300, 200 ] )
	# scatter!( x, y )
	# plt = plot!( x_vals, p.( x_vals ) )
	# png( plt, "plt" )
end

main()