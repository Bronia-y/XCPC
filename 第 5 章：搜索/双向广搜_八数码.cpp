#include <bits/stdc++.h>
using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

string S, T = "123804765";

// 0 -> S信息，1 -> T信息
queue<string> q[2];

// st[0] : S 当前可达
// st[1] : T 当前可达
unordered_set<string> st[2];

// 对 a 扩展一层, 是否有解
bool extend(int a) {
	int b = a ^ 1;
	int sz = q[a].size();

	for (int i = 1; i <= sz; ++i) {
		auto u = q[a].front(); q[a].pop();
		int pos = 0; // x 中 0 的位置
		while (u[pos] != '0') ++pos;

		// 解码
		int x = pos / 3, y = pos % 3;

		for (int j = 0; j < 4; ++j) {
			int mx = x + dx[j], my = y + dy[j];
			if (mx < 0 || mx > 2 || my < 0 || my > 2) continue;

			string v = u;
			swap(v[pos], v[3 * mx + my]); // 新pos : 3 * mx + my(编码)

			// 刷新 dist 和 q
			q[a].emplace(v);
			st[a].insert(v);

			// 有解，直接推出
			if (st[b].count(v)) return true;
		}
	}
	return false;
}

int bfs() {
	if (S == T) return 0;

	// 初始化
	q[0].emplace(S); q[1].emplace(T);
	st[0].insert(S); st[1].insert(T);

	int step = 0; // 扩展总次数

	// 起点走不到终点 或 终点退不到起点 -> 无解
	while (q[0].size() && q[1].size()) {
		++step;
		if (q[0].size() < q[1].size()) {
			if (extend(0)) return step;
		}
		else {
			if (extend(1)) return step;
		}
	}

	return -1;
}

int main() {
	cin >> S;
	int ret = bfs();
	cout << ret << endl;

	return 0;
}