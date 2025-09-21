#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define lc p << 1
#define rc p << 1 | 1

const int N = 1e5 + 10;

LL a[N];
int n, m;

struct {
	int l, r;
	LL sum, mx; // 区间最大值用于剪枝
}tr[N << 2];

void pushup(int p) {
	tr[p].sum = tr[lc].sum + tr[rc].sum;
	tr[p].mx = max(tr[lc].mx, tr[rc].mx);
}

void build(int p, int l, int r) {
	tr[p] = {l, r, a[l], a[l]};
	if (l == r) return;
	int m = l + r >> 1;
	build(lc, l, m); build(rc, m + 1, r);
	pushup(p);
}

void modify(int p, int x, int y) {
	auto& [l, r, sum, mx] = tr[p];
	if (mx == 1) return; // 该区间最大值是 1, 不必再开更号，撤
	if (l == r) sum = mx = sqrt(sum);
	else {
		int m = l + r >> 1;
		if (x <= m) modify(lc, x, y);
		if (y > m) modify(rc, x, y);
		pushup(p);
	}
}

LL query(int p, int x, int y) {
	auto& [l, r, sum, mx] = tr[p];
	if (x <= l && r <= y) return sum;

	LL ret = 0;
	int m = l + r >> 1;
	if (x <= m) ret += query(lc, x, y);
	if (y > m) ret += query(rc, x, y);
	return ret;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	build(1, 1, n);
	
	cin >> m;
	while (m--) {
		int k, l, r; cin >> k >> l >> r;
		if (l > r) swap(l, r);
		if (k) cout << query(1, l, r) << endl;
		else modify(1, l, r);
	}

	return 0;
}