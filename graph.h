// David Oswald
// CSIT 832
// Assignment 2: Graphs.


// Version: 0.02
// Version notes:
//    Changes from 0.01:
//        Const correctness in Graph class.
//        General code cleanup.


// graph.h.  Template class declarations for the Graph class.
// "#include"s the graph.cpp file at the end of this file.


#include <vector>                   // vector, vector<>::iterator
#include <map>                      // map, map<>::iterator, pair
#include <queue>                    // priority_queue


// Some constants that will be useful:
const bool DIRECTED     = true;
const bool DIGRAPH      = true;
const bool UNDIRECTED   = false;
const bool NONDIRECTED  = false;
const bool NOT_DIRECTED = false;
const bool NON_DIRECTED = false;

const int  NON_EDGE     = 0;


// A comparator class for priority queues.
template< typename VertexT >
struct PairComparator {
    bool operator()(
        const std::pair<VertexT,int>& p1,
        const std::pair<VertexT,int>& p2
    ) const
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
//                              std::vector< std::pair< string, int > >,
//                              PairComparator< string >
// > charPQ;



// Our cool Graph class. ;)
template< class VertexT=char >
class Graph {
  public:
    Graph( bool is_directed = true ) { directed = is_directed; return; }
    virtual ~Graph(){ return; }
    virtual bool add_vertex( VertexT V );
    virtual int  get_vertices( std::vector<VertexT>& vertices ) const;
    virtual int  num_vertices() const;
    virtual void make_empty();
    virtual bool is_empty()     const;
    virtual bool is_full ()     const;
    virtual bool add_edge   ( VertexT va, VertexT vb, int weight = 1 );
    virtual bool edge_exists( VertexT va, VertexT vb ) const; // Assignment 2.
    virtual void delete_edge( VertexT va, VertexT vb );       // Assignment 2.
    virtual int  get_weight ( VertexT va, VertexT vb ) const; // Even better.
    virtual void get_adjacent(
        VertexT v,
        std::priority_queue< std::pair<VertexT,int>,
                             std::vector< std::pair<VertexT,int>
        >,
        PairComparator< VertexT > >& pq
    ) const;
  private:
    virtual int     index_is ( VertexT  v ) const;
    virtual VertexT vertex_is( std::vector<int>::size_type i ) const;

    bool directed;
    std::vector< std::vector< int > >             matrix; // Adjacency matrix.
    std::map<VertexT,std::vector<int>::size_type> v_to_i; // Verts to idx's.
    std::vector< VertexT >                        i_to_v; // idx's to Verts.
};


#include "graph.cpp"
