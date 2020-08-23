
#ifndef GRAPH_INTERFACE_
#define GRAPH_INTERFACE_

#include "graph_node.h"
#include "not_found_exception.h"

template < class Key, class Data, class Edge >
class GraphInterface
{
public:
	virtual ~GraphInterface() { }

	virtual int get_num_vertices() const = 0;
	virtual int get_num_edges() const = 0;
	virtual Edge get_edge_weight( Key start, Key end ) throw ( NotFoundException ) = 0;

	virtual bool Add( Key start, Key end, Edge edge_weight ) = 0;
	virtual bool Remove( Key start, Key end ) = 0;
};

#endif
