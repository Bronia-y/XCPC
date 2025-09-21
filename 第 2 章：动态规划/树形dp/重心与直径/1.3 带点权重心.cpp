#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 1e2 + 10, INF = 0x3f3f3f3f;
vector<int> e[N];

LL n, m; // 分子个数 / 节点个数

// i 分子的节点个数
int w[N]; 

// 子树节点个数
LL f[N]; 

// 去除 i，最多节点的 生成子树的 节点个数
LL g[N];

// 返回 以 x 为根的子树节点个数
LL dfs1(int x, int fa) {
    f[x] = w[x];

    for (auto y : e[x]) {
        if (y == fa) continue;

        LL k = dfs1(y, x);

        f[x] += k;
        g[x] = max(g[x], k);
    }
    g[x] = max(g[x], m - f[x]);
    return f[x];
}

// 返回 x 所有子节点到 x 的总步数
LL dfs2(int x, int fa) {
    LL ret = 0;
    for (auto y : e[x]) {
        if (y == fa) continue;

        int k = dfs2(y, x);
        ret += k + f[y];
    }
    return ret;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        m += w[i];

        // 左链接 右链接
        int l, r; cin >> l >> r;

        if (l) e[i].push_back(l), e[l].push_back(i);
        if (r) e[i].push_back(r), e[r].push_back(i);
    }

    // 以 1 为根节点刷新 f, g
    dfs1(1, 0);
  
    LL mn = INF;
    for (int i = 1; i <= n; ++i) mn = min(mn, g[i]);

    int core;
    for (int i = 1; i <= n; ++i)
        if (g[i] == mn) core = i;

    //  以 core 为根节点刷新 f
    memset(f, 0, sizeof f);
    dfs1(core, 0);

    cout << dfs2(core, 0) << endl;
    
    return 0;
}