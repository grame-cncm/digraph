# Digraph library [![Build Status](https://travis-ci.org/grame-cncm/digraph.svg?branch=master)](https://travis-ci.org/grame-cncm/digraph)

**Digraph** is a very simple, template-based directed graph library. It is not designed to be general, but to suit the needs of the Faust compiler.

It is made of two files:

- `digraph.hh` the digraph class
- `digraphop.hh` some operations on digraphs

## Building a digraph
A **digraph** is a directed graph. It is composed of a set of nodes `{n_1,n_2,...}` and a set of connections (i.e. arrows) between these nodes `{(n_i -d-> n_j),...}`.

For a connection `(n_i -d-> n_j)`, the node `n_i` is the source of the connection, the node `n_j` is the destination of the connections, and the integer `d` is the value of the connection. When the value is not specified its is by default 0.

The API to create a graph is very simple. You start by creating an empty graph:

	digraph<char> g;

Then you add nodes and connections to the graph:

	g.add('A','B').add('B','C',1).add('D')...

The method `add()` can be used to add individual nodes like in `add('D')` or connections `add('A','B')`. In this case, the involved nodes are automatically added to the graph. There is no need to add them individually.

By default the value of the connection is 0. To create a connection with a different value use: `add('A','B',3)`. If multiple connections between two nodes are created, only the connection with the smallest value is kept.

It is also possible to `add()` a whole graph with all its nodes and connections. For example if `g1` and `g2` are two graphs, then:

	g1.add(g2)

Will add all the nodes and connections of `g2` into `g1`. If multiple connections between two nodes are created, only the connection with the smallest value is kept.

Please note that the only way to modify a digraphs is by adding nodes and connections using the `add()` method.



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

### Partition
A partition of a digraph into strongly connected components can be obtained using the Tarjan class.

	Tarjan<N> t(mygraph);
	...t.partition()...

The Tarjan class has essentially two methods:

- `partition()` returns the partition of the graph into strongly connected components. The result is a set of set on nodes.  Each set of nodes represent a strongly connected component of the graph.
- `cycles()` returns the number of cycles of the graph.

### Number of cycles
The function `cycles(mygraph)` return the number of cycles of a graph. It uses internally `Tarjan`.

	cycles(digraph<N>) -> int


### Direct acyclic graph of graphes
The function `graph2dag(mygraph)` transfoms a graph into a direct acyclic graph (DAG):

 	graph2dag(digraph<N>) -> digraph<digraph<N>>

The nodes of the resulting DAG are themselves graphs representing the strongly connected components of the input graph.

### Parallelize

Provided the input graph is a DAG,  `parallelize(mygraph)` transforms the input graph into a sequence of parallel nodes

	parallelize(digraph<N>) -> vector<vector<N>>

### Serialize

Provided the input graph is a DAG, `serialize(mygraph)` transforms the input graph into a sequence of nodes

	serialize(digraph<N>) -> vector<N>


### Map nodes
Transforms the input graph by applying a function to each node. The connections are preserved.

	mapnodes(digraph<N>, f:N->M) -> digraph<M>


### Map connections
Transfoms the input graph by applying a filter function to each connection. If the function returns true, the connection is maintained, otherwise it
is removed.

	mapconnections(digraph<N>, f:(N,N,int)->bool) -> digraph<N>

### Cut high-value connections

Cuts all connections of the input graph of value >= d.

	cut(digraph<N>, d) -> digraph<N>

