
#include <stdexcept>                // runtime_error()
#include <vector>                   // vector, vector<>::iterator
#include <map>                      // map, pair

#include <iostream>					// cerr.

// Add vertices, one at a time.  Returns false if vertex already existed.
// Throws under the impossible condition of an attempt to add to same
// index twice.  
// Also throws if is_full() returns true, or if any memory allocation fails.
template<class VertexT>
bool Graph<VertexT>::add_vertex( VertexT v )
{
    using std::map;
    using std::vector;
    using std::pair;
    using std::runtime_error;

	// is_full() *should* catch out of memory before we attempt to allocate,
	// but we will also trap std::bad_alloc's later on just in case.
	if( is_full() )
		throw( runtime_error(
			"add_vertex(): No room for more vertices."
		) );  // This should be difficult but NOT impossible to reach.

    // Note: v_to_i.size() will return number of elements, which we can use
    // as the index number of the new element.

    // Add the vertex to our crossreference lookups.
	// First, the vertex to index crossref.
	pair< map< VertexT, int >::iterator,bool > v_to_i_ret;
	try
	{ 
	    v_to_i_ret = v_to_i.insert( pair< VertexT, int >( v, v_to_i.size() ) );
	}
	catch( std::bad_alloc& ba )
	{
		std::cerr << "Bad Allocation caught adding to map: " 
				  << ba.what() << std::endl;
		throw( runtime_error(
			"add_vertex(): Failed to allocate memory for new vertex."
		) );
	}

	if( !v_to_i_ret.second )
        return false; // The vertex already existed.
	
	// Next, the index to vertex crossref.
	try
	{
		i_to_v.push_back( v );
	}
	catch( std::bad_alloc& ba )
	{
		std::cerr << "Bad Allocation caught adding to index: " 
				  << ba.what() << std::endl;
		throw( runtime_error(
			"add_vertex(): Failed to allocate memory for new vertex."
		) );
	}

    // Add a column to each existing row of the matrix for this new vertex.
    vector<vector<int> >::iterator it;
    for( it=matrix.begin(); it < matrix.end(); it++ )
	{
		try
		{
	        it->push_back( NON_EDGE );
		}
		catch( std::bad_alloc& ba )
		{
			std::cerr << "Bad Allocation caught adding to matrix: " 
					  << ba.what() << std::endl;
			throw( runtime_error(
				"add_vertex(): Failed to allocate memory for new vertex."
			) );
		}
	}

    // Note: v_to_i.size() will now return the number of elements inclusive of
    // the new vertex, so we can use that as the number of columns for our
    // new row.

    // Add a new row to the matrix for this new vertex.
    vector<int> row( v_to_i.size(), NON_EDGE ); // Create a new row to insert
    matrix.push_back( row );

    return true;
}


// Passes by reference a vector containing all the vertex names.
// Returns a vertex count.
template<class VertexT>
int Graph<VertexT>::get_vertices( std::vector<VertexT>& vertices )
{
	using std::map;
	using std::pair;
	int size = num_vertices();
	vector<VertexT>::iterator vit;
	for( vit = i_to_v.begin(); vit != i_to_v.end(); vit++ )
	{
		vertices.push_back( *vit );
	}
	return size;
}

// Returns a vertex count.
template<class VertexT>
int Graph<VertexT>::num_vertices()
{
	using std::runtime_error;
	if( i_to_v.size() != v_to_i.size() || v_to_i.size() != matrix.size() )
		throw( runtime_error(
			"Graph components out of sync: Detected in num_vertices()"
		) ); // Should be impossible.  Just a sanity check.
	return i_to_v.size();
}

// Removes all vertices.
// Clears the matrix.
template<class VertexT>
void Graph<VertexT>::make_empty()
{
	using std::runtime_error;
    v_to_i.clear();
    i_to_v.clear();
    matrix.clear();
	if( ! v_to_i.empty() || ! i_to_v.empty() || ! matrix.empty() )
		throw( runtime_error(
			"make_empty(): One or more components of Graph failed to clear"
		) );  // Impossible, but never hurts to be careful.
    return;
}

// Returns true if the graph is empty.
template<class VertexT>
bool Graph<VertexT>::is_empty()
{
	using std::runtime_error;
	if( i_to_v.empty() != v_to_i.empty() || v_to_i.empty() != matrix.empty() )
		throw( runtime_error(
			"Graph components out of sync: detected in is_empty()"
		) ); // This should be impossible.  Just a sanity check.
    return matrix.empty(); // Returns true for empty, false otherwise.
}

