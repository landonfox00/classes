
include( "./sequence.jl" )
include( "./bisection.jl" )
using .Sequence, .Bisection

# div: determines if sequence s diverges with initial value s_1
# 	computes first few indices to see if they become large
function div( s_1, s )
	for i in 1:50
		if s( s_1, i ) > 100
			return true
		end
	end
	return false
end

function main()

	# problem 2
	println( "problem 2" )
	Sequence.output( 1, 50 )
	println()

	# problem 4
	println( "problem 4" )
	Sequence.output( 2, 50 )
	println()

	# problem 7
	println( "problem 7" )
	println( "alpha_* (4 decimals): ", Bisection.bisect( 4, 1, 2, Sequence.x_odd, div ) )
	println()

	# problem 8
	println( "problem 8" )
	println( "alpha^* (4 decimals): ", Bisection.bisect( 4, 1, 2, Sequence.x_even, div ) )
	println()

end

main()
