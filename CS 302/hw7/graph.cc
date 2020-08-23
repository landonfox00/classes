
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

#include "graph_node.h"
#include "graph_interface.h"
#include "graph.h"
#include "not_found_exception.h"

template < class Key, class Data, class Edge >
Graph< Key, Data, Edge >::Graph()
	: nodes_(), adj_list_(), vertex_count_( 0 ), edge_count_( 0 ) { }

template < class Key, class Data, class Edge >
Graph< Key, Data, Edge >::Graph( const std::map< Key, GraphNode< Data > >& nodes )
	: nodes_( nodes ), adj_list_(), vertex_count_( nodes.size() ), edge_count_( 0 ) { }

template < class Key, class Data, class Edge >
Graph< Key, Data, Edge >::Graph( const std::map< Key, GraphNode< Data > >& nodes, const std::map< Key, std::map< Key, Edge > >& adj_list )
	: nodes_( nodes ), adj_list_( adj_list ), vertex_count_( nodes.size() ), edge_count_( 0 )
{
	typename std::map< Key, std::map< Key, Edge > >::iterator end = this->adj_list_.end();
	for ( typename std::map< Key, std::map< Key, Edge > >::iterator it = this->adj_list_.begin(); it != end; ++it )
		this->edge_count_ += it->size();
}

template < class Key, class Data, class Edge >
Graph< Key, Data, Edge >::Graph( const Graph< Key, Data, Edge >& graph )
	: nodes_( graph.nodes_ ), adj_list_( graph.adj_list_ ), vertex_count_( graph.vertex_count_ ), edge_count_( graph.edge_count_ ) { }

template < class Key, class Data, class Edge >
Graph< Key, Data, Edge >::~Graph() { }

template < class Key, class Data, class Edge >
int Graph< Key, Data, Edge >::get_num_vertices() const
{
	return this->vertex_count_;
}

template < class Key, class Data, class Edge >
int Graph< Key, Data, Edge >::get_num_edges() const
{
	return this->edge_count_;
}

template < class Key, class Data, class Edge >
Edge Graph< Key, Data, Edge >::get_edge_weight( Key start, Key end ) throw ( NotFoundException )
{
	if ( this->IsAdjacent( start, end ) )
		return this->adj_list_[ start ][ end ];
	throw NotFoundException( "An edge connecting " + start + " and " + end + " does not exist" );
}

template < class Key, class Data, class Edge >
GraphNode< Data > Graph< Key, Data, Edge >::get_node( Key key )
{
	return this->nodes_[ key ];
}

template < class Key, class Data, class Edge >
std::vector< Key > Graph< Key, Data, Edge >::get_keys()
{
	std::vector< Key > keys;
	typename std::map< Key, GraphNode< Data > >::iterator end = this->nodes_.end();
	for ( typename std::map< Key, GraphNode< Data > >::iterator it = this->nodes_.begin(); it != end; ++it )
		keys.push_back( it->first );
	return keys;
}

template < class Key, class Data, class Edge >
bool Graph< Key, Data, Edge >::IsAdjacent( Key start, Key end )
{
	return this->adj_list_[ start ].count( end ) != 0;
}

template < class Key, class Data, class Edge >
bool Graph< Key, Data, Edge >::Add( Key start, Key end, Edge edge_weight )
{
	this->nodes_.insert( std::pair< Key, GraphNode< Data > >( start, GraphNode< Data >() ) );
	this->nodes_.insert( std::pair< Key, GraphNode< Data > >( end,   GraphNode< Data >() ) );
	this->vertex_count_ = this->nodes_.size();
	if ( !this->IsAdjacent( start, end ) )
		this->edge_count_++;
	this->adj_list_[ start ][ end ] = edge_weight;
	return true;
}

template < class Key, class Data, class Edge >
bool Graph< Key, Data, Edge >::Add( Key start, Data start_data, Key end, Data end_data, Edge edge_weight )
{
	this->nodes_.insert( std::pair< Key, GraphNode< Data > >( start, GraphNode< Data >( start_data ) ) );
	this->nodes_.insert( std::pair< Key, GraphNode< Data > >( end,   GraphNode< Data >( end_data ) ) );
	this->vertex_count_ = this->nodes_.size();
	if ( !this->IsAdjacent( start, end ) )
		this->edge_count_++;
	this->adj_list_[ start ][ end ] = edge_weight;
	return true;
}

template < class Key, class Data, class Edge >
bool Graph< Key, Data, Edge >::Remove( Key start, Key end )
{
	int size = this->adj_list_[ start ].size();
	this->adj_list_[ start ].erase( end );
	bool removed = this->adj_list_[ start ].size() < ( unsigned ) size;
	if ( removed )
		edge_count_--;
	return removed;
}
