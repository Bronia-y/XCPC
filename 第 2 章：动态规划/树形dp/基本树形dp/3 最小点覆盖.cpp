#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10, INF = 0x3f3f3f3f;
int n;
vector<int> e[N];

int f[N], g[N], h[N];

void dfs(int x, int p) {
    int mn = INF;
    for (auto y : e[x]) {
        if (y == p) continue;
        dfs(y, x);
        h[x] += min(f[y], g[y]);
        f[x] += min(f[y], min(g[y], h[y]));
        g[x] += min(f[y], g[y]);
        mn = min(f[y] - g[y], mn);
    }
    if (mn > 0) g[x] += mn;
}

int main() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        e[x].emplace_back(y); e[y].emplace_back(x);
    }
    for (int i = 1; i <= n; ++i) f[i] = 1;
    dfs(1, 1);
    cout << min(f[1], g[1]);

    return 0;
}