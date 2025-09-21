#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f;
int dp1[N], dp0[N], n;

vector<int> e[N];

void dfs(int u, int fa) {
    for (auto v : e[u]) {
        if (fa == v) continue;
        dfs(v, u);

        if (dp0[v] > 0) dp1[u] += dp0[v];

        int x = max(dp0[v], dp1[v]);
        if (x > 0) dp0[u] += x;
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> dp1[i];
    
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        e[v].emplace_back(u);
        e[u].emplace_back(v);
    }

    dfs(1, 1);

    cout << max(dp1[1], dp0[1]) << endl;
    
    return 0;
}