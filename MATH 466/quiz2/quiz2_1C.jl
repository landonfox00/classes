#   Find 6 iterations of the secant method for x0=0 and x1=1
#   and the polynomial p(x)=5x^3+2x^2+6x-7

println("This is Problem 1C for Quiz 2.")

xn=[0.5384615384615384, 0.670672296200065,
    0.7114704015436424, 0.7063292309258846,
    0.706468534258185, 0.7064690734329935 ]

f( t ) = ( ( 5 * t + 2 ) * t + 6 ) * t - 7

function secant( x_0, x_1 )
    global f
    return x_1 - f( x_1 ) * ( x_1 - x_0 ) / ( f( x_1 ) - f( x_0 ) )
end

#   Please fix the definition of x0 and x1
x0=0.0
x1=1.0

wrong=6
for i=1:6
    global wrong,x0,x1, secant
    x2=secant(x0,x1);
    println("x_$(i+1) = $x2")
    if abs(x2-xn[i])<1e-7
        wrong-=1
    end
    x0=x1
    x1=x2
end

if wrong>0
    println("Please try again.  Your answer is incorrect.")
else
    println("Congratulations!  Your answer is correct!")
end