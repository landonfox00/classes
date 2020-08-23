
#include <stdexcept>
#include <string>

#include "not_found_exception.h"

NotFoundException::NotFoundException( const std::string& message )
	: std::logic_error( "Not Found Exception: " + message ) { }
