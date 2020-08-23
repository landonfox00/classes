
#ifndef BINARY_NODE_INTERFACE_
#define BINARY_NODE_INTERFACE_

#include "not_found_exception.h"
#include "precond_violated_exception.h"

template < class T >
class BinaryTreeInterface
{
public:
	virtual ~BinaryTreeInterface() { }

	virtual bool IsEmpty() const = 0;
	virtual int get_height() const = 0;
	virtual int get_number_of_nodes() const = 0;

	virtual T get_root_data() const throw ( PrecondViolatedException ) = 0;
	virtual void set_root_data( const T& data ) = 0;

	virtual bool Add( const T& entry ) = 0;
	virtual bool Remove( const T& target ) = 0;
	virtual void Clear() = 0;

	virtual T get_entry( const T& entry ) const throw ( NotFoundException ) = 0;
	virtual bool Contains( const T& entry ) const = 0;

	virtual void PreorderTraverse( void Visit( T& ) ) const = 0;
	virtual void InorderTraverse( void Visit( T& ) ) const = 0;
	virtual void PostorderTraverse( void Visit( T& ) ) const = 0;

};

#endif
