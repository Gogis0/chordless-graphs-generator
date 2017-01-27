# rocnikovy-projekt
## Grafy bez indukovanych cyklov danej dlzky

Compile as `g++ -W -Wall -g -O2 -std=c++11 find_cycles.cpp`.

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
