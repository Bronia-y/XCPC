#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define lc p << 1
#define rc p << 1 | 1

const int N = 1e5 + 10;

int n, m;
LL a[N];

struct {
	LL l, r, sum, add;
}tr[N << 2];

// 根据左右孩子的sum，刷新父亲的sum
void pushup(int p) {
	tr[p].sum = tr[lc].sum + tr[rc].sum;
}

// p 接受父亲的懒信息 k
void lazy(int p, LL k) {
	auto& [l, r, sum, add] = tr[p];
	sum += (r - l + 1) * k;
	add += k;
}

// 下放 p 的懒信息
void pushdown(int p) {
	lazy(lc, tr[p].add);
	lazy(rc, tr[p].add);

	tr[p].add = 0;
}

void build(int p, int l, int r) {
	tr[p] = {l, r, a[l], 0};
	if (l == r) return;

	int m = (l + r) >> 1;

	build(lc, l, m); build(rc, m + 1, r);
	pushup(p);
}

// 将[x, y] 区间内每个点染色
// 查找 p 区间染色点的sum
LL query(int p, int x, int y) {
	auto& [l, r, sum, add] = tr[p];

	if (x <= l && r <= y) return sum; // p 中所有点都被染色了

	int m = (l + r) >> 1;
	LL ret = 0;

	pushdown(p);
	if (x <= m) ret += query(lc, x, y); // 处理 p 左区间的染色点的sum
	if (y > m) ret += query(rc, x, y); // 处理 p 区间染色点的sum

	return ret;
}

// [x, y] += k
void modify(int p, int x, int y, LL k) {
	auto& [l, r, sum, add] = tr[p];
	if (x <= l && r <= y) lazy(p, k);
	else {
		int m = (l + r) >> 1;

		pushdown(p);
		if (x <= m) modify(lc, x, y, k);
		if (y > m) modify(rc, x, y, k);
		pushup(p);
	}
}

int main() {

	return 0;
}