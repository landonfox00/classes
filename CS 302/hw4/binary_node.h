
#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include <memory>

template < class T >
class BinaryNode
{
public:
	BinaryNode();
	BinaryNode( const T& data );
	BinaryNode( const T& data, std::shared_ptr< BinaryNode< T > > left, std::shared_ptr< BinaryNode< T > > right );
	BinaryNode( const BinaryNode< T >& node );

	bool IsLeaf() const;

	void set_data( const T& data );
	T get_data() const;

	void set_left( std::shared_ptr< BinaryNode< T > > left );
	std::shared_ptr< BinaryNode< T > > get_left() const;

	void set_right( std::shared_ptr< BinaryNode< T > > right );
	std::shared_ptr< BinaryNode< T > > get_right() const;

private:
	T data_;
	std::shared_ptr< BinaryNode< T > > left_;
	std::shared_ptr< BinaryNode< T > > right_;

};

#include "binary_node.cc"

#endif
