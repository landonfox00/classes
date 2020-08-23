
#include <stdexcept>
#include <string>

#include "precond_violated_exception.h"

PrecondViolatedException::PrecondViolatedException( const std::string& message )
	: std::logic_error( "Precondition Violated Exception: " + message ) { }
