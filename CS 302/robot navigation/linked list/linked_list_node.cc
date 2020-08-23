
#include <memory>

#include "linked_list_node.h"

template < class T >
LinkedListNode< T >::LinkedListNode()
	: data_(), next_( nullptr ) { }

template < class T >
LinkedListNode< T >::LinkedListNode( T data )
	: data_( data ) next_( nullptr ) { }

template < class T >
LinkedListNode< T >::LinkedListNode( T data, std::shared_ptr< LinkedListNode< T > > next )
	: data_( data ), next_( next ) { }

template < class T >
LinkedListNode< T >::LinkedListNode( const LinkedListNode< T >& node )
	: data_( node.data_ ), next_( node.next_ ) { }

template < class T>
LinkedListNode< T >::~LinkedListNode() { }

template < class T >
void LinkedListNode< T >::set_data( T1 data_item )
{
	this->data_item_1_ = data_item;
}

template < class T >
void LinkedListNode< T >::set_next( std::shared_ptr< LinkedListNode< T > > next )
{
	this->next_ = next;
}

template < class T >
T1 LinkedListNode< T >::get_data() const
{
	return this->data_item_1_;
}

template < class T >
std::shared_ptr< LinkedListNode< T > > LinkedListNode< T >::get_next() const
{
	return this->next_;
}
