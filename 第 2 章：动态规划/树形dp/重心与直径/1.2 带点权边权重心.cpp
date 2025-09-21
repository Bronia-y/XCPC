#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using PII = pair<int, int>;

const int N = 1e5 + 10, INF = 0x3f3f3f3f;

vector<PII> e[N];

LL n, m;

// f[i] : i 子树节点个数
// g[i] : 去除 i 后，最大子树节点个数
LL w[N], f[N], g[N];

// 刷新 f, g
LL dfs1(int x, int fa) {
	f[x] = w[x];

	for (auto [y, l] : e[x]) {
		if (y == fa) continue;

		LL k = dfs1(y, x);

		f[x] += k;
		g[x] = max(g[x], k);
	}

	g[x] = max(g[x], m - f[x]);

	return f[x];
}

LL dfs2(int x, int fa) {
	LL ret = 0;

	for (auto [y, l] : e[x]) {
		if (y == fa) continue;

		LL k = dfs2(y, x);

		ret += k + f[y] * l;
	}
	return ret;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> w[i];
		m += w[i];
	}

	for (int i = 1; i < n; ++i) {
		int x, y, l; 
		cin >> x >> y >> l;
		e[x].emplace_back(y, l); e[y].emplace_back(x, l);
	}

	dfs1(1, 0);

	LL mn = INF;
	for (int i = 1; i <= n; ++i) mn = min(mn, g[i]);

	int core;
	for (int i = 1; i <= n; ++i) 
		if (g[i] == mn) core = i;

	memset(f, 0, sizeof f);
	dfs1(core, 0);

	cout << dfs2(core, 0) << endl;

	return 0;
}