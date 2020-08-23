
#include <stdexcept>
#include <memory>

#include "linked_list_node.h"
#include "linked_list.h"
#include "precond_violated_except.h"

template < class T >
LinkedList< T >::LinkedList()
	: head_( nullptr ), tail_( nullptr ), item_count_( 0 ) { }

// attempt to make recursive
template < class T >
LinkedList< T >::LinkedList( const LinkedList< T >& list ) throw ( std::logic_error )
	: head_( std::shared_ptr< LinkedListNode< T > >( new LinkedListNode( *list.head_ ) ) ), tail_( nullptr ), item_count_( list.item_count_ )
{
	std::shared_ptr< LinkedListNode< T > > curr_node = this->head_;
	std::shared_ptr< LinkedListNode< T > > new_node = curr_node->get_next();
	for ( int i = 1; i < this->item_count_; ++i )
	{
		curr_node->set_next( std::shared_ptr< LinkedListNode< T > >( new LinkedListNode< T >( new_node ) ) );
		curr_node = curr_node->get_next();
		new_node = curr_node->get_next();
	}
	this->tail_ = curr_node;
	// if new_node is not nullptr at this point, throw logic error, means list is larger than item count
	// use during testing
	if ( new_node != nullptr )
		throw std::logic_error( "Provided list is not the length described by item_count_" );
}

template < class T >
LinkedList< T >::~LinkedList()
{
	this->Clear();
}

template < class T >
bool LinkdeList< T >::IsEmpty() const
{
	return this->head_ == nullptr;
}

template < class T >
int LinkdeList< T >::get_length() const
{
	return this->item_count_;
}

template < class T >
LinkedListNode< T > LinkdeList< T >::get_node( int position ) const throw ( PrecondViolatedExcept )
{
	std::shared_ptr< LinkedListNode< T > > node = get_node_helper( this->head_, position, 0 );
	if ( node == nullptr )
		throw PrecondViolatedExcept( "Node at position " + position + " does not exist" );
	return *node;
}

template < class T >
std::shared_ptr< LinkedListNode< T > > LinkedList< T >::get_node_helper( std::shared_ptr< LinkedListNode< T > > node, int position, int curr_position ) const
{
	if ( curr_position == position || node == nullptr )
		return node;
	this->get_node_helper( node->get_next(), position, ++curr_position );
}

template < class T >
bool LinkdeList< T >::Remove( int position )
{
	if ( position == 0 )
		this->head_ = get_node_helper( this->head_, position, 0 )->get_next();
	else if ( position > 0 && position < this->item_count_ )
	{
		std::shared_ptr< LinkedListNode< T > > parent = get_node_helper( this->head_, position - 1, 0 );
		parent->set_next( parent->get_next()->get_next() );
	}
}

template < class T >
void LinkedList< T >::Clear()
{
	
}


LinkedListNode< T > Replace( int position, const T& new_entry ) throw ( PrecondViolatedExcept );
