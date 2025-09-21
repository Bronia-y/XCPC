#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define lc p << 1
#define rc p << 1 | 1

const int N = 1e5 + 10, INF = 0x3f3f3f3f, MOD = 1e9 + 7;

LL a[N], n, m;

struct node {
    int l, r;
    LL sum, sum2; // 维护区间sum和，区间平方和， 间接维护方差信息
}tr[N << 2];

// 用 l 和 r 拼接 p
void pushup(node& p, node& l, node& r) {
    p.sum = (l.sum + r.sum) % MOD;
    p.sum2 = (l.sum2 + r.sum2) % MOD;
}

void build(int p, int l, int r) {
    tr[p] = {l, r, a[l], a[l] * a[l] % MOD};
    if (l == r) return;
    int m = l + r >> 1;
    build(lc, l, m); build(rc, m + 1, r);
    pushup(tr[p], tr[lc], tr[rc]);
}

node query(int p, int x, int y) {
    auto& [l, r, sum, sum2] = tr[p];
    if (x <= l && r <= y) return tr[p];

    int m = l + r >> 1;
    if (y <= m) return query(lc, x, y);
    else if (x > m) return query(rc, x, y);
    else {
        node ret, ln, rn;
        ln = query(lc, x, y); rn = query(rc, x, y);
        pushup(ret, ln, rn);
        return ret;
    }    
}

void modify(int p, int x, LL k) {
    auto& [l, r, sum, sum2] = tr[p];
    if (l == r) {
        sum = k; sum2 = k * k % MOD;
        return;
    }

    int m = l + r >> 1;
    if (x <= m) modify(lc, x, k);
    else modify(rc, x, k);

    pushup(tr[p], tr[lc], tr[rc]);
}

LL qpow(LL a, LL b) {
    LL ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % MOD;
        a = a * a % MOD, b >>= 1;
    }
    return ret;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);
    
    while (m--) {
        LL op, x, y; cin >> op >> x >> y;
        if (op == 1) modify(1, x, y);
        else {
            auto[_, __, sum, sum2] = query(1, x, y);
            LL len = y - x + 1;
            LL k = qpow(len, MOD - 2);
            cout << ((sum2 * k % MOD - (sum * k % MOD) * (sum * k % MOD) % MOD) % MOD + MOD) % MOD << endl;
        }
    }

    return 0;
}