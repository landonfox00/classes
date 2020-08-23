
#include <memory>

#include "binary_node.h"

template < class T >
BinaryNode< T >::BinaryNode() 
	: data_(), left_( nullptr ), right_( nullptr ) { }

template < class T >
BinaryNode< T >::BinaryNode( const T& data )
	: data_( data ), left_( nullptr ), right_( nullptr ) { }

template < class T >
BinaryNode< T >::BinaryNode( const T& data, std::shared_ptr< BinaryNode< T > > left, std::shared_ptr< BinaryNode< T > > right )
	: data_( data ), left_( left ), right_( right ) { }

template < class T >
BinaryNode< T >::BinaryNode( const BinaryNode< T >& node )
	: data_( node.get_data() ), left_( node.get_left() ), right_( node.get_right() ) {}

template < class T >
bool BinaryNode< T >::IsLeaf() const
{
	return ( this->left_ == nullptr ) && ( this->right_ == nullptr );
}

template < class T >
void BinaryNode< T >::set_data( const T& data )
{
	this->data_ = data;
}

template < class T >
T BinaryNode< T >::get_data() const
{
	return this->data_;
}

template < class T >
void BinaryNode< T >::set_left( std::shared_ptr< BinaryNode< T > > left )
{
	this->left_ = left;
}

template < class T >
std::shared_ptr< BinaryNode< T > > BinaryNode< T >::get_left() const
{
	return this->left_;
}

template < class T >
void BinaryNode< T >::set_right( std::shared_ptr< BinaryNode< T > > right )
{
	this->right_ = right;
}

template< class T >
std::shared_ptr< BinaryNode< T > > BinaryNode< T >::get_right() const
{
	return this->right_;
}
