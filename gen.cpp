#include <iostream>
#include <vector>
using namespace std;

// number of vertices
const int N = 8;

void edge_f(int mask, int vertex, bool val) {
    for (int k = 0; k < 32; k++) {
        if (mask & (1 << k) != 0) {
            adj[vertex][k] = adj[k][vertex] = val;
        }
    }
}

void add_edges(int mask, int vertex) {
    edge_f(mask, vertex, true);
}

void remove_edges(int mask, int vertex) {
    edge_f(mask, vertex, false);
}

void generate(int adj[][N], int K) {
    // generate all subsets of edges with one end in K
    vector<int> good_masks;

    for (int i = 1; i < N; i++) {
        for (int mask = 1; mask < (1 << i); i++) {
            add_edges(mask, i);
            // some logic
            // asi tu chcem volat nauty na otestovanie,
            // ci nie je novy graf izomorfny s nejakym predchadzajucim "dobrym" 

            // ak nie je izomorfny so ziadnym, pridam aktualnu masku do good_masks
            // a rekurzivne pridavam dalsi vrchol
            remove_edges(mask, i);
        }
    }
}

int main() {
}
