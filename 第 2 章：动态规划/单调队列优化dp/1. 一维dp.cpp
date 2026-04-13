#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 10, INF = 0x3f3f3f3f;
int f[N];
int n, l, r;
int a[N];

int q[N];
int h = 1, t = 0;

// 状态转移方程：f[i] = max(f[i - r], f[i - r + 1], ... f[i - l])

int main() {
    cin >> n >> l >> r;
    for (int i = 0; i <= n; ++i) cin >> a[i];
    
    memset(f, -0x3f, sizeof f);
    f[0] = 0;

    int ret = -INF;
    for (int i = l; i <= n + r; ++i) {
        // i - l 入队
        while (h <= t && f[q[t]] <= f[i - l]) --t;
        q[++t] = i - l;
        
        // 维护实际区间长度
        while (q[t] - q[h] + 1 > r - l + 1) ++h;

        // 状态转移
        f[i] = f[q[h]] + a[i];
        if (i > n) ret = max(ret, f[i]);
    }

    cout << ret << endl;

    return 0;
}