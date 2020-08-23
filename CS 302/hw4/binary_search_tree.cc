
#include <memory>

#include "binary_search_tree.h"
#include "binary_tree_interface.h"
#include "binary_node.h"
#include "binary_node_tree.h"
#include "not_found_exception.h"
#include "precond_violated_exception.h"

// constructor
template < class T >
BinarySearchTree< T >::BinarySearchTree() : BinaryNodeTree< T >() { }

// constructor initializing root_
template < class T >
BinarySearchTree< T >::BinarySearchTree( const T& root_data ) : BinaryNodeTree< T >( root_data ) { }

// copy constructor
template < class T >
BinarySearchTree< T >::BinarySearchTree( const BinarySearchTree< T >& tree )
	: root_( this->CopyTree( tree ) ) { }

// destructor, calls parent BinaryNodeTree's destructor dismantling tree
template < class T >
BinarySearchTree< T >::~BinarySearchTree() { }

// assignment operator overload
template < class T >
BinarySearchTree< T >& BinarySearchTree< T >::operator=( const BinarySearchTree< T >& tree )
{
	tree.set_data(  this->root_->get_data() );
	tree.set_left(  this->CopyTree( this->root_->get_left()  ) );
	tree.set_right( this->CopyTree( this->root_->get_right() ) );
}

// places a given new node at its proper position in the tree
template < class T >
std::shared_ptr< BinaryNode< T > > BinarySearchTree< T >::AddNode( std::shared_ptr< BinaryNode< T > > subtree, std::shared_ptr< BinaryNode< T > > node )
{
	if ( subtree == nullptr )
		return node;
	if ( subtree->get_data() > node->get_data() )
		subtree->set_left( this->AddNode( subtree->get_left(), node ) );
	else
		subtree->set_right( this->AddNode( subtree->get_right(), node ) );
	return subtree;
}

// removes the given target value from the tree while maintaining a binary search tree
template < class T >
std::shared_ptr< BinaryNode< T > > BinarySearchTree< T >::RemoveValue( std::shared_ptr< BinaryNode< T > > subtree, const T target, bool& is_successful )
{
	if ( subtree == nullptr )
		// target was not found
		is_successful = false;
	else if ( subtree->get_data() == target )
	{	// target is root of a subtree
		subtree = this->RemoveNode( subtree );
		is_successful = true;
	}
	else if ( subtree->get_data() > target )
	{	// search left subtree
		std::shared_ptr< BinaryNode< T > > left = this->RemoveValue( subtree->get_left(), target, is_successful );
		subtree->set_left( left );
	}
	else
	{	// search right subtree
		std::shared_ptr< BinaryNode< T > > right = this->RemoveValue( subtree->get_right(), target, is_successful );
		subtree->set_right( right );
	}
	return subtree;
}

// removes a given node from the tree while maintaining a binary search tree
template < class T >
std::shared_ptr< BinaryNode< T > > BinarySearchTree< T >::RemoveNode( std::shared_ptr< BinaryNode< T > > node )
{
	if ( node->IsLeaf() )
		// no children
		return node;
	std::shared_ptr< BinaryNode< T > > left  = node->get_left();
	std::shared_ptr< BinaryNode< T > > right = node->get_right();
	bool is_left = left != nullptr, is_right = right != nullptr;
	if ( is_left && is_right )
	{	// two children
		T inorder_successor;
		std::shared_ptr< BinaryNode< T > > leftmost = this->RemoveLeftmostNode( node->get_right(), inorder_successor );
		node->set_right( leftmost );
		node->set_data( inorder_successor );
		return node;
	}
	// one child
	std::shared_ptr< BinaryNode< T > > child;
	if ( is_left )
		// left child
		child = node->get_left();
	else
		// right child
		child = node->get_right();
	return child;
}

// removes the leftmost node in the subtree of the node
template < class T >
std::shared_ptr< BinaryNode< T > > BinarySearchTree< T >::RemoveLeftmostNode( std::shared_ptr< BinaryNode< T > > subtree, T& inorder_successor )
{
	if ( subtree->get_left() == nullptr )
	{
		inorder_successor = subtree->get_data();
		return this->RemoveNode( subtree );
	}
	std::shared_ptr< BinaryNode< T > > leftmost = this->RemoveLeftmostNode( subtree->get_left(), inorder_successor );
	subtree->set_left( leftmost );
	return subtree;
}

// returns a pointer to the node containing the given value or nullptr if not found
template < class T >
std::shared_ptr< BinaryNode< T > > BinarySearchTree< T >::FindNode( std::shared_ptr< BinaryNode< T > > subtree, const T& target, bool& is_successful ) const
{
	if ( subtree == nullptr )
		// Not found
		return nullptr;
	if ( subtree->get_data() == target )
	{	// Found
		is_successful = true;
		return subtree;
	}
	if ( subtree->get_data() > target)
		// Search left subtree
		return this->FindNode( subtree->get_left(), target, is_successful );
	else
		// Search right subtree
		return this->FindNode( subtree->get_right(), target, is_successful );
}
