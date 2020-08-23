
#include <memory>
#include "Node.h"

template<class T>
Node<T>::Node()
{ }

template<class T>
Node<T>::Node( T item )
	:item( item )
{ }

template<class T>
Node<T>::Node( T item, std::shared_ptr< Node<T> > next )
	:item( item ), next( next )
{ }

template<class T>
void Node<T>::setItem( const T item )
{
	this->item = item;
}

template<class T>
void Node<T>::setNext( const std::shared_ptr< Node<T> > next )
{
	this->next = next;
}

template<class T>
T Node<T>::getItem() const
{
	return this->item;
}

template<class T>
std::shared_ptr< Node<T> > Node<T>::getNext() const
{
	return this->next;
}

template<class T>
bool Node<class T>::hasItem( const T item ) const
{
	return this->item == item;
}