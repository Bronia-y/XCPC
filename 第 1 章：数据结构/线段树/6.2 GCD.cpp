#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define lc p << 1
#define rc p << 1 | 1

const int N = 5e5 + 10, INF = 0x3f3f3f3f;

LL a[N], n, q;

struct {
    int l, r;
    LL sum, d; // 维护差分数组的 sum 和 gcd
}tr[N << 2];

void pushup(int p) {
    tr[p].sum = tr[lc].sum + tr[rc].sum;
    tr[p].d = gcd(tr[lc].d, tr[rc].d);
}

void build(int p, int l, int r) {
    tr[p] = {l, r, a[l], a[l]};
    if (l == r) return;

    int m = l + r >> 1;
    build(lc, l, m); build(rc, m + 1, r);
    pushup(p);
}

// 维护的是差分数组，区间修改变成了单点修改
void modify(int p, int x, LL k) {
    auto& [l, r, sum, d] = tr[p];
    if (l == r) {
        sum += k; d += k;
        return;
    }

    int m = l + r >> 1;
    if (x <= m) modify(lc, x, k);
    else modify(rc, x, k);
    pushup(p);
}

LL query_sum(int p, int x, int y) {
    auto& [l, r, sum, d] = tr[p];
    if (x <= l && r <= y) return sum;
    
    LL ret = 0;
    int m = l + r >> 1;
    if (x <= m) ret += query_sum(lc, x, y);
    if (y > m) ret += query_sum(rc, x, y);

    return ret;
}

LL query_d(int p, int x, int y) {
    auto& [l, r, sum, d] = tr[p];
    if (x <= l && r <= y) return d;
    
    LL ret = 0;
    int m = l + r >> 1;
    if (x <= m) ret = gcd(ret, query_d(lc, x, y));
    if (y > m) ret = gcd(ret, query_d(rc, x, y));

    return ret;
}

// 数组的 gcd 和它对应的 差分数组 gcd 一致
// gcd(a, b, c, d) == gcd(a, b - a, c - b, d - c)
// 本题是求右边，从而间接求出左边

int main() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        LL x; cin >> x;
        a[i] += x; a[i + 1] -= x;
    }

    build(1, 1, n);

    while (q--) {
        char op; int x, y; 
        cin >> op >> x >> y;

        if (op == 'Q') {
            // 根据公式：第一项为原数组的值，用 sum[1, x] 表示
            LL sum = query_sum(1, 1, x); 
            LL d = 0;
            // 根据公式：其余项为差分数组值，直接求 gcd
            if (x + 1 <= y) d = query_d(1, x + 1, y); 

            // ret 为所有项的 gcd
            LL ret = gcd(sum, d);

            // 由于存在减法操作，可能出现负数，此处直接补正即可
            cout << abs(ret) << endl;
        }
        else {
            LL k; cin >> k;
            modify(1, x, k); 
            if (y + 1 <= n) modify(1, y + 1, -k);
        }
    }

    return 0;
}