#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f;
int f[N]; // 必选
int g[N]; // 必不选

vector<int> e[N];

void dfs(int x, int p) {
    for (auto y : e[x]) {
        if (y == p) continue;
        dfs(y, x);
        f[x] += min(f[y], g[y]);
        g[x] += f[y];
    }
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) f[i] = 1;

    for (int i = 1; i <= n; ++i) {
        int u; cin >> u;
        int k; cin >> k;
        while (k--) {
            int v; cin >> v;
            e[u].emplace_back(v); e[v].emplace_back(u);
        }
    }

    dfs(0, 0);
    cout << min(f[0], g[0]) << endl;
    
    return 0;
}