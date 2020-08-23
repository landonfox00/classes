
#ifndef LIST_INTERFACE_
#define LIST_INTERFACE_

#include "linked_list_node.h"

template < class T >
class ListInterface
{
public:
	virtual ~ListInterface() { }

	virtual bool IsEmpty() const = 0;

	virtual int get_length() const = 0;

	virtual bool Insert( int new_position, const T& data ) = 0;
	virtual bool Append( const T& data ) = 0;
	virtual bool Remove( int position ) = 0;
	virtual void Clear() = 0;
	virtual LinkedListNode< T > Replace( int position, const T& data ) = 0;
};

#endif
