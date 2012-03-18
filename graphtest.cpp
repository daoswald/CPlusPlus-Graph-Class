// David Oswald
// CSIT 832
// Assignment 2: Graphs.

// Menu/Prompt-driven test driver for Graph class.
// The graph class is template based so that the user may decide what type
// of object should be used as vertices.  This driver uses a string vertex.
// Edges have an integer weight.  Weights of 1 can be used to emulate a
// non-weighted graph if that is preferred.

// The Graph class uses an adjacency matrix stored as a vector of vectors.
// It is not necessary to know beforehand how many vertices will be stored.
// The user may keep adding them as long as memory permits.  With each new
// vertex, a new row and column are added to the matrix, as well as a new
// index/map to crossreference vertex names with matrix positions.

// The Graph class also allows the user to specify (via the constructor)
// whether the class should instantiate as a directed graph (default) or
// an undirected graph.  This driver instantiates one of each for
// comparison purposes.

// User will be prompted for input.  The first thing to do would be to
// type 'av', and follow the prompts to add a vertex.  Repeat that a few
// times.  Then 'ae' to add an edge.  ...repeat that a few times too.
// 'de' to delete an edge, if you wish.  'ee' to check edge existance.

// Many other options are also available.  Have fun.
//     -- Dave


#include "graph.h"

#include <string>
#include <iostream>
#include <vector>	// std::vector
#include <queue>	// std::priority_queue
#include <map>		// std::map, std::pair

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



// Display helper functions.
void output_intro();
void status_summary( Graph<string>& dg, Graph<string>& ug );
void display_adjacencies( Graph<string>& graph, string va );
void display_vertices( Graph<string>& graph );
void list_commands();



// Menu items (all functions beginning with option_XX)
// Setters.
void option_av( Graph<string>& dg, Graph<string>& ug ); // Add Vertex.
void option_ae( Graph<string>& dg, Graph<string>& ug ); // Add Edge.
void option_de( Graph<string>& dg, Graph<string>& ug ); // Delete Edge.
void option_me( Graph<string>& dg, Graph<string>& ug ); // Make graphs Empty.

// Getters.
void option_gv( Graph<string>& dg, Graph<string>& ug ); // Get list of Verts.
void option_gn( Graph<string>& dg, Graph<string>& ug ); // Get Num. of Verts.
void option_ee( Graph<string>& dg, Graph<string>& ug ); // Edge Exists
void option_gw( Graph<string>& dg, Graph<string>& ug ); // Get edge Weight.
void option_ga( Graph<string>& dg, Graph<string>& ug ); // Get Adjacencies.
void option_em( Graph<string>& dg, Graph<string>& ug ); // Is EMpty?
void option_fl( Graph<string>& dg, Graph<string>& ug ); // Is FulL?
void option_st( Graph<string>& dg, Graph<string>& ug ); // STatus summaryl

// Miscellaneous.
// void option_qq() {} // Quit test application 
// -- Implemented in-line, not as function.

void option_hh(); // Display this help.




// I don't think I like this "Enumeration hack", but it seemed
// ugly declaring fourteen constants.
enum command_option 
{ 
// Value:0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 ... Lucky day!
	av = 0, ae, de, me, gv, gn, ee, gw, ga, em, fl, st, qq, hh 
};

int prompt( std::map<string,int>& options );

int main()
{
	// Set up some option keys.
	// Enumerates as:          0     1     2     3     4     5     6     7     8     9    10    11    12    13
	string option_keys[] = { "av", "ae", "de", "me", "gv", "gn", "ee", "gw", "ga", "em", "fl", "st", "qq", "hh" };
	std::map<string,int> option_map;
	for(  size_t ix = 0;  ix < 14;  ++ix  )
		option_map[ option_keys[ix] ] = ix;

	output_intro();
	list_commands();

	cout << "- Instantiating directed graph, 'digraph', "
		 << "and undirected graph, 'udgraph'." << endl;

	Graph<string> digraph(DIRECTED);
	Graph<string> udgraph(UNDIRECTED);

	bool keep_going = true;

	while( keep_going )
	{
		int command = prompt( option_map );
		switch( command )
		{
		case qq:	// Quit.
			keep_going = false;
			cout << "\nThanks for playing.  Have a nice day!" 
				 << endl;
											break;
		case hh:	// Help (display options).
			option_hh();					break;
		case av:	// Add vertex.
			option_av( digraph, udgraph );	break;
		case ae:	// Add edge.
			option_ae( digraph, udgraph );	break;
		case de:	// Delete edge.
			option_de( digraph, udgraph );	break;
		case me:	// Make empty.
			option_me( digraph, udgraph );	break;
		case gv:	// Get Vertices (list)
			option_gv( digraph, udgraph );	break;
		case gn:	// Get Number of Vertices.
			option_gn( digraph, udgraph );	break;
		case ee:	// Edge exists?
			option_ee( digraph, udgraph );	break;
		case gw:	// Get (edge) Weight.
			option_gw( digraph, udgraph );	break;
		case ga:	// Get Adjacencies.
			option_ga( digraph, udgraph );	break;
		case em:	// Graph is EMpty?
			option_em( digraph, udgraph );	break;
		case fl:	// Graph is FulL?
			option_fl( digraph, udgraph );	break;
		case st:	// Status update.
			option_st( digraph, udgraph );	break;
		default:	// Should be unreachable.
			cout << "Unrecognized command.  This shouldn't happen!" << endl;
		}
	}
    return 0;
}


