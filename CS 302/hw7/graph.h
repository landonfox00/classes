
#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <vector>

#include "graph_node.h"
#include "graph_interface.h"
#include "not_found_exception.h"

// Key: node label, Data: GraphNode data, Edge: edge weight
template < class Key, class Data, class Edge >
class Graph : public GraphInterface< Key, Data, Edge >
{
public:
	Graph();
	Graph( const std::map< Key, GraphNode< Data > >& nodes );
	Graph( const std::map< Key, GraphNode< Data > >& nodes, const std::map< Key, std::map< Key, Edge > >& adj_list );
	Graph( const Graph< Key, Data, Edge >& graph );
	virtual ~Graph();

	int get_num_vertices() const;
	int get_num_edges() const;
	Edge get_edge_weight( Key start, Key end ) throw ( NotFoundException );
	GraphNode< Data > get_node( Key key );
	std::vector< Key > get_keys();

	bool IsAdjacent( Key start, Key end );

	bool Add( Key start, Key end, Edge edge_weight );
	bool Add( Key start, Data start_data, Key end, Data end_data, Edge edge_weight );
	bool Remove( Key start, Key end );

protected:
	std::map< Key, GraphNode< Data > > nodes_;
	std::map< Key, std::map< Key, Edge > > adj_list_;
	int vertex_count_;
	int edge_count_;
};

#include "graph.cc"

#endif
