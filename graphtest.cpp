
#include "graph.h"

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

// This facilitates passing our own comparator function to the priority queue used by Graph::get_adjacent().
// While a typedef is never essential, it cleans up the syntax within the program's main logic.  See 'graph.h' for details.
typedef std::priority_queue< std::pair<char,int>, std::vector< std::pair<char,int> >, PairComparator< char, int > > char_intPQ;

int main()
{
    Graph x;
    x.add_vertex( 'A' );
    x.add_vertex( 'B' );
    x.add_vertex( 'C' );
	vector<char> vertices;
	int num_vertices = x.get_vertices( vertices );
	cout << "Vertices: " << num_vertices << endl;
	for( vector<char>::iterator vit = vertices.begin(); vit != vertices.end(); vit++ )
		cout << "Vertex: " << *vit << endl;
	
	x.add_edge( 'A', 'C', 2 );
	cout << "Edge A-B: ";
	if( x.edge_exists( 'A', 'B' ) )
		cout << "exists.\n";
	else
		cout << "doesn't exist.\n";
	cout << "Edge A-C: ";
	if( x.edge_exists( 'A', 'C' ) )
		cout << "exists.\n";
	else
		cout << "doesn't exist.\n";

	x.add_edge( 'A', 'B', 1 );

	cout << "All edges for 'A' are: " << endl;
	char_intPQ pq;
	x.get_adjacent( 'A', pq );
	while( !pq.empty() )
	{
		pair<char,int> edge = pq.top();
		cout << "\t" << edge.first << " => " << edge.second << ".\n";
		pq.pop();
	}

	x.delete_edge( 'A', 'C' );
	cout << "Now edge A-C: ";
	if( x.edge_exists( 'A', 'C' ) )
		cout << "exists.\n";
	else
		cout << "doesn't exist.\n";
	
	x.make_empty();
	cout << "Remaining vertices: " << x.get_vertices( vertices ) << endl;


    return 0;
}
