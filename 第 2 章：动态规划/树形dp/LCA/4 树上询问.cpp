// 查询 有多少个节点作为根节点时，lca(a, b) == c
// 本质：一般情况下，以 c 为核心，除了a, b所在分支，其余节点均可
#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, INF = 0x3f3f3f3f;
vector<int> e[N];
int dep[N];
int f[N][25];
int sum[N]; // 以该节点为根的子树的 节点个数

void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    sum[x] = 1;

    f[x][0] = fa;
    for (int i = 1; i <= 20; ++i)
        f[x][i] = f[f[x][i - 1]][i - 1];

    for (auto y : e[x]) {
        if (y == fa) continue;
        dfs(y, x);
        sum[x] += sum[y];
    }
}

// x 向上跳，跳到 depth 那一层
int up(int x, int depth) {
    for (int i = 20; i >= 0; --i)
        if (dep[f[x][i]] >= depth) x = f[x][i];
    return x;
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    x = up(x, dep[y]);

    if (x == y) return y;

    for (int i = 20; i >= 0; --i)
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    
    return f[x][0];
}

int main() {
    int n, m; 
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        e[x].push_back(y); e[y].push_back(x);
    }

    dfs(1, 0);

    for (int i = 1; i <= m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;

        // 三点重合，所有点都行
        if (a == b && b == c) cout << n << endl;
        // 考虑两两重合

        // a 和 b 重合，必定无解
        else if (a == b) cout << 0 << endl;
        // a 和 c 重合
        else if (a == c) {
            // 除了 b 所在的分支都行
            if (lca(b, c) == c) {
                b = up(b, dep[c] + 1);
                cout << n - sum[b] << endl;
            }
            else cout << sum[c] << endl;
        }
        else if (b == c) {
            // 除了 a 所在的分支都行
            if (lca(a, c) == c) {
                a = up(a, dep[c] + 1);
                cout << n - sum[a] << endl;
            }
            else cout << sum[c] << endl;
        }
        // 考虑没有重合的情况
        // 若有解，则a, b都是 c 的孩子，或者一个是 c 的孩子，而另一个不是

        // 先考虑 a, b 都是 c 的孩子
        else if (lca(a, c) == c && lca(b, c) == c) {
            // a 和 b 在 c 的不同分枝
            if (lca(a, b) == c) {
                a = up(a, dep[c] + 1);
                b = up(b, dep[c] + 1);
                cout << n - sum[a] - sum[b] << endl;
            }
            // a 和 b 在 c 的同一个分枝
            else cout << 0 << endl;
        }
        // 再考虑一个是 c 的孩子，而另一个不是

        // a 是 b 不是
        else if (lca(b, c) == c && lca(a, c) != c) {
            b = up(b, dep[c] + 1);
            cout << sum[c] - sum[b] << endl;
        }
        // b 是 a 不是
        else if(lca(a, c) == c && lca(b, c) != c) {
            a = up(a, dep[c] + 1);
            cout << sum[c] - sum[a] << endl;
        }
        // 其余情况均无解
        else cout << 0 << endl;
    }
    
    return 0;
}