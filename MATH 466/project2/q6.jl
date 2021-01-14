
using Plots

x_values = [ 1.3, 2.7 ]

l1( x ) = ( x - x_values[ 2 ] ) / ( x_values[ 1 ] - x_values[ 2 ] )
l2( x ) = ( x - x_values[ 1 ] ) / ( x_values[ 2 ] - x_values[ 1 ] )

eta1( x ) = l1( x )^2 * l2( x )
eta2( x ) = l1( x ) * l2( x )^2

g1( x ) = ( x_values[ 2 ] - x_values[ 1 ] ) * eta1( x )
g2( x ) = ( x_values[ 1 ] - x_values[ 2 ] ) * eta2( x )

h1( x ) = l1( x ) + ( g1( x ) + g2( x ) ) / ( x_values[ 2 ] - x_values[ 1 ] )
h2( x ) = l2( x ) + ( g1( x ) + g2( x ) ) / ( x_values[ 1 ] - x_values[ 2 ] )

f( x ) = exp( x ) - 13 / x

df( x ) = exp( x ) + 13 / x ^ 2

y = f.( x_values )
z = df.( x_values )

p( x ) = y[ 1 ] * h1( x ) + z[ 1 ] * g1( x ) + y[ 2 ] * h2( x ) + z[ 2 ] * g2( x )


# print( p( 2 ) )

xs=[0.5:0.1:4;];
yf=f.(xs);
yp=p.(xs);
pl = plot(xs,[yf yp],size=[400,300],
legend=:bottomright,label=["f" "p"] )
png( pl, "plot" )