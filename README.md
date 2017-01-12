# rocnikovy-projekt
## Grafy bez indukovanych cyklov danej dlzky

Compile as `g++ -W -Wall -g -O2 -std=c++11 find_cycles.cpp`.

#### What it does:
The program takes a set of circle lengths *X* and a an undirected Graph *G* as an input and:
1. determines whether it contains chordless cycles of every length in *X* 
2. determines whether it contains such an edge *e* that the first conditon doesn't hold for *G-e* 

#### Input format:
The first line contains one positive integer *K*.
The next line contains *K* positive integers - the lengths of the chordless cycles to find.

On the next line there are two space separated integers *N* and *M*, *N* specifying the number of vertices of the graph *G* and *M* the number of edges.
*M* lines follow, each in a format "X Y" meaning that there is a undirected edge from vertex *X* to vertex *Y*. Vertices are numbered from *0* to *N-1*.

