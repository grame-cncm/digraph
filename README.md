# Digraph library ![Build GH Status](https://github.com/grame-cncm/digraph/workflows/compile-test/badge.svg)

**Digraph** is a very simple, C++ 11 template-based, directed graph library. It is not designed to be general, but to suit the needs of the (next) Faust compiler.

It is made of five files:

- `arrow.hh` arrows between nodes
- `digraph.hh` directed graphs made of nodes and arrows
- `digraphop.hh` basic operations on directed graphs
- `schedule.hh` various scheduling strategies
- `stdprinting.hh` utility printing operators for pairs, vectors, maps, etc.


## Building a digraph
A **digraph** is a directed graph. It is composed of a set of nodes `{n_1,n_2,...}` and a set of connections (i.e. arrows) between these nodes `{(n_i -a-> n_j),...}`.

For a connection `(n_i -a-> n_j)`, the node `n_i` is the source of the connection, the node `n_j` is the destination of the connections, and `a` is the value of the connection. 

The API to create a graph is very simple. You start by creating an empty graph:

	digraph<char,int> g;

Then you add nodes and connections to the graph:

	g.add('A','B').add('B','C',1).add('D')...

The method `add()` can be used to add individual nodes like in `add('D')` or connections `add('A','B')`. In this case, the involved nodes are automatically added to the graph. There is no need to add them individually.

By default, the value of the connection is 0. To create a connection with a different value use: `add('A','B',3)`. If multiple connections between two nodes are created, only the connection with the smallest value is kept.

It is also possible to `add()` a whole graph with all its nodes and connections. For example if `g1` and `g2` are two graphs, then:

	g1.add(g2)

Will add all the nodes and connections of `g2` into `g1`. If multiple connections between two nodes are created, only the connection with the smallest value is kept.

Please note that the only way to modify a digraphs is by adding nodes and connections using the `add()` method. Digraphs are otherwise immutable, and all other transformation implies the creation of a new digraph.



## Accessing nodes and connections
To access the nodes of a graph, one uses the method `g.nodes()`. For example to iterate over the nodes:

	for (const auto& n : g.nodes()) {
		... do something with node n ...
	}

Once you have a node you can iterate over its connections. To access the connections of a node we use the method `g.connections(n)`:

	for (const auto& n : g.nodes()) {
    	for (const auto& c : g.connections(n)) {
	   		... c.first: destination node of the connection
			... c.second: value of the connection
	    }
	}

## Algorithms and Operations on digraphs
Please note that the following operations never modify the graphs used as arguments.

### Partition
A partition of a digraph into strongly connected components can be obtained using the Tarjan class, an implementation of [Robert Tarjan's algorithm](https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm)

	Tarjan<N> t(const digraph<N,A>&);
	...t.partition()...

The Tarjan class has essentially two methods:

#### Partition

The method `partition()` returns the partition of the graph into strongly connected components. 

	partition() -> set<set<N>>&

The result is a set of set on nodes.  Each set of nodes represents a strongly connected component of the graph.
  
#### Cycles
The method `cycles()` returns the number of cycles of the graph.

	cycles() -> int

### Number of cycles
The function `cycles(mygraph)` return the number of cycles of a graph. It uses internally `Tarjan`.

	cycles(const digraph<N,A>&) -> int


### Direct acyclic graph of graphes
The function `graph2dag(mygraph)` uses Tarjan to transform a graph into a direct acyclic graph (DAG):

 	graph2dag(const digraph<N,A>&) -> digraph<digraph<N,A>>

The nodes of the resulting DAG are themselves graphs representing the strongly connected components of the input graph.

### Parallelize

Provided the input graph is a DAG, the function `parallelize()` transforms the input graph into a sequence of parallel nodes

	parallelize(const digraph<N,A>&) -> vector<vector<N>>

### Serialize

Provided the input graph is a DAG, the function `serialize()` transforms the input graph into a vector of nodes

	serialize(const digraph<N,A>&) -> vector<N>


### Map nodes
The function `mapnodes()` creates a copy of the input graph in which each node is transformed by the function `f()`. Existing connections in the input graph are preserved in the resulting graph.

	mapnodes(const digraph<N,A>&, f:N->M) -> digraph<M>


### Map connections
The function `mapconnections()` creates a copy of the input graph in which only the connections that satisfy the predicate `f()` are kept. 

	mapconnections(const digraph<N,A>&, f:(N,N,int)->bool) -> digraph<N,A>

### Cut high-value connections

The function `cut()` creates a copy of the input graph in which all connections of value >= `d` are eliminated.

	cut(const digraph<N,A>&, d) -> digraph<N,A>

### Split graph

The function `splitgraph()` splits a graph `G` into two subgraphs `L` and `R` according to a predicate `left()`. The nodes satisfying the predicate are copied into `L`, the others into `R`. The connections are kept, unless they concern nodes that are not in the same subgraph.

	splitgraph(const digraph<N,A>& G, function<bool(const N&)> left, digraph<N,A>& L, digraph<N,A>& R)