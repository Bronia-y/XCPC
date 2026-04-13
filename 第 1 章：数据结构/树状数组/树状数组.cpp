#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define lowbit(x) (x & -x)

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
LL s[N];
int n, m;

// 可以通过对 差分数组 单点修改 + 区间查询
// 间接完成对 原数组区 间修改 + 单点查询

// a[i] += x
void modify(int p, int x) {
    for (int i = p; i <= n; i += lowbit(i)) s[i] += x;
}

// return sum[1, x]
LL query(int p) {
    LL ret = 0;
    for (int i = p; i; i -= lowbit(i)) ret += s[i];
    return ret;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        modify(i, x);
    }
    while (m--) {
        int op, x, y; cin >> op >> x >> y;
        // a[x] += y
        if (op == 1) modify(x, y);
        // cout << sum[x, y] << endl;
        else cout << query(y) - query(x - 1) << endl;
    }
    
    return 0;
}