#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define lc p << 1
#define rc p << 1 | 1

const int N = 1e5 + 10;
int n, q, MOD;
LL a[N];

struct {
	int l, r;
	LL sum, k1, b1;
}tr[N << 2];

void pushup(int p) {
	tr[p].sum = (tr[lc].sum + tr[rc].sum) % MOD;
}

void build(int p, int l, int r) {
	tr[p] = {l, r, a[l], 1};
	if (l == r) return;
	int m = (l + r) >> 1;
	build(lc, l, m); build(rc, m + 1, r);
	pushup(p);
}

// 对 p 子树造成 t = k * t + b
void lazy(int p, LL k2, LL b2) {
	auto& [l, r, sum, k1, b1] = tr[p];
	sum = (sum * k2 % MOD + b2 * (r - l + 1)) % MOD;
	b1 = (b1 * k2 % MOD + b2) % MOD; k1 = k1 * k2 % MOD;
}

void pushdown(int p) {
	auto& [l, r, sum, k1, b1] = tr[p];
	lazy(lc, k1, b1); lazy(rc, k1, b1);
	k1 = 1; b1 = 0;
}

LL query(int p, int x, int y) {
	auto& [l, r, sum, k1, b1] = tr[p];
	if (x <= l && r <= y) return sum;
	LL ret = 0;
	pushdown(p);
	int m = (l + r) >> 1;
	if (x <= m) ret = (ret + query(lc, x, y)) % MOD;
	if (y > m) ret = (ret + query(rc, x, y)) % MOD;
	return ret;
}

void modify(int p, int x, int y, LL k2, LL b2) {
	auto& [l, r, sum, k1, b1] = tr[p];
	if (x <= l && r <= y) lazy(p, k2, b2);
	else {
		pushdown(p);
 		int m = (l + r) >> 1;
 		if (x <= m) modify(lc, x, y, k2, b2);
 		if (y > m) modify(rc, x, y, k2, b2);
 		pushup(p);
	}
}

int main() {
	cin >> n >> q >> MOD;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	build(1, 1, n);
	while (q--) {
		int op, x, y; cin >> op >> x >> y;
		if (op == 3) cout << query(1, x, y) << endl;
		else {
			LL k; cin >> k;
			if (op == 1) modify(1, x, y, k, 0);
			else modify(1, x, y, 1, k);
		}
	}
	
	return 0;
}