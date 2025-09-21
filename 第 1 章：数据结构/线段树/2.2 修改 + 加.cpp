#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define endl '\n'
#define lc p << 1
#define rc p << 1 | 1

const int N = 1e6 + 10; LL INF = 1e18;
LL a[N];
int n, m;

struct {
	int l, r;
	LL mx;
	bool st; LL x;
	LL add;
}tr[N << 2];

void pushup(int p) {
	tr[p].mx = max(tr[lc].mx, tr[rc].mx);
}

void build(int p, int l, int r) {
	tr[p] = {l, r, a[l]};
	if (l == r) return;
	int m = l + r >> 1;
	build(lc, l, m); build(rc, m + 1, r);
	pushup(p);
}

void lazy(int p, bool st, LL x, LL add) {
	if (st) tr[p].mx = x, tr[p].add = 0, tr[p].st = true, tr[p].x = x;
	tr[p].mx += add, tr[p].add += add;
}

void pushdown(int p) {
	auto& [l, r, mx, st, x, add] = tr[p];
	lazy(lc, st, x, add); lazy(rc, st, x, add);
	st = x = add = 0;
}

LL query(int p, int x, int y) {
	auto& [l, r, mx, st, k, add] = tr[p];
	if (x <= l && r <= y) return mx;

	pushdown(p);
	LL ret = -INF;
	int m = l + r >> 1;
	if (x <= m) ret = max(ret, query(lc, x, y));
	if (y > m) ret = max(ret, query(rc, x, y));
	return ret;
}

void modify(int p, int x, int y, bool st, LL k, LL add) {
	auto& [l, r, mx, _, __, ___] = tr[p];
	if (x <= l && r <= y) lazy(p, st, k, add);
	else {
		pushdown(p);
		int m = l + r >> 1;
		if (x <= m) modify(lc, x, y, st, k, add);
		if (y > m) modify(rc, x, y, st, k, add);
		pushup(p);
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	build(1, 1, n);

	while (m--) {
		int op, l, r; cin >> op >> l >> r;
		if (op == 1) {
			LL x; cin >> x;
			modify(1, l, r, true, x, 0);
		}
		else if (op == 2) {
			LL x; cin >> x;
			modify(1, l, r, false, 0, x);
		}
		else cout << query(1, l, r) << endl;
	}
	return 0;
}