// Introduction to the driver program.
void output_intro()
{	
	cout << "----------------------------------------------------------"
		 << "---------------------"	   << endl;
	cout << "|   graphtest: Explore the implementation of a Graph class by "
		 << "David Oswald.   |"        << endl;
	cout << "----------------------------------------------------------"
		 << "---------------------"    << endl	<< endl;
	cout << "Two Graph objects will be instantiated: One directed, and "
		 << "one undirected graph."    << endl;
	cout << "You will be given options to manipulate and inspect the Graphs."
		 << endl  << endl;
	cout << "Actions will be applied to both Graphs.  "
		 << "Output will be generated to "
		 << endl;
	cout << "show how the action transformed each Graph." << endl << endl;
	cout << "The Graph objects expect 'string' vertices, and integer edges."
		 << endl << endl;
	return;
}


// Invoked whenever a status summary is needed.
void status_summary( Graph<string>& dg, Graph<string>& ug ) 
{ 
	int dg_v_num = dg.num_vertices();
	int ug_v_num = ug.num_vertices();
	cout << "- Number of vertices: (digraph=" 
		 << dg_v_num << "), (udgraph=" 
		 << ug_v_num << ")." << endl;
	if( dg_v_num || ug_v_num ) 
	{
		cout << "\t(digraph vertices: ";
		display_vertices( dg );
		cout << ")" << endl;
		cout << "\t(udgraph vertices: ";
		display_vertices( ug );
		cout << ")" << endl;
	}
	return; 
}


// display the list of commands that the user may invoke.
void list_commands()
{
	cout << "Options are:"																	 << endl
		 << "   Setters:   av = add vertex.        ae = add edge.         de = delete edge." << endl
	     << "              me = make graphs empty."                                          << endl
	     << "   Accessors: gv = get vertex list.   gn = get vertex count. ee = edge exists?" << endl
		 << "              gw = edge weight.       ga = list adjancies.   em = Graph empty?" << endl
		 << "              fl = Graph full?        st = status summary."                     << endl
		 << "   Misc:      qq = quit testing.      hh = display this help."                  << endl << endl;
	return;
}


// Simple prompt for user to select an option.
int prompt( std::map<string,int>& options )
{
	string option    = "";
	bool   do_prompt = true;

	while( do_prompt )
	{
		cout << "\nSelect an option (";
		for( 
			std::map<string,int>::iterator mit = options.begin(); 
			mit != options.end(); 
			++mit 
		)
		{
			string op_name = mit->first;
			if( op_name == "qq" || op_name == "hh" )
				continue;
			cout << op_name << ",";
		}
		cout << " qq=quit, hh=help): ";
		getline(cin, option);
		if( !options.count( option ) )
		{
			cout << "\n" << option 
				 << " is an invalid option.  Please choose again." 
				 << endl;
			continue;
		}
		do_prompt = false;
	}
	return options.find( option )->second;
}


// Setters.

// Prompt for a vertex name, and add it to the graphs.
void option_av( Graph<string>& dg, Graph<string>& ug ) 
{ 
	cout << "Enter a unique vertex (implemented as a string): ";
	string vertex = "";
	cin >> vertex;
	cin.ignore();
	try
	{
		if( dg.add_vertex(vertex) )
			cout << vertex << " added to directed graph."     << endl;
		else
			cout << vertex 
			     << " is already a member of directed graph." << endl;
	}
	catch( std::runtime_error& re )
	{
		cout << re.what() 
			 << ": Vertex not added to directed graph."       << endl;
		return;
	}
	try
	{
		if( ug.add_vertex(vertex) )
			cout << vertex << " added to undirected graph."   << endl;
		else
			cout << vertex 
				 << " is already a member of directed graph." << endl;
	}
	catch( std::runtime_error& re )
	{
		cout << re.what() 
			 << ": Vertex not added to undirected graph."     << endl;
		return;
	}
	status_summary( dg, ug );
	return;
}


