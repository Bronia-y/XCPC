// 定义：
// 在一棵树上有 n 个 分子，每一个分子上有若干个节点，节点总数为 m
// g[i] : 将第 i 个 分子 及其 相连的边删去，生成的若干子树中，节点个数最多的 子树的 节点个数
// g[core] = min(g[N])

// 性质 1 ： 重心最多有两个，如果有两个，那么两重心一定相邻
// 性质 2 ： 所有子树节点个数不会超过 m / 2 (向下取整)
// 性质 3 ： 
//     dist[i] : 所有节点到 i 分子的距离总和
//     dist[core] = min(dist[N])

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 5e4 + 10, INF = 0x3f3f3f3f;
vector<int> e[N];
int n;

// i分子 为根的 子树的 节点个数
int f[N];

int g[N];

// 返回 以 x分子 为根的子树的节点个数
int dfs1(int x, int fa) {
    f[x] = 1;

    for (auto y : e[x]) {
        if (y == fa) continue;

        int k = dfs1(y, x);

        f[x] += k;
        g[x] = max(g[x], k);
    }

    g[x] = max(g[x], n - f[x]);
    return f[x];
}

// 所有子节点走到 x 的距离总和
LL dfs2 (int x, int fa) {
    LL ret = 0;
    for (auto y : e[x]) {
        if (y == fa) continue;
        int k = dfs2(y, x);
        // y 的子节点共 f[y] 个
        // 这 f[y] 个节点先走到 y 共走了 k 步
        // 然后他们再一起走一步到 x，共 f[y] 步
        ret += k + f[y];
    }
    return ret;
}

int main() {
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        e[x].push_back(y); e[y].push_back(x);
    }

    // 以 1 为根节点刷新 f, g
    dfs1(1, 0);

    int mn = INF;

    for (int i = 1; i <= n; ++i) mn = min(mn, g[i]);
    
    int core; // 重心

    for (int i = 1; i <= n; ++i) {
        if (g[i] == mn) {
            core = i;
            break;
        }
    }

    memset(f, 0, sizeof f);
    dfs1(core, 0); // 用重心为根，刷新 f 数组
    cout << core << ' ';
    cout << dfs2(core, 0) << endl;
    
    return 0;
}