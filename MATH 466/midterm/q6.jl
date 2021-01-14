
using LinearAlgebra

get_A() = 2 * rand( 9, 4 ).-1

function get_G()
	global get_A
	A = get_A()
	return A' * A
end

# assuming we are checking only diagonally dominant, not strictly diagonally dominant
function is_diagonally_dominant( G )
	m, n = size( G )
	for i in 1:m
		s = 0
		for j in 1:n
			if j != i
				s += abs( G[ i, j ] )
			end
		end
		if abs( G[ i, i ] ) < s
			return false
		end
	end
	return true
end

function get_proportion( k )
	global get_G, is_diagonally_dominant
	c = 0
	for i in 1:k
		if is_diagonally_dominant( get_G() )
			c += 1
		end
	end
	return c / k
end

# after running the function many times, ~30 of the 100 random matrices are diagonally
# dominant
println( "Diagonally dominant, k = 100 : ", get_proportion( 100   ) )
# similarly, when scalling to 1000, it would appear ~300 random matrices are diagonally
# dominant
# with small samples, it would appear to be fairly accurate (maybe error roughly < 0.05)
# and consistent to larger samples
println( "Diagonally dominant, k = 1000 : ", get_proportion( 1000 ) )
println( "Diagonally dominant, k = 10000 : ", get_proportion( 10000 ) )

function get_B()
	global get_G
	G = get_G()
	D = Diagonal( G )
	return -inv( D ) * ( G - D )
end

# determine if the infinity norm of the matrix G is less than 1
function is_jacobi_convergent( B )
	m, n = size( B )
	for i in 1:m
		s = 0
		for j in 1:n
			s += abs( B[ i, j ] )
		end
		if s > 1
			return false
		end
	end
	return true
end

function get_proportion_jacobi( k )
	global get_B, is_jacobi_convergent
	c = 0
	for i in 1:k
		if is_jacobi_convergent( get_B() )
			c += 1
		end
	end
	return c / k
end

# it would appear we get similar results as diagonally dominant matrices.
# perhaps a majority of matrices with convergent jacobi iterations come from strictly
# diagonally dominant matrices?
println( "Convergent Jacobi iteration, k = 10000 : ", get_proportion_jacobi( 10000 ) )
