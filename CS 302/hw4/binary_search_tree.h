
#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include <memory>

#include "binary_tree_interface.h"
#include "binary_node.h"
#include "binary_node_tree.h"
#include "not_found_exception.h"
#include "precond_violated_exception.h"

template < class T >
class BinarySearchTree : public BinaryNodeTree< T >
{
public:
	BinarySearchTree();
	BinarySearchTree( const T& root_data );
	BinarySearchTree( const BinarySearchTree< T >& tree );
	virtual ~BinarySearchTree();

	// all commmented lines are implemented via inheritance of BinaryNodeTree

	// bool IsEmpty() const;
	// int get_height() const;
	// int get_number_of_nodes() const;

	// T get_root_data() const throw ( PrecondViolatedExcept );
	// void set_root_data( const T& data );

	// bool Add( const T& entry );
	// bool Remove( const T& target );
	// void Clear();

	// T get_entry( const T& entry ) const throw ( NotFoundException );
	// bool Contains( const T& entry ) const;

	// void PreorderTraverse( void Visit( T& ) ) const;
	// void InorderTraverse( void Visit( T& ) ) const;
	// void PostorderTraverse( void Visit( T& ) ) const;

	BinarySearchTree< T >& operator=( const BinarySearchTree< T >& tree );

protected:
	std::shared_ptr< BinaryNode< T > > AddNode( std::shared_ptr< BinaryNode< T > > subtree, std::shared_ptr< BinaryNode< T > > node ) override;

	std::shared_ptr< BinaryNode< T > > RemoveValue( std::shared_ptr< BinaryNode< T > > subtree, const T target, bool& is_successful ) override;

	std::shared_ptr< BinaryNode< T > > RemoveNode( std::shared_ptr< BinaryNode< T > > node ) override;

	std::shared_ptr< BinaryNode< T > > RemoveLeftmostNode( std::shared_ptr< BinaryNode< T > > subtree, T& inorder_successor );

	std::shared_ptr< BinaryNode< T > > FindNode( std::shared_ptr< BinaryNode< T > > subtree, const T& target, bool& is_successful ) const override;

private:
	std::shared_ptr< BinaryNode< T > > root_;

};

#include "binary_search_tree.cc"

#endif
