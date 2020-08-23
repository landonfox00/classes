
#include <memory>

#include "binary_node_tree.h"
#include "binary_tree_interface.h"
#include "binary_node.h"
#include "not_found_exception.h"
#include "precond_violated_exception.h"

// constructor
template < class T >
BinaryNodeTree< T >::BinaryNodeTree()
	: root_( nullptr ) { }

// constructor initializing root_
template < class T >
BinaryNodeTree< T >::BinaryNodeTree( const T& root_data )
	: root_( root_data ) { }

// constructor initializing root_ and its children
template < class T >
BinaryNodeTree< T >::BinaryNodeTree( const T& root_data, const std::shared_ptr< BinaryNodeTree< T > > left, const std::shared_ptr< BinaryNodeTree< T > > right )
	: root_( root_data, this->CopyTree( left ), this->CopyTree( right ) ) { }

// copy constructor
template < class T >
BinaryNodeTree< T >::BinaryNodeTree( const BinaryNodeTree< T >& tree )
	: root_( this->CopyTree( tree ) ) { }

// destructor
template < class T >
BinaryNodeTree< T >::~BinaryNodeTree()
{
	this->Clear();
}

// states if tree is empty
template < class T >
bool BinaryNodeTree< T >::IsEmpty() const
{
	return this->root_->IsLeaf();
}

// returns height of tree
template < class T >
int BinaryNodeTree< T >::get_height() const
{
	return this->get_height_helper( this->root_ );
}

// returns the number of nodes within tree
template < class T >
int BinaryNodeTree< T >::get_number_of_nodes() const
{
	return this->get_number_of_nodes_helper( this->root_ );
}

// returns data held within root node
template < class T >
T BinaryNodeTree< T >::get_root_data() const throw ( PrecondViolatedException )
{
	if ( this->IsEmpty() )
		throw PrecondViolatedException( "No root exists for this object" );
	return this->root_->get_data();
}

// redefines data held within root node
template < class T >
void BinaryNodeTree< T >::set_root_data( const T& data )
{
	if ( this->IsEmpty() )
		this->Add( data );
	else
		this->root_->set_data( data );
}

// adds entry to tree
template < class T >
bool BinaryNodeTree< T >::Add( const T& entry )
{
	std::shared_ptr< BinaryNode< T > > node = std::shared_ptr< BinaryNode< T > >( new BinaryNode< T >( entry ) );
	this->root_ = this->AddNode( this->root_, node );
	return true;
}

// removes target from tree
template < class T >
bool BinaryNodeTree< T >::Remove( const T& target )
{
	bool is_successful = false;
	this->root_ = this->RemoveValue( this->root_, target, is_successful );
	return is_successful;
}

// clears the entirety of tree
template < class T >
void BinaryNodeTree< T >::Clear()
{
	this->DestroyTree( this->root_ );
}

// returns given entry found in tree
template < class T >
T BinaryNodeTree< T >::get_entry( const T& entry ) const throw ( NotFoundException )
{
	bool is_successful = false;
	std::shared_ptr< BinaryNode< T > > found_entry = this->FindNode( this->root_, entry, is_successful );
	if ( !is_successful )
		throw NotFoundException( "Entry cannot be found within tree" );
	return found_entry->get_data();
}

// states if an entry is found within tree
template < class T >
bool BinaryNodeTree< T >::Contains( const T& entry ) const
{
	bool is_successful = false;
	this->FindNode( this->root_, entry, is_successful );
	return is_successful;
}

// traverses tree in preorder fashion
template < class T >
void BinaryNodeTree< T >::PreorderTraverse( void Visit( T& ) ) const
{
	this->Preorder( Visit, this->root_ );
}

// traverses tree in inorder fashion
template < class T >
void BinaryNodeTree< T >::InorderTraverse( void Visit( T& ) ) const
{
	this->Inorder( Visit, this->root_ );
}

// traverses tree in postorder fashion
template < class T >
void BinaryNodeTree< T >::PostorderTraverse( void Visit( T& ) ) const
{
	this->Postorder( Visit, this->root_ );
}

// assignment operator overload
template < class T >
BinaryNodeTree< T >& BinaryNodeTree< T >::operator=( const BinaryNodeTree< T >& tree )
{
	tree.set_data(  this->root_->get_data() );
	tree.set_left(  this->CopyTree( this->root_->get_left()  ) );
	tree.set_right( this->CopyTree( this->root_->get_right() ) );
}

// recursively obtains height of a given subtree
template < class T >
int BinaryNodeTree< T >::get_height_helper( std::shared_ptr< BinaryNode< T > > subtree ) const
{
	if ( subtree == nullptr || subtree->IsLeaf() )
		return 0;
	int left_height  = this->get_height_helper( subtree->get_left()  );
	int right_height = this->get_height_helper( subtree->get_right() );
	return ( left_height >= right_height ? left_height : right_height ) + 1;
}

// recursively obtains the number of nodes in a given subtree
template < class T >
int BinaryNodeTree< T >::get_number_of_nodes_helper( std::shared_ptr< BinaryNode< T > > subtree ) const
{
	if ( subtree == nullptr )
		return 0;
	if ( subtree->IsLeaf() )
		return 1;
	int left_node_count  = this->get_number_of_nodes_helper( subtree->get_left()  );
	int right_node_count = this->get_number_of_nodes_helper( subtree->get_right() );
	return left_node_count + right_node_count + 1;
}

