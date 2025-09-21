#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int disc[N], pos; // 排序去重后的数组，辅助离散化
// x 是第 id(x) 大的（保证 x 必须存在）
int id(int x, int l = 1, int r = pos) {
	while (l < r) {
		int m = l + r >> 1;
		if (x > disc[m]) l = m + 1;
		else r = m;
	}
	return l;
}

int a[N], n;

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	// 离散化
	memcpy(disc, a, sizeof a); pos = n;
	sort(disc + 1, disc + n + 1);
	pos = unique(disc + 1, disc + n + 1) - (disc + 1);



	return 0;
}