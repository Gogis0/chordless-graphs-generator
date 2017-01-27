#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
using namespace std;

// max number of vertices
const int MAX_N = 35;

// output messages in one place, so changing them is easier
const string out_has_cycle = "G contains a chordless cycle of length in X";
const string out_has_critical = "G contains a critical edge";
const string out_is_ok = "G doesn't contain a critical edge";


set<int> find_chordless_cycles(bool adj[][MAX_N], int N) {
    set<int> cycles;

    //RL: generujeme vsetky mozne indukovane cykly. Nech C je akurat generovany cyklus
    for (int i = 0; i < N - 2; i++) { //RL: Nech i je najnizsi prvok C
        for (int j = i + 1; j < N - 1; j++) { //RL: Nech j je sused i v C s nizsou hodnotou
            if (!adj[i][j]) continue; // ak i a j nie su spojene
            vector < vector<int> > candidates;

            //RL: Nech k je sused i v C s vyssou hodnotou, tym kazdy cyklus vygenerujeme prave raz
            for (int k = j + 1; k < N; k++) { 
                if (!adj[i][k]) continue;
                if (adj[j][k]) { cycles.insert(3); continue; }
                vector<int> v = {j, i, k};
                candidates.push_back(v);
            }


            while (!candidates.empty()) {
                vector<int> v = candidates.back();
                candidates.pop_back();

                /* // pomocny vypis:
                for (auto x : v) cout << x << " ";
                    cout << endl;
                */
                int k = v.back();
                //RL: staci prechadzat vrcholy >i, pretoze i je najnizzsi prvok C.
                for (int m = i + 1; m < N; m++) { 
                    if (!adj[m][k]) continue; //RL: lahky test som dal pred tazsi
                    if (find(v.begin(), v.end(), m) != v.end()) continue;
                    bool is_chord = false;

                    for (int l = 1; l < (int)v.size() - 1; l++) {
                        if (adj[m][v[l]]) is_chord = true;
                    }
                    if (is_chord) continue;

                    if (adj[m][j]) cycles.insert(v.size() + 1);
                    else {
                        v.push_back(m);
                        candidates.push_back(v);
                    } 
                }
            }
        }
    }
    return cycles;
}

set<int> get_intersection(set<int> X, set<int> Y) {
    set<int> intersect;
    set_intersection(X.begin(), X.end(), Y.begin(), Y.end(), inserter(intersect, intersect.begin()));
    return intersect;
}

pair<int, int> try_delete_edge(bool adj[][MAX_N], int N, set<int> X) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (adj[i][j]) {
                adj[i][j] = adj[j][i] = false;
                if (!get_intersection(X, find_chordless_cycles(adj, N)).empty()) {
		    return {i, j};
                }
                adj[i][j] = adj[j][i] = true;
            }
        }
    }
    return {-1, -1};
}

int main() {
    int K; cin >> K;
    set<int> X;
    for (int i = 0; i < K; i++) {
        int x; cin >> x;
        X.insert(x);
    }

    int N, M; cin >> N >> M;
    bool adj[MAX_N][MAX_N];
    fill(adj[0], adj[0] + MAX_N*MAX_N, false);

    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        adj[x][y] = adj[y][x] = true;
    }

    set<int> found_cycles = find_chordless_cycles(adj, N);

    if (get_intersection(X, found_cycles).empty()) {
        auto res = try_delete_edge(adj, N, X);
	if (res.first == -1) cout << out_is_ok << endl;
	else cout << out_has_critical << endl;
    } else cout << out_has_cycle << endl;
}
