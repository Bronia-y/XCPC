#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;
const int N = 2e5 + 10, INF = 0x3f3f3f3f;

vector<PII> e[N];
int f[N][25]; // f[x][i] : x 向上跳 2 ^ i 步的节点编号
int dep[N]; // dep[x] : x 所在的层数
int dist[N]; // 根到每一个节点的距离

void dfs(int x, int fa) {
	dep[x] = dep[fa] + 1;

	f[x][0] = fa;

	for (int i = 1; i <= 20; ++i)
		f[x][i] = f[f[x][i - 1]][i - 1];

	for (auto [y, w] : e[x]) {
		if (y == fa) continue;

        dist[y] = dist[x] + w;
		dfs(y, x);
	}
}

int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);

	// x 跳到与 y 同层
	for (int i = 20; i >= 0; --i)
		if (dep[f[x][i]] >= dep[y]) x = f[x][i];

	// y 是 x 的祖先，x 跳到 dep[y]时，刚好到 y
	if (x == y) return y;

	// x 与 y 同时向上跳，跳到 lca(x, y) 的下面
	for (int i = 20; i >= 0; --i) {
		if (f[x][i] != f[y][i]) 
			x = f[x][i], y = f[y][i];
	}
	return f[x][0];
}

int main() {
    int n, m; cin >> n >> m;
    
    for (int i = 1; i < n; ++i) {
        int x, y, w; cin >> x >> y >> w;
        e[x].emplace_back(y, w); e[y].emplace_back(x, w);
    }

    // 	谁是根都不重要
    dfs(1, 0);

    for (int i = 1; i <= m; ++i) {
        int x, y; cin >> x >> y;
        cout << dist[x] + dist[y] - 2 * dist[lca(x, y)] << endl;
    }
    
    return 0;
}