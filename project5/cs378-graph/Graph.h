// ----------------------
// Fionnuala Gunter
// Zachary Tschirhart
// July 2012
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector
#include "boost/graph/exception.hpp" // not_a_dag

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int vertex_descriptor;
        typedef std::pair<vertex_descriptor, vertex_descriptor> edge_descriptor;

        typedef std::set<vertex_descriptor>::iterator vertex_iterator;
        typedef std::set<edge_descriptor>::iterator edge_iterator;

        typedef std::vector<vertex_descriptor>::const_iterator adjacency_iterator;

        typedef std::size_t vertices_size_type;
        typedef std::size_t edges_size_type;

    public:
        // --------
        // add_edge
        // --------

        /**
         * Adds edge (s,t) to the graph and returns the edge descriptor for the new edge.
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor s, vertex_descriptor t, Graph& graph) {
            edge_descriptor ed(s,t);
            bool b = graph.e.insert(ed).second;
            if (b) {
	        	graph.g[s].push_back(t);
	    	}    
	    	return std::make_pair(ed,b);}

        // ----------
        // add_vertex
        // ----------

        /**
         * Adds a vertex to the graph and returns the vertex descriptor for the new vertex.
         */
        friend vertex_descriptor add_vertex (Graph& graph) {
            graph.g.push_back(std::vector<vertex_descriptor>());
            vertex_descriptor v = graph.g.size() - 1;
	    	graph.v.insert(v);
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         * Returns an iterator-range providing access to the vertices adjacent to vertex s in the graph.
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor s, const Graph& graph) {
	        adjacency_iterator b = graph.g[s].begin();
            adjacency_iterator e = graph.g[s].end();
            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         * If and edge from vertex s to vertex t exists, return a pair containing one such edge and true.
         * If there are no edges between s and t, return a pair with an arbitrary edge descriptor and false.
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor s, vertex_descriptor t, const Graph& graph) {
            edge_descriptor ed(s,t);
            bool b;
	        std::set<edge_descriptor>::iterator p = graph.e.find(ed);
	        b = p != graph.e.end();
	        if (b) {
		        ed = *p;
	        }
            return std::make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
         * Returns an iterator-range providing access to the edge set of the graph.
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& graph) {
            edge_iterator b = graph.e.begin();
            edge_iterator e = graph.e.end();
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         * Returns the number of edges in the graph.
         */
        friend edges_size_type num_edges (const Graph& graph) {
            return graph.e.size();}

        // ------------
        // num_vertices
        // ------------

        /**
         * Returns the number of vertices in the graph.
         */
        friend vertices_size_type num_vertices (const Graph& graph) {
            return graph.g.size();}

        // ------
        // source
        // ------

        /**
         * Returns the source vertex of edge ed.
         */
        friend vertex_descriptor source (edge_descriptor ed, const Graph&) {
           return ed.first;}

        // ------
        // target
        // ------

        /**
         * Returns the target vertex of edge ed.
         */
        friend vertex_descriptor target (edge_descriptor ed, const Graph&) {
            return ed.second;}

        // ------
        // vertex
        // ------

        /**
         * Returns the nth vertex in the graph's vertex list.
         */
        friend vertex_descriptor vertex (vertices_size_type n, const Graph&) {
            return n;}

        // --------
        // vertices
        // --------

        /**
         * Returns an iterator-range providing access to the vertex set of the graph.
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& graph) {
            vertex_iterator b = graph.v.begin();
            vertex_iterator e = graph.v.end();
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        std::vector< std::vector<vertex_descriptor> > g; // adjacency list
	    std::set<vertex_descriptor> v; // set of vertices
	    std::set<edge_descriptor> e; // set of edges

        // -----
        // valid
        // -----

        /**
         * Returns true if the graph is valid.
         */
        bool valid () const {
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * Default constructor. Creates an empty graph with zero vertices and zero edges.
         */
        Graph () {
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

// -----
// color
// -----

// 0 = white
// 1 = gray
// 2 = black

/**
 * recursive helper function for has_cycle
 * Return true if a gray vertex is seen twice (a cycle was detected).
 */

template <typename T, typename G>
bool color(T u, std::vector<int>& colors, const G& graph) {
    typedef typename G::vertex_descriptor vertex_descriptor;
    typedef typename G::adjacency_iterator adjacency_iterator;
    
    std::pair<adjacency_iterator, adjacency_iterator> adjacencyIterators 
        = adjacent_vertices(u, graph);
    adjacency_iterator b = adjacencyIterators.first;
    adjacency_iterator e = adjacencyIterators.second;
    
    colors[u] = 1;
    
    while(b != e) {
        vertex_descriptor v = *b;
        if (colors[v] == 1) {
            return true;
        }
        if (colors[v] == 0) {
            if (color<T, G>(v, colors, graph)) {
                return true;
            }
        }
        ++b;
    }
    
    colors[u] = 2;
    return false;
} 

// ---------
// has_cycle
// ---------

/**
 * depth-first traversal
 * three colors
 * Return true if the graph has a cycle.
 */
template <typename G>
bool has_cycle (const G& graph) {
    typedef typename G::vertex_descriptor vertex_descriptor;
    typedef typename G::edge_descriptor edge_descriptor;
    typedef typename G::vertex_iterator vertex_iterator;
    
    std::pair<vertex_iterator, vertex_iterator> vertexIterators = vertices(graph);
    vertex_iterator b = vertexIterators.first;
    vertex_iterator e = vertexIterators.second;
    std::vector<int> colors(num_vertices(graph), 0);
    
    while (b != e) {
        vertex_descriptor u = *b;
        if (colors[u] != 2) {
            if (color<vertex_descriptor, G>(u, colors, graph)) {
                return true;
            }
        }
        ++b;
    }
    
    return false;}

// -----
// visit
// -----

/**
 * recursive helper function for topological_sort
 * Sorts descendents of v before v.
 */

template <typename T, typename OI>
void visit(T v, std::vector<bool>& visited, std::vector< std::vector<T> >& neighbors, OI& result){

    if(!visited[v]){
        visited[v] = 1;
        
        for(unsigned int i = 0; i < neighbors[v].size(); ++i){
            T u = neighbors[v][i];
            visit<T,OI>(u, visited, neighbors, result);
        }
        result.push_back(v);
    }
}

// ----------------
// topological_sort
// ----------------

/**
 * depth-first traversal
 * two colors
 * Returns a topological ordering of the vertices in the graph in reverse order.
 * @throws Boost's not_a_dag exception if !has_cycle()
 */
template <typename G, typename OI>
void topological_sort (const G& graph, OI x) {

    if (has_cycle<G>(graph)) {
        throw boost::not_a_dag();
    }

    typedef typename G::vertex_descriptor vertex_descriptor;
    typedef typename G::edge_descriptor edge_descriptor;
    typedef typename G::edge_iterator edge_iterator;
    typedef typename std::vector<vertex_descriptor>::iterator vector_iterator;
    
    std::vector< std::vector< vertex_descriptor > > k(num_vertices(graph));
    std::pair<edge_iterator, edge_iterator> edgeIterators = edges(graph);
    edge_iterator b = edgeIterators.first;
    edge_iterator e = edgeIterators.second;
    std::vector<bool> isASource(num_vertices(graph), 0);
    
    while(b != e){
        edge_descriptor edge = *b;
        vertex_descriptor s = source(edge, graph);
        vertex_descriptor t = target(edge, graph);
        isASource[s] = 1;
        
        k[t].push_back(s);
        ++b;
    }
    
    std::vector<bool> visited(num_vertices(graph), 0);
    std::vector<vertex_descriptor> result;
    result.reserve(num_vertices(graph));
    
    for(unsigned int i = 0; i < isASource.size(); ++i){
        if(!isASource[i]){
            visit<vertex_descriptor, std::vector<vertex_descriptor> >((vertex_descriptor)i, visited, k, result);
        }
    }
    reverse(result.begin(), result.end());
    std::copy(result.begin(), result.end(), x);
}


#endif // Graph_h
