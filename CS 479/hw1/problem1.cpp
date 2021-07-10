
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "BayesianClassifier.h"
#include "FileInput.h"


int main()
{
	std::vector< std::vector< double > > inputs      = read_csv( "test1.csv" );
	std::vector< std::vector< double > > inputs_temp = read_csv( "test2.csv" );
	int input1_len = inputs.size();
	inputs.insert( inputs.end(), inputs_temp.begin(), inputs_temp.end() );

	std::vector< double > mu1{ 1, 1 };
	std::vector< double > mu2{ 4, 4 };
	std::vector< double > sigma1{ 1, 1 };
	std::vector< double > sigma2{ 1, 1 };
	Category cat1( 2,  mu1, sigma1, 0.3 );
	Category cat2( 2,  mu2, sigma2, 0.7 );
	UncorrelatedClassifier classifier( cat1, cat2 );

	int misclassified1 = 0;
	int misclassified2 = 0
	std::ofstream file( "output.csv" );
	for ( int i = 0; i < inputs.size(); i++ )
	{
		int cat = classifier.classify( inputs[ i ] );
		if ( i < inputs1_len && cat == 2 )
			misclassified1++;
		else if ( i >= inputs1_len && cat == 1 )
			misclassified2++;
		file      << "(" << inputs[ i ][ 0 ] << ", " << inputs[ i ][ 1 ] << "); category " << cat << std::endl;
		std::cout << "(" << inputs[ i ][ 0 ] << ", " << inputs[ i ][ 1 ] << "); category " << cat << std::endl;
	}
	file.close();
	std::cout << "Total misclassification rate : " << ( (double) ( misclassified1 + misclassified2 ) / inputs.size() ) << '%' << std::endl
			<< "Misclassification rate class 1 : " << ( (double) misclassified1 / inputs.size() ) << '%' << std::endl
			<< "Misclassification rate class 2 : " << ( (double) misclassified2 / inputs.size() ) << '%' << std::endl;

	return 0;
}