// Check whether the Graph is full.  Because our graph is implemented with
// a vector matrix and maps, running out of room is synonymous with running
// out of heap space (memory).  We probably should just be handling that sort
// of situation via exceptions, since memory shortages are exceptional cases.
template<class VertexT>
bool Graph<VertexT>::is_full()
{
    // First, check to see if we can fit another vertex in our maps.
    // Also check whether our matrix can hold another row.  We subtract one
    // from the max_size to accommodate an extra column per existing row.
    if(
        v_to_i.size() >= v_to_i.max_size()    ||
        i_to_v.size() >= i_to_v.max_size()    ||
        matrix.size() >= matrix.max_size() - 1
    )
        return true;
    else
        // We should be ok.  Return false, indicating there's room for
        // another vertex.
        return false;
}


// Get the index of a vertex v.  Return -1 if not found.
template<class VertexT>
int Graph<VertexT>::index_is( VertexT v )
{
    using std::map;
    map<VertexT,int>::iterator idx_it;
    idx_it = v_to_i.find( v );
    if( idx_it == v_to_i.end() )
        return -1;  // Sentinal flag: Vertex doesn't exist!
    else
        return idx_it->second;
}

// Get the vertex for index i.  Throw if vertex not found.
template<class VertexT>
VertexT Graph<VertexT>::vertex_is( unsigned i )
{
    using std::map;
    using std::runtime_error;
	if( i < 0 || i > i_to_v.size() - 1 )
		throw( runtime_error(
			"vertex_is() called on an out of range index: No vertex by that index."
		) );
	else
		return i_to_v[i];
}


// Adds an edge.  Returns false under the condition that either vertex
// doesn't exist.  Will blindly modify an existing edge.
template<class VertexT>
bool Graph<VertexT>::add_edge( VertexT va, VertexT vb, int weight )
{
    int row = index_is( va );
    int col = index_is( vb );
    if( row < 0 || col < 0 )
        return false;
    else {
        matrix[row][col] = weight;
		// We implement non-directed as auto-two-way-direction.
		if( !directed ) matrix[col][row] = weight;
        return true;
    }
}


// Returns true if an edge exists.  False if edge doesn't exist, or
// also if one of the specified vertices doesn't exist.
template<class VertexT>
bool Graph<VertexT>::edge_exists( VertexT va, VertexT vb )
{
    int row = index_is( va );
    int col = index_is( vb );
    if( row >= 0 && col >= 0 && matrix[row][col] != NON_EDGE )
        return true;
    else
        return false;
}

// Deletes an edge by setting its position in matrix to zero.
// Fails silently if edge doesn't exist
// Throws if one or more of the vertices doesn't exist.
// While that should reflect a logic error, it's not necessarily
// a fatal issue.  Perhaps I could re-implement as a bool return.
template<class VertexT>
void Graph<VertexT>::delete_edge( VertexT va, VertexT vb )
{
	using std::runtime_error;
    int row = index_is( va );
    int col = index_is( vb );
	if( row < 0 || col < 0 )
		throw( runtime_error(
			"delete_edge(): Attempt to delete an edge with invalid vertex."
		) );
    if( row >= 0 && col >= 0 )
        matrix[row][col] = NON_EDGE;
		// non-directed implemented as automatic direct-back (2-way direction).
		if( !directed ) matrix[col][row] = NON_EDGE;
    return;
}


// Returns the weight of an edge.  Throws if a vertex doesn't exist.
// If an edge doesn't exist, returns NON_EDGE, which is defined as 0.
template<class VertexT>
int Graph<VertexT>::get_weight( VertexT va, VertexT vb )
{
	using std::runtime_error;
    int row = index_is( va );
    int col = index_is( vb );
    if( row < 0 || col < 0 )
        throw( runtime_error(
			"get_weight(): Can't get a weight of edge with invalid vertex."
        ) );
    else
        return matrix[row][col];
}


// Scan all the columns for the Vertex's row in the matrix.
// Any non-zero column is an edge.
template<class VertexT>
void Graph<VertexT>::get_adjacent(
    VertexT v, 
	std::priority_queue< std::pair<VertexT,int>, 
						 std::vector< std::pair<VertexT,int> >, 
						 PairComparator< VertexT > >& pq
)
{
	using std::runtime_error;
	using std::pair;
	int r_ix = index_is( v );
	if( r_ix < 0 )
		throw( runtime_error(
			"get_adjacent(): Invalid vertix."
		) );
	for( unsigned c_ix = 0; c_ix < matrix[r_ix].size(); c_ix++ )
		if( int weight = matrix[r_ix][c_ix] )
		{
			VertexT vb = vertex_is( c_ix );
			pq.push( pair<VertexT,int>( vb, weight ) );
		}
	return;
}
