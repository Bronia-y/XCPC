#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define endl '\n'
#define lc p << 1
#define rc p << 1 | 1

const int N = 5e5 + 10;

// 排序去重后的数组，辅助离散化
int disc[N], pos; 

int a[N], n;

// 记录当前容器中 每一个数据范围（区间）的元素个数
// [l, r] ： sum 表示位次在该区间的元素个数
struct {
	int l, r, sum;
}tr[N << 2];

// 找 x 离散化后的值
int id(int x, int l = 1, int r = pos) {
	while (l < r) {
		int m = l + r >> 1;
		if (disc[m] < x) l = m + 1;
		else r = m;
	}
	return l;
}

void pushup(int p) {
	tr[p].sum = tr[lc].sum + tr[rc].sum;
}

void build(int p, int l, int r) {
	tr[p] = {l, r};
	if (l == r) return;
	int m = l + r >> 1;
	build(lc, l, m); build(rc, m + 1, r);
}

void modify(int p, int x) {
	auto& [l, r, sum] = tr[p];
	if (l == r) ++sum;
	else {
		int m = l + r >> 1;
		if (x <= m) modify(lc, x);
		if (x > m) modify(rc, x);
		pushup(p);
	}
}

int query(int p, int x, int y) {
	auto& [l, r, sum] = tr[p];
	if (x <= l && r <= y) return sum;

	int m = l + r >> 1;
	int ret = 0;
	if (x <= m) ret = ret + query(lc, x, y);
	if (y > m) ret = ret + query(rc, x, y);
	return ret;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);

	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	// 离散化
	for (int i = 1; i <= n; ++i) disc[++pos] = a[i];
	sort(disc + 1, disc + n + 1);
	pos = unique(disc + 1, disc + n + 1) - (disc + 1);

	build(1, 1, pos); // 注意线段树维护【1, pos】

	LL ret = 0;
	for (int i = 1; i <= n; ++i) {
		int x = id(a[i]);
		ret = ret + query(1, x + 1, pos);
		modify(1, x);
	}
	cout << ret << endl;

	return 0;
}