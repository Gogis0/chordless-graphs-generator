#include <queue>
#include <set>
#include <algorithm>
#include <vector>
#define MAXN 20
#include "nauty26r7/nauty.h"

// generate graphs up to MAX_VERTICES
static const int MAX_VERTICES = 8;
static const int MAX_CYCLE_LENGTH = 30;

typedef struct {
    graph g[MAXN * MAXM];
    int V;
} G;


bool is_edge(G &graph, int i, int j) {
    return ISELEMENT(GRAPHROW(graph.g, i, MAXM), j);
}


inline bool operator<(const G &A, const G &B) {
    if (A.V < B.V) return true;
    if (A.V > B.V) return false;
    for (int i = 0; i < MAXN*MAXM; i++) {
        unsigned long long ax = ((unsigned long long *) A.g)[i];
        unsigned long long bx = ((unsigned long long *) B.g)[i];
        if (ax < bx) return true;
        if (ax > bx) return false;
    }
    return false;
}


bool has_chordless_cycle(G graph, bool *lengths) {
    int N = graph.V;
    for (int i = 0; i < N - 2; i++) {
        for (int j = i + 1; j < N - 1; j++) {
            if (!is_edge(graph, i, j)) continue;
            std::vector< std::vector<int> > candidates;

            for (int k = j + 1; k < N; k++) {
                if (!is_edge(graph, i, k)) continue;
                if (is_edge(graph, j, k)) {
                    if (lengths[3]) return true;
                    continue;
                }

                std::vector<int> V = {j, i, k};
                candidates.push_back(V);
            }


            while (!candidates.empty()) {
                std::vector<int> V = candidates.back();
                candidates.pop_back();

                int k = V.back();
                for (int m = i + 1; m < N; m++) {
                    if (!is_edge(graph, m, k)) continue;
                    if (find(V.begin(), V.end(), m) != V.end()) continue;
                    bool is_chord = false;

                    for (int l = 1; l < (int)V.size() - 1; l++) {
                        if (is_edge(graph, m, V[l])) is_chord = true;
                    }
                    if (is_chord) continue;

                    if (is_edge(graph, m, j) && lengths[V.size() + 1]) return true;
                    else {
                        V.push_back(m);
                        candidates.push_back(V);
                    }
                }
            }
        }
    }
    return false;
}


int main() {
    // we generate small graphs, so we can afford representing the cycle lengths as this
    bool lengths[MAX_CYCLE_LENGTH];
    std::fill(lengths, lengths + MAX_CYCLE_LENGTH, false);
    int M; scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int length;
        scanf("%d", &length);
        lengths[length] = true;
    }

    int lab[MAXN], ptn[MAXN], orbits[MAXN];
    graph canong[MAXN*MAXM];
    statsblk stats;

    DEFAULTOPTIONS_GRAPH(options);

    std::queue<G> Q;
    Q.push(G());
    EMPTYGRAPH(Q.front().g, MAXM, MAXN);
    Q.front().V = 1;
    
    while (!Q.empty()) {
 
        G act = Q.front();
        if (act.V >= MAX_VERTICES) {
            printf("There are %lu graphs left in the queue\n", Q.size());
            break;
        }
        Q.pop();

        int vec[act.V];
        std::fill(vec, vec + act.V,  0);

        std::set<G> res[act.V+1];
        options.getcanon = TRUE;
        options.defaultptn = FALSE;
        int sum = 0;

        while (1) {
            int start = 0, end = act.V - 1;
            for (int i = 0; i < act.V; i++) {
                ptn[i] = 1;
                if (vec[i]) lab[start++] = i;
                else lab[end--] = i;
            }
            if (sum != 0) ptn[sum-1] = 0;
            ptn[act.V-1] = 0;

            densenauty(act.g, lab, ptn, orbits, &options, &stats, MAXM, act.V, canong);
            G a;
            a.V = act.V;
            std::copy(canong, canong + MAXN*MAXM, a.g);
            res[sum].insert(a);

            int j = 0;
            for (; j < act.V; j++) {
                if (vec[j] == 0) {
                    sum++;
                    vec[j] = 1;
                    for (int k = j - 1; k >= 0; k--) { vec[k] = 0; sum --; }
                    break;
                }
            }
            if (j == act.V) break;
        }

        options.getcanon = TRUE;
        options.defaultptn = TRUE;
        for (int i = 0; i < act.V + 1; i++) {
            for (auto it : res[i]) {
                G a = it;
                a.V++;
                ((unsigned long long *) a.g)[a.V - 1] = 0;
                for (int j = 0; j < i; j++) ADDONEEDGE(a.g, a.V-1, j, MAXM);

                densenauty(a.g, lab, ptn, orbits, &options, &stats, MAXM, a.V, canong);
                if (orbits[lab[0]] == orbits[a.V - 1] && !has_chordless_cycle(a, lengths)) {
                    //printf("pushed %d %d\n", a.V, i);
                    Q.push(a);
                }
            }
        }
    }
}
