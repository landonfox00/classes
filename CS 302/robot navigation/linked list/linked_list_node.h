
#ifndef LINKED_LIST_NODE
#define LINKED_LIST_NODE

#include <memory>

template < class T >
class LinkedListNode
{
public:
	LinkedListNode();
	LinkedListNode( T data );
	LinkedListNode( T data, std::shared_ptr< LinkedListNode< T > > next );
	LinkedListNode( const LinkedListNode< T >& node );
	
	virtual ~LinkedListNode();

	void set_data( T data );
	void set_next( std::shared_ptr< LinkedListNode< T > > next );

	T get_data() const;
	std::shared_ptr< LinkedListNode< T > > get_next() const;

private:
	T data_;
	std::shared_ptr< LinkedListNode< T > > next_; 
};

#include "linked_list_node.cc"

#endif
