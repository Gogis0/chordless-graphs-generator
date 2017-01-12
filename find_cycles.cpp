#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

const int MAX_N = 35;

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

pair<int, int> try_delete_edge(bool adj[][MAX_N], int N, set<int> X) {
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (adj[i][j]) {
                adj[i][j] = adj[j][i] = false;
                if (X != find_chordless_cycles(adj, N)) {
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
    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        adj[x][y] = adj[y][x] = true;
    }

    set<int> found_cycles = find_chordless_cycles(adj, N);

    if (X != find_chordless_cycles(adj, N)) {
        cout << "Graf obsahuje vsetky kruznice s dlzkami z mnoziny X" << endl;
        auto res = try_delete_edge(adj, N, X);
	if (res.first == -1) cout << "Graf neobsahuje hranu, ktorej odstranenim sa zmensi pocet indukovanych kruznic" << endl;
	else cout << "Odstranenim hrany [" << res.first << "," << res.second << "]" << " sa zmensi pocet indukovanych cyklov" << endl;
    } else cout << "Graf neobsahuje nejaku indukovanu kruznicu s dlzkou z mnoziny X" << endl;
}
