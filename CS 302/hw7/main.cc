
#include <vector>
#include <algorithm>
#include <limits>
#include <fstream>

#include "graph.h"

void FindRoutes( Graph< std::string, int, int >& graph, std::string start, std::vector< std::string >& unvisited, std::vector< std::string >& visited, std::vector< std::vector< std::string > >& routes )
{
	visited.push_back( start );
	unvisited.erase( std::find( unvisited.begin(), unvisited.end(), start ) );
	for ( unsigned int i = 0; i < unvisited.size(); ++i )
	{
		if ( graph.IsAdjacent( start, unvisited[ i ] ) )
		{
			std::vector< std::string > visited_cp( visited );
			std::vector< std::string > unvisited_cp( unvisited );
			FindRoutes( graph, unvisited[ i ], unvisited_cp, visited_cp, routes );
		}
	}
	if ( visited.size() == ( unsigned ) graph.get_num_vertices() )
		routes.push_back( visited );
}

// GetAllRoutesFrom assumes that start_end node is reachable from all nodes
std::vector< std::vector< std::string > > GetAllRoutesFrom( Graph< std::string, int, int >& graph, std::string start_end )
{
	std::vector< std::vector< std::string > > routes;
	std::vector< std::string > unvisited = graph.get_keys();
	std::vector< std::string > visited;
	FindRoutes( graph, start_end, unvisited, visited, routes );
	for ( unsigned int i = 0; i < routes.size(); ++i )
		routes[ i ].push_back( start_end );
	return routes;
}

int GetCost( Graph< std::string, int, int >& graph, std::vector< std::string >& route )
{
	int cost = 0;
	for ( unsigned int i = 0; i < route.size() - 1; ++i )
		cost += graph.get_edge_weight( route[ i ], route[ i + 1 ] );
	return cost;
}

std::vector< std::vector< std::string > > MinRoutes( Graph< std::string, int, int >& graph, std::vector< std::vector< std::string > >& routes )
{
	int min_cost = std::numeric_limits< int >::max();
	std::vector< std::vector< std::string > > min_routes;
	for ( unsigned int i = 0; i < routes.size(); ++i )
	{
		int cost = GetCost( graph, routes[ i ] );
		if ( cost < min_cost )
		{
			min_cost = cost;
			min_routes.clear();
			min_routes.push_back( routes[ i ] );
		}
		else if ( cost == min_cost )
			min_routes.push_back( routes[ i ] );
	}
	return min_routes;
}

int main()
{
	// Reno -> SF: 218 miles
	// Reno -> SLC: 518 miles
	// Reno -> Seattle: 704 miles
	// Reno -> LV: 439 miles
	// SF -> Reno: 218 miles
	// SF -> Seattle: 806 miles
	// SF -> LV: 569 miles
	// SLC -> Reno: 518 miles
	// SLC -> Seattle: 840 miles
	// SLC -> LV: 421 miles
	// Seattle -> Reno: 705 miles
	// Seattle -> SF: 806 miles
	// Seattle -> SLC: 830 miles
	// Seattle -> LV: 1115 miles
	// LV -> Reno: 438 miles
	// LV -> SF: 570 miles
	// LV -> SLC: 412 miles
	// LV -> Seattle: 1125 miles

	Graph< std::string, int, int > graph;
	graph.Add( "Reno", "San Fransico", 218 );
	graph.Add( "Reno", "Salt Lake City", 518 );
	graph.Add( "Reno", "Seattle", 704 );
	graph.Add( "Reno", "Las Vegas", 439 );
	graph.Add( "San Fransico", "Reno", 218 );
	graph.Add( "San Fransico", "Seattle", 806 );
	graph.Add( "San Fransico", "Las Vegas", 569 );
	graph.Add( "Salt Lake City", "Reno", 518 );
	graph.Add( "Salt Lake City", "Seattle", 840 );
	graph.Add( "Salt Lake City", "Las Vegas", 421 );
	graph.Add( "Seattle", "Reno", 705 );
	graph.Add( "Seattle", "San Fransico", 806 );
	graph.Add( "Seattle", "Salt Lake City", 830 );
	graph.Add( "Seattle", "Las Vegas", 1115 );
	graph.Add( "Las Vegas", "Reno", 438 );
	graph.Add( "Las Vegas", "San Fransico", 570 );
	graph.Add( "Las Vegas", "Salt Lake City", 412 );
	graph.Add( "Las Vegas", "Seattle", 1125 );

	std::ofstream file;
	file.open( "routes.txt" );

	std::vector< std::vector< std::string > > routes = GetAllRoutesFrom( graph, "Reno" );
	for ( unsigned int i = 0; i < routes.size(); ++i )
	{
		file << "Route " << i + 1 << ") ";
		for ( unsigned int j = 0; j < routes[ i ].size() - 1; ++j )
			file << routes[ i ][ j ] << ", ";
		file << routes[ i ][ routes[ i ].size() - 1 ] << std::endl;
	}

	std::vector< std::vector< std::string > > min_routes = MinRoutes( graph, routes );
	file << std::endl << "Cheapest route(s) with cost: " << GetCost( graph, min_routes[ 0 ] ) << " miles" << std::endl;
	for ( unsigned int i = 0; i < min_routes.size(); ++i )
	{
		file << "Route " << i + 1 << ") ";
		for ( unsigned int j = 0; j < min_routes[ i ].size() - 1; ++j )
			file << min_routes[ i ][ j ] << ", ";
		file << min_routes[ i ][ min_routes[ i ].size() - 1 ] << std::endl;
	}
}
