
#include "graph_node.h"

template < class T >
GraphNode< T >::GraphNode()
	: data_() { }

template < class T >
GraphNode< T >::GraphNode( T data )
	: data_( data ) { }

template < class T >
GraphNode< T >::GraphNode( const GraphNode< T >& graph_node )
	: data_( graph_node.data_ ) { }

template < class T >
GraphNode< T >::~GraphNode() { }

template < class T >
void GraphNode< T >::set_data( const T& data )
{
	this->data_ = data;
}

template < class T >
T GraphNode< T >::get_data() const
{
	return this->data_;
}
