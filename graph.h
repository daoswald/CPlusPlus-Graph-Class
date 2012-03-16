
#include <vector>                   // vector, vector<>::iterator
#include <map>                      // map, map<>::iterator, pair
#include <queue>                    // priority_queue


// Some constants that will be useful:
const bool DIRECTED		= true;
const bool DIGRAPH		= true;
const bool UNDIRECTED	= false;
const bool NONDIRECTED	= false;
const bool NOT_DIRECTED = false;
const bool NON_DIRECTED = false;

const int  NON_EDGE     = 0;


// A comparator class for priority queues.
template< typename VertexT >
struct PairComparator {
	bool operator()( const std::pair<VertexT,int>& p1, const std::pair<VertexT, int>& p2 ) const 
    {  
		if( p1.second > p2.second ) 
			return true;
		else
			return false;
    }
};


// Implement something similar to the following typedef within the calling 
// code for Graph to facilitate cleaner syntax in using 
// Graph::get_adjacent().
// typedef std::priority_queue< std::pair< string, int >, 
//								std::vector< std::pair< string, int > >, 
//								PairComparator< string > 
// > charPQ;



// Our cool Graph class. ;)
template< class VertexT=char >
class Graph {
  public:
    Graph( bool is_directed = true ) { directed = is_directed; return; }
    ~Graph(){ return; }
    bool add_vertex( VertexT V ); // Tested.
	int  get_vertices( std::vector<VertexT>& vertices ); // Tested.
	int  num_vertices();
    void make_empty();
    bool is_empty();
    bool is_full();
    bool add_edge( VertexT va, VertexT vb, int weight = 1 );
    bool edge_exists( VertexT va, VertexT vb ); // Assignment 2.
    void delete_edge( VertexT va, VertexT vb ); // Assignment 2.
    int  get_weight ( VertexT va, VertexT vb ); // Better than edge_exists().
    void get_adjacent(
        VertexT v, 
		std::priority_queue< std::pair<VertexT,int>, 
			                 std::vector< std::pair<VertexT,int> 
		>, 
		PairComparator< VertexT > >& pq
    );
  private:
    int     index_is ( VertexT  v );
    VertexT vertex_is( unsigned i );

	bool directed;
    std::vector< std::vector< int > > matrix;	// Adjacency matrix.
    std::map< VertexT, int >          v_to_i;   // Map Vertices to indices.
    std::vector< VertexT >            i_to_v;	// xref indices to Vertices.
};

#include "graph.cpp"