
#ifndef LINKED_BINARY_LIST_H
#define LINKED_BINARY_LIST_H

#include <stdexcept>
#include <memory>

#include "linked_list_node.h"
#include "list_interface.h"
#include "precond_violated_except.h"

template < class T >
class LinkedList : public ListInterface< T >
{
public:
	LinkedList();
	LinkedList( const LinkedList< T >& list ) throw ( std::logic_error );

	virtual ~LinkedList();

	bool IsEmpty() const;

	int get_length() const;
	LinkedListNode< T > get_node( int position ) const throw ( PrecondViolatedExcept );

	bool Remove( int position );
	void Clear();
	LinkedListNode< T > Replace( int position, const T& new_entry ) throw ( PrecondViolatedExcept );

private:
	std::shared_ptr< LinkedListNode< T > > head_;
	std::shared_ptr< LinkedListNode< T > > tail_;
	int item_count_;

	std::shared_ptr< LinkedListNode< T > > get_node_helper( int position ) const;
};

#include "linked_list.cc"

#endif
