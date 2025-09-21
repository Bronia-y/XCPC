// 在 n * n * n 的正方体中选 n 个 数，使得sum最小
// 每个（x, y, z）平面只选一个

#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define endl '\n'

const int N = 12, INF = 0x3f3f3f3f;
int a[N + 1][N][N], n;

// fst[i]: 第 i 个 z 平面的 f1和f2, 有且仅有 i 个1，筛选合法状态
vector<int> fst[N + 1]; 

// f[i][f1][f2], 在 【0，i】 号 z 平面挑选，
//0 不挑，x 平面挑选了 f1， y平面挑了 f2，最小sum

// ret = f[n][1111111][1111111]

int f[N + 1][1 << N][1 << N]; 

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n;
    for (int k = 1; k <= n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                cin >> a[k][i][j];

    for (int st = 0; st < (1 << n); ++st) {
        int sum = 0; // st 的 1 的个数
        for (int i = 0; i < n; ++i) 
            if ((st >> i) & 1) ++sum;

        fst[sum].emplace_back(st);
    }

    memset(f, 0x3f, sizeof f);
    f[0][0][0] = 0;

    for (int k = 1; k <= n; ++k)
        for (auto x : fst[k])
            for (auto y : fst[k])
            	// 枚举第 k 个 z 平面可能选的点
                for (int i = 0; i < n; ++i)
                    if ((x >> i) & 1)
                        for (int j = 0; j < n; ++j)
                            if ((y >> j) & 1)
                                f[k][x][y] = min(f[k][x][y], 
                                	a[k][i][j] + f[k - 1][x ^ (1 << i)][y ^ (1 << j)]);

    cout << f[n][(1 << n) - 1][(1 << n) - 1] << endl;

    return 0;
}