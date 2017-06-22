## Graphs without chordless cycles of given lengths
## Grafy bez indukovanych cyklov danej dlzky

### find_cycles.cpp

Compile as `g++ -std=c++11 find_cycles.cpp`.

#### What it does:
The program takes a set of circle lengths *X* and an undirected graph *G* as an input and:

1. Determines whether it contains a chordless cycle of such a length that is in *X*.

2. If it doesn't (i.e. the first condition isn't fulfilled), determines whether *G* contains an edge
   *e* for which *G-e* fulfills condition 1. Such an edge we will call critical.

#### Input format:
The first line contains one positive integer *K*.
The next line contains *K* positive integers - the lengths of the chordless cycles to find.

On the next line there are two space separated integers *N* and *M*, *N* specifying the number of vertices of the graph *G* and *M* the number of edges.
*M* lines follow, each in a format "X Y" meaning that there is a undirected edge from vertex *X* to vertex *Y*. Vertices are numbered from *0* to *N-1*.

#### Output format:
One line containing one of the 3 possible output messages, specifically:

+ "G contains a chordless cycle of length in X"
+ "G contains a critical edge"
+ "G doesn't contain a critical edge"

### gen.cpp

This program requires [nauty](http://pallini.di.uniroma1.it/index.html). It has been built using the
version 26r7, byt newer versions will hopefully be compatible.

Compile as `g++ gen.cpp nauty26r7/nauty.a`.

#### What it does:
The program generates all (unlabeled) undirected graphs up to some reasonably small number of vertices defined in a
constant *MAX_VERTICES*. Optionally, it can generate graphs without chordless cycles of given
lengths. The program uses nauty representation of dense graphs as specified in nauty documentation.

#### Input format:
The first line contains one positive integer *N*.
On the next line there are *N* space separated integers representing the unwanted lengths of
chordless cycles of generated graphs.

#### Output format:
As for now, the only output is the number of graphs that have been generated. All generated graphs
are put to the *std::queue*, hence the output says "There are X graphs in the queue".
