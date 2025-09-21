#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
int n;

int path[N], pos;
// 有解则一路向上返回
bool dfs(int p, int depth) {
	// 迭代加深 bfs 剪枝：搜索到 depth 则停止
	if (p == depth + 1) return path[p - 1] == n;

	for (int i = 1; i < p; ++i) {
		for (int j = i; j < p; ++j) {
			int x = path[i] + path[j];

			// 4个 都是可行性剪枝
			if (x <= path[p - 1]) continue; // 3. 单调递增
			if (x > n) break; // 最后为 n, 又单调递增 -> x <= n
			if (x + depth - p > n) break;
			if (x * (1 << (depth - p)) < n) continue;

			path[++pos] = x;
			if (dfs(p + 1, depth)) return true;
			--pos;
		}
	}

	return false;
}

void solve() {
	if (n == 1) {
		cout << 1 << endl;
		return;
	}

	path[++pos] = 1;
	for (int depth = 2; ; ++depth) {
		// 有解则停止搜索
		if (dfs(2, depth)) {
			for (int i = 1; i <= depth; ++i) {
				cout << path[i];
				if (i < depth) cout << ' ';
			}
			cout << endl;
			break; 
		}
	}

	// 清数据
	pos = 0;
}

int main() {
	while (cin >> n, n) solve();

	return 0;
}