#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

/* maxN = 100000 */

int N;
vector<int> E[100005];

void ucitaj(){
    int M, u, v;
    cin >> N >> M;
    while (M--){
        cin >> u >> v;
        E[u].push_back(v);
    }
}

int B[100005], Deg[100005];

void toposort(){
    for (int u=1; u<=N; u++) Deg[u] = 0;

    for (int u=1; u<=N; u++){
        for (int v : E[u]){
            Deg[v]++;
        }
    }
    int l = 1, r = 0;
    for (int u=1; u<=N; u++) if (!Deg[u]){
        B[++r] = u;
        E[0].push_back(u);
    }
    while (l<=r){
        int u = B[l++];
        for (int v : E[u]) if (!--Deg[v]) B[++r] = v;
    }
    for (int u=0; u<=N; u++) Deg[u] = 0;
    for (int u=0; u<=N; u++){
        for (int v : E[u]){
            Deg[v]++;
        }
    }
}

void stampaj_label(int u){
    puts("");
    if (u) printf("L%d:", u);
}

void stampaj_naredbu(const char* nar, int x){
    printf("\t%s%d;\n", nar, x);
}

void blok(int u){
    size_t i;
    stampaj_label(u);
    if (u) {
        if (Deg[u] > 1){
            stampaj_naredbu("join j", u);
        }
        stampaj_naredbu("S", u);
    }
    if (E[u].size()){
        for (i=0; i < E[u].size() - 1; i++){
            stampaj_naredbu("fork L", E[u][i]);
        }
        stampaj_naredbu("goto L", E[u][i]);
    } else {
        stampaj_naredbu("goto END", 0);
    }
}

void forkjoin(){
    /* inicijalizuj jx */
    for (int u=1; u<=N; u++) if (Deg[u] > 1) printf("\tj%d = %d\n", u, Deg[u]);
    /* cepaj */
    blok(0);
    for (int i=1; i<=N; i++) blok(B[i]);
    printf("END0:\n");
}

int main(){
    ucitaj();
    toposort();
    forkjoin();
    return 0;
}
