Graph class implementation and driver.
David Oswald <daoswald@gmail.com>
3/17/12
CSIT832 Spring 2012.

Files:

graph.h       -- Template based header file for Graph class.
graph.cpp     -- Implementation file for template based Graph class.
graphtest.cpp -- Driver program to facilitate testing of Graph class.


I chose to implement my own Graph class.  It uses an adjacency matrix that is
built using std::vector<std::vector<int> >, so that it is unnecessary to know
ahead of time how many vertices will be added.  User may add as many as he
wants so long as memory holds out.

The Graph class is template based so that the class user may specify what
type of object a vertex should be.  My driver program instantiates using
'string's as vertices.

The class also encapsulates a std::map to map vertex names to indices, and
a std::vector to map indices to vertex names for crossreference purposes.

I implemented a fairly complete graph.  Just check the header to see what
member functions are available.  edge_exists() and delete_edge() are
implemented.  However, I permit the user to specify an integer edge weight,
so in addition to edge_exists(), I also implemented edge_weight() to get
the weight.

I implemented a get_adjacencies() function, and it returns a priority queue
of vertices that are adjacent to the specified vertex.  For each adjacency,
a weight is also returned.  I implemented a custom comparator in order that
the PQ always returns the lowest-weight element next, but it is possible for
the class user to specify his own comparator if a different criteria are
desirable.



The driver...

The driver starts off by offering some brief instructions.  Here's how to
get started:

At the prompt type 'av' and enter.  You will be prompted to add a vertex
name (a string).  Type 'av' again to enter another, and another.  Vertices
may be added at any time, and the matrix will just grow to accommodate them.

After adding a few vertices, you may type 'ae' at the prompt to add an edge.
You will then be prompted for the first vertex, and the second one, and
a weight.  If weight isn't interesting, just enter a 1.

At the main prompt you may always type 'hh' to get the list of options and
what they're for.  There are many options.  'ee' is for testing edge_exists().
'de' is for testing delete_edge().  There are others, so go ahead and explore.

I tried to cover every base with respect to recovering from user errors.  For
example, I throw exceptions if someone tries to add an edge for which no
vertex exists.  But I catch the exception and use it to display a warning
message before moving on.




I hope you like it.  I enjoyed implementing the Graph class a lot, though
the driver was a bit tedious.  I've used graphs before, but never
implemented one.  This was a great excuse to dive into a bunch of my books
again and read up.  THANKS!

Dave


Version: 0.02 -- Change log:
    -- Const correctness in Graph class
    -- Const iterators in display-only functions within driver program.
    -- General code cleanup (formatting, etc.)
