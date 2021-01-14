#   Find the interpolating polynomial p(x) passing through the points
#
#       (-1,4.1), (-0.1,1.5), (0.8,6.6), (1.7,-6.5)
#
#   and then evaluate p(0.54).

println("This is Problem 2A for Quiz 2.")

# Please fix the definitions of xs and ys

xgold=0.54
pgold=5.853135436671239

x = [-1, -0.1, 0.8, 1.7]
y = [4.1, 1.5, 6.6, -6.5]

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

function p( t )
    global x, y
    r = 0
    for j in 1:length( x )
        r += y[ j ] * l( j, t )
    end
    return r
end


r=p(xgold)
println("p($xgold)=",r)

if abs(p(xgold)-pgold)>1e-7
    println("Please try again.  Your answer is incorrect.")
else
    println("Congratulations!  Your answer is correct!")
end