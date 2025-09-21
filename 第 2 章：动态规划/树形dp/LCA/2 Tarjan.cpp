#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

const int N = 5e5 + 10;
vector<int> e[N];
int fa[N]; // 并查集
int st[N]; // 是否遍历过

// q[x] : x 有关查询的所有的另一半 y, 以及问题的编号id
vector<PII> q[N]; 
int ret[N];

int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void tarjan(int x) {
	st[x] = true;
	for (auto y : e[x]) {
		if (st[y]) continue;

		tarjan(y);
		fa[y] = x; // 回溯时合并，子树向根合并
	}

	for (auto [y, id] : q[x]) {
		if (st[y] == false) continue;
		ret[id] = find(y); // y 已经遍历，y 的根是 y 的代表元
	}
}

int main() {
	int n, m, s;
	cin >> n >> m >> s;

	for (int i = 1; i <= n; ++i) fa[i] = i;

	for (int i = 1; i < n; ++i) {
		int x, y; cin >> x >> y;
		e[x].emplace_back(y); e[y].emplace_back(x);
	}

	for (int i = 1; i <= m; ++i) {
		int x, y; cin >> x >> y;
		q[x].emplace_back(y, i); q[y].emplace_back(x, i);
	}

	tarjan(s);

	for (int i = 1; i <= m; ++i) cout << ret[i] << endl;

	return 0;
}