// Prompt for an edge (described by two vertices) and add it to the graph.
void option_ae( Graph<string>& dg, Graph<string>& ug ) 
{ 
	cout << "Add an edge by entering the first vertex name: ";
	string va, vb;
	int weight = 1;
	getline( cin, va );
	cout << "Now enter the second vertex name: ";
	getline( cin, vb );
	cout << "Enter a non-zero positive integral weight: ";
	cin  >> weight;
	if( weight < 1 )
	{
		cout << "Invalid weight.  No edge added." << endl;
		return;
	}
	bool dg_added = true;
	bool ug_added = true;
	if( dg.add_edge( va, vb, weight ) )
		cout << "Edge (" 
			 << va << "," << vb 
			 << ") added to directed graph with "
		     << "weight of " << weight 
			 << "." << endl;
	else
	{
		cout << "Either vertex " 
			 << va << " or " << vb 
			 << " doesn't exist in the directed graph." 
			 << endl;
		dg_added = false;
	}
	if( ug.add_edge( va, vb, weight ) )
		cout << "Edge (" 
		     << va << "," << vb 
			 << ") added to undirected graph with weight of " 
			 << weight 
			 << "." << endl;
	else
	{
		cout << "Either vertex " 
			 << va << " or " << vb 
			 << " doesn't exist in the undirected graph." 
			 << endl;
		ug_added = false;
	}
	
	if( dg_added )
	{
		cout << "Directed graph adjacencies for " << va << ": ";
        display_adjacencies( dg, va );
	}

	if( ug_added )
	{
		cout << "Undirected graph adjacencies for " << va << ": ";
		display_adjacencies( ug, va );
	}
	cin.ignore();
	return;
} // Add edge.



// Prompt for an edge (described by two vertex names) and delete that edge.
void option_de( Graph<string>& dg, Graph<string>& ug ) 
{ 
	string va, vb;
	cout << "Delete an edge by entering the first vertex's name: ";
	getline( cin, va );
	cout << "Now enter the second vertex's name: ";
	getline( cin, vb );
	bool dg_success = true;
	bool ug_success = true;
	try
	{
		dg.delete_edge( va, vb );
	}
	catch( std::runtime_error& re )
	{
		cout << re.what() << "\nNothing deleted from directed graph.\n";
		dg_success = false;
	}
	try
	{
		ug.delete_edge( va, vb );
	}
	catch( std::runtime_error& re )
	{
		cout << re.what() << "\nNothing deleted from undirected graph.\n";
		ug_success = false;
	}
	if( dg_success ) 
	{
		cout << "Directed graph adjacencies for " 
			 << va << " are:" << endl;
		display_adjacencies( dg, va );
	}
	if( ug_success )
	{
		cout << "Undirected graph adjacencies for " 
			 << va << " are:" << endl;
		display_adjacencies( ug, va );
	}
	return;
} // Delete edge.



// Make the graphs empty.
void option_me( Graph<string>& dg, Graph<string>& ug ) { 
	cout << "Clearing directed graph." << endl;
	try
	{
		dg.make_empty();
	}
	catch( std::runtime_error& re )
	{
		cout << re.what() << "\nFailed to clear directed graph."   << endl;
	}
	cout << "Clearing undirected graph." << endl;
	try
	{
		ug.make_empty();
	}
	catch( std::runtime_error& re )
	{
		cout << re.what() << "\nFailed to clear undirected graph." << endl;
	}
	return;
} // Make [graphs] empty.


// Getters.


// Display the names of vertices in each graph.
void option_gv( Graph<string>& dg, Graph<string>& ug ) { 
	cout << "Directed graph vertices: "   << endl << "\t";
	display_vertices(dg);
	cout << endl;
	cout << "Undirected graph vertices: " << endl << "\t";
	display_vertices(ug);
	cout << endl;
	return;
}


// Display how many vertices each graph contains.
void option_gn( Graph<string>& dg, Graph<string>& ug ) 
{ 
	cout << "The directed graph contains "   << dg.num_vertices() 
		 << " vertices." << endl;
	cout << "The undirected graph contains " << ug.num_vertices() 
		 << " vertices." << endl;
	return;
}


