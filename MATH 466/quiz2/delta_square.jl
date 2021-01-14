

function delta( F, x_0, d2, n )
	x = big( x_0 )
	for i in 3:n
		t1 = x_0; t2 = F( t1 ); t3 = F( t2 )
		x = d2( t1, t2, t3 )
		println( n, " ", x )
	end
end