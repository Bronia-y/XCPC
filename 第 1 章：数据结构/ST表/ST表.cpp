#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

const int N = 1e5 + 10;

int a[N], n, m;
int mx[N][20]; // mx[i][j] : max[i, i + 2 ^ j)
int lg[N];

// 初始化 ST表
void init() {
	lg[0] = -1;
	for (int i = 1; i <= n; ++i) {
		lg[i] = lg[i >> 1] + 1;
		mx[i][0] = a[i];
	}

	// 用 短区间 更新 长区间，j从小到大
	for (int j = 1; j <= lg[n]; ++j)
		for (int i = 1; i + (1 << j) - 1 <= n; ++i)
			mx[i][j] = max(mx[i][j - 1], mx[i + (1 << j - 1)][j - 1]);
}

int query(int l, int r) {
	int k = lg[r - l + 1];
	return max(mx[l][k], mx[r - (1 << k) + 1][k]);
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	init();
	for (int i = 1; i <= m; ++i) {
		int l, r; cin >> l >> r;
		cout << query(l, r) << endl;
	}

	return 0;
}