// Prompt for an edge (described by two vertices) and display whether
// that edge exists.
void option_ee( Graph<string>& dg, Graph<string>& ug ) 
{ 
	string va, vb;
	cout << "Check if an edge exists by entering the first vertex: ";
	getline( cin, va );
	cout << "Now specify the second vertex: ";
	getline( cin, vb );
	cout << "Directed graph: edge (" 
		 << va << "," << vb 
		 << ") ";
	if( dg.edge_exists(va,vb) )
		cout << "exists."        << endl;
	else
		cout << "doesn't exist." << endl;
	cout << "Undirected graph: edge (" 
		 << va << "," << vb 
		 << ") ";
	if( ug.edge_exists(va,vb) )
		cout << "exists."        << endl;
	else
		cout << "doesn't exist." << endl;
	return;
}


// Prompt for an edge (pair of vertices) and display the
// weight for that edge.
void option_gw( Graph<string>& dg, Graph<string>& ug ) 
{ 
	string va, vb;
	cout << "Check an edge's weight by entering the first vertex: ";
	getline( cin, va );
	cout << "Now specify the second vertex: ";
	getline( cin, vb );
	cout << "Directed graph: edge (" 
		 << va << "," << vb 
		 << ") ";
	try
	{
		int weight = dg.get_weight(va,vb);
		cout << "has weight of " << weight << "." << endl;
	}
	catch( std::runtime_error& re )
	{
		cout << re.what() << endl 
			 << "One or more of the vertices doesn't exist in "
			 << "directed graph."
			 << endl;
	}
	cout << "Undirected graph: edge (" 
		 << va << "," << vb 
		 << ") ";
	try
	{
		int weight = ug.get_weight(va,vb);
		cout << "has weight of " << weight << "." << endl;
	}
	catch( std::runtime_error& re )
	{
		cout << re.what() << endl
			 << "One or more of the vertices doesn't exist in "
			 << "undirected graph."
			 << endl;
	}
	return;
}


// Prompt for a vertex and display an adjacency list for it.
void option_ga( Graph<string>& dg, Graph<string>& ug ) { 
	cout << "Enter vertex name to view adjacency list: ";
	string vertex;
	getline( cin, vertex );
	cout << "Directed graph adjacencies for "   << vertex << ": ";
	display_adjacencies( dg, vertex );
	cout << endl;
	cout << "Undirected graph adjacencies for " << vertex << ": ";
	display_adjacencies( ug, vertex );
	cout << endl;
	return;
} // Get adjacency list.


// Display whether or not the graphs are empty.
void option_em( Graph<string>& dg, Graph<string>& ug ) 
{ 
	cout << "Directed graph is ";
	if( dg.is_empty() )
		cout << "empty."     << endl;
	else
		cout << "not empty." << endl;
	cout << "Undirected graph is ";
	if( ug.is_empty() )
		cout << "empty."     << endl;
	else
		cout << "not empty." << endl;
	return;
}


// Display whether or not either graph is full.
// This should be difficult but not impossible to reach.
// I suspect there would be a lot of agony from swapfile
// churning before we ever saw this report full.
void option_fl( Graph<string>& dg, Graph<string>& ug ) 
{ 
	cout << "Directed graph is ";
	if( dg.is_full() )
		cout << "full."     << endl;
	else
		cout << "not full." << endl;
	cout << "Undirected graph is ";
	if( ug.is_full() )
		cout << "full."     << endl;
	else
		cout << "not full." << endl;
	return;
}


// Display a status summary.
void option_st( Graph<string>& dg, Graph<string>& ug ) { 
	status_summary( dg, ug );
	return;
}


// Miscellaneous.

// void option_qq() {} -- Quit test application. 
// -- Implemented inline, not as function.

void option_hh() 
{ 
	list_commands(); 
	return; 
} // Display this help.



// Displays a list of adjacencies for a given vertex.
// Adjacencies are wrapped in [] square brackets.
void display_adjacencies( Graph<string>& graph, string va ) 
{
	string_intPQ pq;
	try
	{
		graph.get_adjacent( va, pq );
		while( !pq.empty() )
		{
			pair<string,int> edge = pq.top();
			cout << " [" 
				 << edge.first 
				 << " => " 
				 << edge.second 
				 << "]";
			pq.pop();
		}
		cout << "." << endl;
	}
	catch( std::runtime_error& re )
	{
		cout << re.what();
	}
	return;
}


// Just displays a list of vertices with each element wrapped in [] brackets.
void display_vertices( Graph<string>& graph )
{
	std::vector<string> vertices;
	graph.get_vertices( vertices );
	for( 
		std::vector<string>::iterator it = vertices.begin(); 
		it != vertices.end(); 
		++it 
	)
		cout << "[" << *it << "] ";
	return;
}
