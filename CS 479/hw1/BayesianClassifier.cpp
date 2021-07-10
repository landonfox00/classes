
#include <math.h>
#include <vector>


struct Category
{
	unsigned int dim;
	std::vector< double > mu;
	double sigma;
	double prior;
	Category() {}
	Category( unsigned int dim, std::vector< double > mu, double sigma, double prior ) : dim( dim ), mu( mu ), sigma( sigma ), prior( prior ) {}
};


bool dichotomized_bayesian_classifier( std::vector< double > x, double ( *discrimiant )( double*, Category ), Category cat1, Category cat2 )
{
	return discrimiant( x, cat1 ) - discrimiant( x, cat2 ) > 0;
}


double uncorrelated_discrimiant( std::vector< double > x, Category cat )
{
	double norm2 = 0;
	for ( int i = 0; i < cat.dim; i++ )
		norm2 += pow( x[ i ] - cat.mu[ i ], 2 );
	return -0.5 * norm2 / pow( cat.sigma, 2 ) + log( cat.prior );
}
