
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


// Implement something similar to the following line within the calling code for Graph to facilitate cleaner syntax in
// using Graph::get_adjacent().
// typedef std::priority_queue< std::pair<char,int>, std::vector< std::pair<char,int> >, PairComparator< char > > charPQ;

template< class VertexT=char >
class Graph {
  public:
    Graph(bool is_directed = true) { directed = is_directed; return;};
//  ~Graph(){}; // or destructor.
    bool add_vertex( VertexT V ); // Tested.
	int get_vertices( std::vector<VertexT>& vertices ); // Tested.
	int num_vertices();
    void make_empty();
    bool is_empty();
    bool is_full();
    bool add_edge( VertexT va, VertexT vb, int weight = 1 );
    bool edge_exists( VertexT va, VertexT vb ); // This is part of the assignment.
    void delete_edge( VertexT va, VertexT vb ); // This is part of the assignment.
    int  get_weight( VertexT va, VertexT vb );  // Better than edge_exists().
    void get_adjacent(
        VertexT v, std::priority_queue< std::pair<VertexT,int>, std::vector< std::pair<VertexT,int> >, PairComparator< VertexT > >& pq
    );
  private:
    int  index_is( VertexT v );
    VertexT vertex_is( int i );

	bool directed;
    std::vector< std::vector< int > > matrix;
    std::map< VertexT, int > v_to_i;   // Map Vertices to indices in the matrix.
    std::map< int, VertexT > i_to_v;   // Map indices in the matrix to Vertices.
};

#include "graph.cpp"