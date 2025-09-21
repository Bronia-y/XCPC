#include <bits/stdc++.h>
using namespace std;
const int N = 15, INF = 0x3f3f3f3f;

int a[N], n;

int f[N][N]; // 

// 从 p 位置开始填，前一位是 prev，限制为limit，共有多少种
// limit : 父亲都是上届
int dfs(int p, int prev, bool limit) {
    if (p == 0) return 1;
    if (~f[p][prev][limit]) return f[p][prev][limit];

    int end = 9;
    if (limit) end = a[p]; // 父亲都是上界

    int ret = 0;

    for (int i = prev; i <= end; ++i) 
        ret += dfs(p - 1, i, limit && (i == a[p])); 
    // 当所有父亲都是上界，我也是上界，那么我的孩子的所有父亲都是上届

    return f[p][prev][limit] = ret;
}

// 统计[0, x]，不降数的个数
int calc(int x) {
    if (x == 0) return 1;

    memset(f, -1, sizeof f);
    n = 0;

    while (x) {
        a[++n] = x % 10;
        x /= 10;
    }

    return dfs(n, 0, true);
}

int main() {
    int a, b; 
    while (cin >> a >> b) {
        cout << calc(b) - calc(a - 1) << endl;
    }    
    
    return 0;
}