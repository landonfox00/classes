
#ifndef PRECOND_VIOLATED_EXCEPTION_
#define PRECOND_VIOLATED_EXCEPTION_

#include <stdexcept>
#include <string>

class PrecondViolatedException : public std::logic_error
{
public:
	PrecondViolatedException( const std::string& message = "" );

}; 

#include "precond_violated_exception.cc"

#endif
