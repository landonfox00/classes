
#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

template < class T >
class GraphNode
{
public:
	GraphNode();
	GraphNode( T data );
	GraphNode( const GraphNode< T >& graph_node );
	virtual ~GraphNode();

	void set_data( const T& data );

	T get_data() const;

private:
	T data_;
};

#include "graph_node.cc"

#endif
