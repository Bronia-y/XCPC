#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f;

// f[i] : 以 i （离散化后的值）为结尾的 LIS
int s[N], n = 1e5; // 维护 f, s[i] = max(f[1], f[2] ... f[i])
int a[N], m;

// disc[i] : i 离散化前的值
// mp[i] : i 离散化后的值
int disc[N], pos;
map<int, int> mp;

// f[p] = max(f[p], x)
void modify(int p, int x) {
    for (int i = p; i <= pos; i += lowbit(i)) s[i] = max(s[i], x);
}

// return max(f[1], f[2] ... f[p])
int query(int p) {
    int ret = 0;
    for (int i = p; i; i -= lowbit(i)) ret = max(ret, s[i]);
    return ret;
}

// 初始化离散化
void init() {
    for (int i = 1; i <= m; ++i) disc[i] = a[i];
    pos = m;
    sort(disc + 1, disc + pos + 1);
    pos = unique(disc + 1, disc + pos + 1) - (disc + 1);
    for (int i = 1; i <= pos; ++i) mp[disc[i]] = i;
}

int main() {
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> a[i];
    init();
    // f 有 pos 项

    for (int i = 1; i <= m; ++i) {
        int x = mp[a[i]]; // 取离散化后的值
        
        // f[x] = max(f[x], max(f[1], f[2], ... f[x - 1]) + 1)
        modify(x, query(x - 1) + 1);
    }

    // ret = max(f[1], f[2], ... f[pos])
    cout << query(pos);
    
    return 0;
}