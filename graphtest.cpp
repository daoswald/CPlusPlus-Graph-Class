
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


void output_intro();
void report_state( Graph<string>& dg, Graph<string>& ug );
void list_commands();

int main()
{
	output_intro();
	cout << "- Instantiating directed graph, 'digraph', "
		 << "and undirected graph, 'udgraph'." << endl;
    Graph<string> digraph(DIRECTED);
	Graph<string> udgraph(UNDIRECTED);

	cout << "Initial state:" << endl;
    digraph.add_vertex( "Porto" );
	udgraph.add_vertex( "Porto" );
    digraph.add_vertex( "Salt Lake City" );
	udgraph.add_vertex( "Salt Lake City" );
    digraph.add_vertex( "Manila" );
	udgraph.add_vertex( "Manila" );

	report_state( digraph, udgraph );
	list_commands();
	
	digraph.add_edge( "Porto", "Manila", 2 );
	cout << "Edge Porto-Salt Lake City: ";
	if( digraph.edge_exists( "Porto", "Salt Lake City" ) )
		cout << "exists.\n";
	else
		cout << "doesn't exist.\n";

	cout << "Edge Porto-Manila: ";
	if( digraph.edge_exists( "Porto", "Manila" ) )
		cout << "exists.\n";
	else
		cout << "doesn't exist.\n";
	cout << "Edge Manila-Porto: ";
	if( digraph.edge_exists( "Manila", "Porto" ) )
		cout << "exists.\n";
	else
		cout << "doesn't exist.\n";

	digraph.add_edge( "Porto", "Salt Lake City", 1 );

	cout << "All edges for 'Porto' are: " << endl;
	string_intPQ pq;
	digraph.get_adjacent( "Porto", pq );
	while( !pq.empty() )
	{
		pair<string,int> edge = pq.top();
		cout << "\t" << edge.first << " => " << edge.second << ".\n";
		pq.pop();
	}

	digraph.delete_edge( "Porto", "Manila" );
	cout << "Now edge Porto-Manila: ";
	if( digraph.edge_exists( "Porto", "Manila" ) )
		cout << "exists.\n";
	else
		cout << "doesn't exist.\n";
	
	digraph.make_empty();


    return 0;
}

void output_intro()
{
	cout << "graphtest: Explore the implementation of a Graph class by "
		 << "David Oswald." << endl;
	cout << "----------------------------------------------------------"
		 << "-------------"    << endl << endl;
	cout << "Two Graph objects will be instantiated: One digraph, and "
		 << "one undirected graph."    << endl;
	cout << "You will then be given options to facilitate manipulation "
		 << "and inspection "          << endl;
	cout << "of the Graph objects."   << endl << endl;
	cout << "Each action will be applied to both Graphs, and output will "
		 << "be generated to "         << endl;
	cout << "show how the action transformed each Graph." << endl << endl;
	cout << "The Graph class is characterized by a template-defined "
		 << "vertex type and an "      << endl;
	cout << "integer-based edge weighting scheme wherein a non-zero edge "
		 << "weight represents "       << endl
		 <<	"an edge, or path exists." << endl << endl;
	return;
}


void report_state( Graph<string>& dg, Graph<string>& ug ) 
{ 
	int dg_v_num = dg.num_vertices();
	int ug_v_num = ug.num_vertices();
	cout << "- Number of vertices: (digraph=" 
		 << dg_v_num << "), (udgraph=" 
		 << ug_v_num << ")." << endl;
	if( dg_v_num || ug_v_num ) {
		std::vector<string> dg_vertices, ug_vertices;
		dg.get_vertices( dg_vertices );
		ug.get_vertices( ug_vertices );
		cout << "\t(digraph vertices: ";
		for( std::vector<string>::iterator it = dg_vertices.begin(); it < dg_vertices.end(); ++it )
			cout << "[" << *it << "] ";
		cout << ")" << endl;
		cout << "\t(udgraph vertices: ";
		for( std::vector<string>::iterator it = ug_vertices.begin(); it < ug_vertices.end(); ++it )
			cout << "[" << *it << "] ";
		cout << ")" << endl;
	}
	return; 
}

void list_commands()
{
	cout << "\nOptions are:"                               << endl
		 << "\tManipulators:"                              << endl
		 << "\t\tav(name)      = add vertex."              << endl
		 << "\t\tae(name,name) = add edge."                << endl
		 << "\t\tde(name,name) = delete edge."             << endl  
		 << "\t\tme            = make graphs empty."       << endl
	     << "\tAccessors:"                                 << endl
		 << "\t\tgv            = get list of vertices."    << endl
		 << "\t\tgn            = get number of vertices."  << endl
		 << "\t\tee(name,name) = edge exists."             << endl
		 << "\t\tgw(name,name) = get edge weight."         << endl
		 << "\t\tga            = get adjacency list."      << endl
	     << "\t\tie            = is empty?"                << endl
		 << "\t\tif            = is_full?"                 << endl
	     << "\tMiscellanious:"                             << endl
		 << "\t\tqq            = quit test application."   << endl
		 << "\t\thh            = display this help."       << endl
		 << "\t\tst            = output a status summary." << endl << endl;
	return;
}