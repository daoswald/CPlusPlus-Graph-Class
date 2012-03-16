
#include <vector>                   // vector, vector<>::iterator
#include <map>                      // map, map<>::iterator, pair
#include <queue>                    // priority_queue

#define GRAPH_H

template< typename FirstType, typename SecondType >
struct PairComparator {
	bool operator()( const std::pair<FirstType, SecondType>& p1, const std::pair<FirstType, SecondType>& p2 ) const 
    {  
		if( p1.second > p2.second ) 
			return true;
		else
			return false;
    }
};


// Implement something similar to the following line within the calling code for Graph to facilitate cleaner syntax in
// using Graph::get_adjacent().
// typedef std::priority_queue< std::pair<char,int>, std::vector< std::pair<char,int> >, PairComparator< char, int > > charPQ;


class Graph {
  public:
    Graph() :directed(true) {};
//  ~Graph(){}; // or destructor.
    bool add_vertex( char v ); // Tested.
	int get_vertices( std::vector<char>& vertices ); // Tested.
	int num_vertices();
    void make_empty();
    bool is_empty();
    bool is_full();
    bool add_edge( char va, char vb, int weight = 1 );
    bool edge_exists( char va, char vb ); // This is part of the assignment.
    void delete_edge( char va, char vb ); // This is part of the assignment.
    int  get_weight( char va, char vb );  // Better than edge_exists().
    void get_adjacent(
        char v, std::priority_queue< std::pair<char,int>, std::vector< std::pair<char,int> >, PairComparator< char, int > >& pq
    );
  private:
    int  index_is( char v );
    char vertex_is( int i );

	bool directed;
    std::vector< std::vector< int > > matrix;
    std::map< char, int > v_to_i;   // Map Vertices to indices in the matrix.
    std::map< int, char > i_to_v;   // Map indices in the matrix to Vertices.
};