// recursively adds a new node to the tree in a left/right fashion to keep tree balanced
template < class T >
std::shared_ptr< BinaryNode< T > > BinaryNodeTree< T >::AddNode( std::shared_ptr< BinaryNode< T > > subtree, std::shared_ptr< BinaryNode< T > > node )
{
	if ( subtree == nullptr )
		return node;
	std::shared_ptr< BinaryNode< T > > left  = subtree->get_left();
	std::shared_ptr< BinaryNode< T > > right = subtree->get_right();
	if ( this->get_height_helper( left ) > this->get_height_helper( right ) )
	{
		right = this->AddNode( right, node );
		subtree->set_right( right );
	}
	else
	{
		left = this->AddNode( left, node );
		subtree->set_left( left );
	}
	return subtree;
}

// removes the target value from the tree
template < class T >
std::shared_ptr< BinaryNode< T > > BinaryNodeTree< T >::RemoveValue( std::shared_ptr< BinaryNode< T > > subtree, const T target, bool& is_successful )
{
	if ( subtree != nullptr )
	{
		if ( subtree->get_data() == target )
		{
			subtree = this->RemoveNode( subtree );
			is_successful = true;
		}
		else
		{
			std::shared_ptr< BinaryNode< T > > left  = this->RemoveValue( subtree->get_left() , target, is_successful );
			subtree->set_left(  left  );
			std::shared_ptr< BinaryNode< T > > right = this->RemoveValue( subtree->get_right(), target, is_successful );
			subtree->set_right( right );
		}
	}
	return subtree;
}

// moves node down tree as a leaf then removes node from tree
template < class T >
std::shared_ptr< BinaryNode< T > > BinaryNodeTree< T >::RemoveNode( std::shared_ptr< BinaryNode< T > > node )
{
	if ( node->IsLeaf() )
		// nothing points to node, it will then be removed
		return node;
	std::shared_ptr< BinaryNode< T > > left  = node->get_left();
	std::shared_ptr< BinaryNode< T > > right = node->get_right();
	if ( left == nullptr )
	{	// swap children with node and right
		node->set_left( right->get_left() );
		node->set_right( right->get_right() );
		right->set_left( left );
		// call RemoveNode on newly placed 'node'
		right->set_right( this->RemoveNode( node ) );
		return right;
	}
	// swap children with node and right
	node->set_left( left->get_left() );
	node->set_right( left->get_right() );
	left->set_right( right );
	// call RemoveNode on newly placed 'node'
	left->set_left( this->RemoveNode( node ) );
	return left;
}

// recursively searches for target value
template < class T >
std::shared_ptr< BinaryNode< T > > BinaryNodeTree< T >::FindNode( std::shared_ptr< BinaryNode< T > > subtree, const T& target, bool& is_successful ) const
{
	if ( subtree->get_data() == target )
	{
		is_successful = true;
		return subtree;
	}
	std::shared_ptr< BinaryNode< T > > found_entry_left  = this->FindNode( subtree->get_left(),  target, is_successful );
	std::shared_ptr< BinaryNode< T > > found_entry_right = this->FindNode( subtree->get_right(), target, is_successful );
	return ( found_entry_left == nullptr ? found_entry_right : found_entry_left );
}

// copies the tree and returns a pointer to the root of the copy
template < class T >
std::shared_ptr< BinaryNode< T > > BinaryNodeTree< T >::CopyTree( const std::shared_ptr< BinaryNode< T > > subtree ) const
{
	std::shared_ptr< BinaryNode< T > > new_tree;
	if ( subtree != nullptr )
	{
		new_tree = std::shared_ptr< BinaryNode< T > >( subtree->get_data(), nullptr, nullptr );
		new_tree->set_left(  this->CopyTree( subtree->get_left()  ) );
		new_tree->set_right( this->CopyTree( subtree->get_right() ) );
	}
	return subtree;
}

// recursively deletes all nodes from the tree
template < class T >
void BinaryNodeTree< T >::DestroyTree( std::shared_ptr< BinaryNode< T > > subtree )
{
	if ( subtree != nullptr )
	{
		this->DestroyTree( subtree->get_left() );
		this->DestroyTree( subtree->get_right() );
		subtree.reset();
	}
}

// recursively traverses tree in preorder fashion calling Visit() for each node
template < class T >
void BinaryNodeTree< T >::Preorder( void Visit( T& ), std::shared_ptr< BinaryNode< T > > subtree ) const
{
	if ( subtree != nullptr )
	{
		T data = subtree->get_data();
		Visit( data );
		this->Preorder( Visit, subtree->get_left() );
		this->Preorder( Visit, subtree->get_right() );
	}
}

// recursively traverses tree in inorder fashion calling Visit() for each node
template < class T >
void BinaryNodeTree< T >::Inorder( void Visit( T& ), std::shared_ptr< BinaryNode< T > > subtree ) const
{
	if ( subtree != nullptr )
	{
		T data = subtree->get_data();
		this->Inorder( Visit, subtree->get_left() );
		Visit( data );
		this->Inorder( Visit, subtree->get_right() );
	}
}

// recursively traverses tree in postorder fashion calling Visit() for each node
template < class T >
void BinaryNodeTree< T >::Postorder( void Visit( T& ), std::shared_ptr< BinaryNode< T > > subtree ) const
{
	if ( subtree != nullptr )
	{
		T data = subtree->get_data();
		this->Postorder( Visit, subtree->get_left() );
		this->Postorder( Visit, subtree->get_right() );
		Visit( data );
	}
}
