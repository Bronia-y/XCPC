#include <bits/stdc++.h>
using namespace std;
const int N = 8e3 + 10, INF = 0x3f3f3f3f;
int n, m, k, T;
int a[N][N];
int f[N][N];
int q[N]; int h = 1, t = 0;

// f[i][j] = max(f[i - 1][j - T], f[i - 1][j - T + 1], 
// ... f[i - 1][j + T]) + a[i][j]

int main() {
    cin >> n >> m >> k >> T;
    for (int i = 1; i <= k; ++i) {
        int x, y, v; cin >> x >> y >> v;
        a[x][y] = v;
    }

    int ret = 0;
    for (int i = 1; i <= n; ++i) {
        h = 1, t = 0;

        // 手法：j 从 1 - T开始，直接将 T 个点入队列
        for (int j = 1 - T; j <= m; ++j) {
            // 手法：j + T > m 时不应该入队，但是不妨入队，因为 f[i - 1][k > m] == 0
            // j + T 入队
            while (h <= t && f[i - 1][q[t]] <= f[i - 1][j + T]) --t;
            q[++t] = j + T;

            while (q[t] - q[h] + 1 > 2 * T + 1) ++h;
            if (j >= 1) {
                f[i][j] = f[i - 1][q[h]] + a[i][j];
                ret = max(ret, f[i][j]);
            }
        }
    }
    cout << ret;
    
    return 0;
}