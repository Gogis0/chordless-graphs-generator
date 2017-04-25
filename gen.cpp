#include <queue>
#include <set>
#define MAXN 20
#include "nauty26r7/nauty.h"

// generate graphs up to MAX_VERTICES
static const int MAX_VERTICES = 8;

typedef struct {
    graph g[MAXN * MAXM];
    int V;
} G;


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


int main() {
    int lab[MAXN], ptn[MAXN], orbits[MAXN];
    graph canong[MAXN*MAXM];
    statsblk stats;

    DEFAULTOPTIONS_GRAPH(options);

    std::queue<G> Q;
    Q.push(G());
    EMPTYGRAPH(Q.front().g, MAXM, MAXN);
    Q.front().V = 1;
    
    options.getcanon = TRUE;
    options.defaultptn = FALSE;
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
                if (orbits[lab[0]] == orbits[a.V - 1]) {
                    //printf("pushed %d %d\n", a.V, i);
                    Q.push(a);
                }
            }
        }
    }
}
