
#ifndef _Node_h
#define _Node_h

#include <memory>

template<class T>
class Node
{
private:
	T item;
	std::shared_ptr< Node<T> > next;

public:
	Node();
	Node( T item );
	Node( T item, std::shared_ptr< Node<T> > next );

	virtual void setItem( const T item ) = 0;
	virtual void setNext( const std::shared_ptr< Node<T> > next ) = 0;

	virtual T getItem() const = 0;
	virtual std::shared_ptr< Node<T> > getNext() const = 0;

	virtual bool hasItem( const T item ) const = 0;

};

#include "Node.cpp"
#endif