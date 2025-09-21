// 0 l r 把 [l,r] 区间内的所有数全变成 0；
// 1 l r 把 [l,r] 区间内的所有数全变成 1；
// 2 l r 把 [l,r] 区间内的所有数全部取反，也就是说把所有的 0 变成 1，把所有的 1 变成 0；
// 3 l r 询问 [l,r] 区间内总共有多少个 1；
// 4 l r 询问 [l,r] 区间内最多有多少个连续的 1。

// 修改考虑多个操作
// 查询考虑分治

#include <bits/stdc++.h>
using namespace std;

#define lc p << 1
#define rc p << 1 | 1

const int N = 1e5 + 10, INF = 0x3f3f3f3f;

int a[N], n, m;

struct node {
    int l, r;
    int s1, m1, l1, r1;
    int s0, m0, l0, r0;
    bool f1, f2, f3;
}tr[N << 2];

void pushup(node& p, node& l, node& r) {
    p.s1 = l.s1 + r.s1;
    p.s0 = l.s0 + r.s0;

    p.m1 = max(max(l.m1, r.m1), l.r1 + r.l1);
    p.m0 = max(max(l.m0, r.m0), l.r0 + r.l0);

    p.l1 = l.s0 ? l.l1 : l.l1 + r.l1;
    p.l0 = l.s1 ? l.l0 : l.l0 + r.l0;

    p.r1 = r.s0 ? r.r1 : r.r1 + l.r1;
    p.r0 = r.s1 ? r.r0 : r.r0 + l.r0;
}

void build(int p, int l, int r) {
    tr[p] = {l, r, 
        a[l], a[l], a[l], a[l], 
        a[l] ^ 1, a[l] ^ 1, a[l] ^ 1, a[l] ^ 1};
    
    if (l == r) return;
    int m = l + r >> 1;
    build(lc, l, m); build(rc, m + 1, r);
    pushup(tr[p], tr[lc], tr[rc]);
}

void lazy(int p, bool f1, bool f2, bool f3) {
    auto& [l, r, s1, m1, l1, r1, s0, m0, l0, r0, _, __, ___] = tr[p];
    if (f1) 
        s1 = m1 = l1 = r1 = 0,
        s0 = m0 = l0 = r0 = r - l + 1,
        tr[p].f1 = true, tr[p].f2 = tr[p].f3 = false;
    
    if (f2) 
        s1 = m1 = l1 = r1 = r - l + 1,
        s0 = m0 = l0 = r0 = 0,
        tr[p].f2 = true, tr[p].f1 = tr[p].f3 = false;

    if (f3)
        swap(s1, s0), swap(m1, m0), swap(l1, l0), swap(r1, r0),
        tr[p].f3 ^= 1;
}

void pushdown(int p) {
    auto& f1 = tr[p].f1, &f2 = tr[p].f2, &f3 = tr[p].f3;
    lazy(lc, f1, f2, f3); lazy(rc, f1, f2, f3);
    f1 = f2 = f3 = false;
}

void modify(int p, int x, int y, bool f1, bool f2, bool f3) {
    auto& l = tr[p].l, r = tr[p].r;
    if (x <= l && r <= y) lazy(p, f1, f2, f3);
    else {
        pushdown(p);
        int m = l + r >> 1;
        if (x <= m) modify(lc, x, y, f1, f2, f3);
        if (y > m) modify(rc, x, y, f1, f2, f3);
        pushup(tr[p], tr[lc], tr[rc]);
    }
}

node query(int p, int x, int y) {
    auto& l = tr[p].l, r = tr[p].r;
    if (x <= l && r <= y) return tr[p];
    else {
        pushdown(p);
        int m = l + r >> 1;

        if (y <= m) return query(lc, x, y);
        if (x > m) return query(rc, x, y);

        node ret, nl, nr;
        
        nl = query(lc, x, y), nr = query(rc, x, y);
        pushup(ret, nl, nr);
        return ret;
    }
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);
    
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        ++l, ++r;

        if (op == 0) modify(1, l, r, true, false, false);
        else if (op == 1) modify(1, l, r, false, true, false);
        else if (op == 2) modify(1, l, r, false, false, true);
        else if (op == 3) cout << query(1, l, r).s1 << endl;
        else cout << query(1, l, r).m1 << endl;
    }
    return 0;
}