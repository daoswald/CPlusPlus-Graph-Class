
#include "graph.h"

#include <string>
#include <iostream>
#include <vector>	// std::vector
#include <queue>	// std::priority_queue
#include <map>		// std::pair

using namespace std;

// This facilitates passing our own comparator function to the priority queue
// used by Graph::get_adjacent().
// While a typedef is never essential, it cleans up the syntax within the 
// program's main logic.  See 'graph.h' for details.
typedef std::priority_queue< 
			std::pair<string,int>, 
			std::vector< std::pair<string,int> >, 
			PairComparator< string > 
> string_intPQ;


int main()
{
    Graph<string> x(DIRECTED);
    x.add_vertex( "Porto" );
    x.add_vertex( "Salt Lake City" );
    x.add_vertex( "Manila" );
	vector<string> vertices;
	int num_vertices = x.get_vertices( vertices );
	cout << "Vertices: " << num_vertices << endl;
	for( vector<string>::iterator vit = vertices.begin(); vit != vertices.end(); ++vit )
		cout << "Vertex: " << *vit << endl;
	
	x.add_edge( "Porto", "Manila", 2 );
	cout << "Edge Porto-Salt Lake City: ";
	if( x.edge_exists( "Porto", "Salt Lake City" ) )
		cout << "exists.\n";
	else
		cout << "doesn't exist.\n";

	cout << "Edge Porto-Manila: ";
	if( x.edge_exists( "Porto", "Manila" ) )
		cout << "exists.\n";
	else
		cout << "doesn't exist.\n";
	cout << "Edge Manila-Porto: ";
	if( x.edge_exists( "Manila", "Porto" ) )
		cout << "exists.\n";
	else
		cout << "doesn't exist.\n";

	x.add_edge( "Porto", "Salt Lake City", 1 );

	cout << "All edges for 'Porto' are: " << endl;
	string_intPQ pq;
	x.get_adjacent( "Porto", pq );
	while( !pq.empty() )
	{
		pair<string,int> edge = pq.top();
		cout << "\t" << edge.first << " => " << edge.second << ".\n";
		pq.pop();
	}

	x.delete_edge( "Porto", "Manila" );
	cout << "Now edge Porto-Manila: ";
	if( x.edge_exists( "Porto", "Manila" ) )
		cout << "exists.\n";
	else
		cout << "doesn't exist.\n";
	
	x.make_empty();
	cout << "Remaining vertices: " << x.get_vertices( vertices ) << endl;


    return 0;
}
