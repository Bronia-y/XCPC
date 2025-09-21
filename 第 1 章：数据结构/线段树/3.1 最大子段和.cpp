#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define lc p << 1
#define rc p << 1 | 1

const int N = 5e5 + 10;

LL a[N], n, m;

struct node {
	int l, r;
	LL sum, 
	mx, // 最大子段和
	lmx, // 左端点开始最大子段和
	rmx; // 右端点开始的最大子段和
}tr[N << 2];

// p = l + r
// 用 l 和 r 的信息 -> p 的信息
void pushup(node& p, node& l, node& r) {
	p.mx = max(max(l.mx, r.mx), l.rmx + r.lmx);
	p.lmx = max(l.lmx, l.sum + r.lmx);
	p.rmx = max(r.rmx, r.sum + l.rmx);
	p.sum = l.sum + r.sum;
}

void build(int p, int l, int r) {
	tr[p] = {l, r, a[l], a[l], a[l], a[l]};
	if (l == r) return;
	int m = l + r >> 1;
	build(lc, l, m); build(rc, m + 1, r);
	pushup(tr[p], tr[lc], tr[rc]);
}

// a[x] = s
void modify(int p, int x, LL s) {
	auto& [l, r, sum, mx, lmx, rmx] = tr[p];
	if (l == r) sum = mx = lmx = rmx = s;
	else {
		int m = l + r >> 1;
		if (x <= m) modify(lc, x, s);
		if (x > m) modify(rc, x, s);
		pushup(tr[p], tr[lc], tr[rc]);
	}
}

// 求 p 中染色区间的 node 信息
node query(int p, int x, int y) {
	auto& [l, r, sum, mx, lmx, rmx] = tr[p];
	int m = l + r >> 1;
	if (x <= l && r <= y) return tr[p];
	else if (y <= m) return query(lc, x, y);
	else if (x > m) return query(rc, x, y);
	else {
		// ln : 左边染色区间的信息
		// rn : 右边染色区间的信息
		// ret : p 中染色区间的信息
		node ret, ln = query(lc, x, y), rn = query(rc, x, y);
		pushup(ret, ln, rn);
		return ret;
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) cin >> a[i];

	build(1, 1, n);

	while (m--) {
		int k, a, b; cin >> k >> a >> b;
		if (k == 1) {
			if (a > b) swap(a, b);
			cout << query(1, a, b).mx << endl;
		}
		else modify(1, a, b);
	}
	return 0;
}