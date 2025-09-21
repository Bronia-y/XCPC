// 以 0 为起点，n - 1 为终点，最小的排列

#include <bits/stdc++.h>
using namespace std;
const int N = 20, INF = 0x3f3f3f3f;
int n;
int e[N][N];

// f[st][i] : 由 st 组成，以 0为起点， i 为结尾，的最小排列
int f[1 << N][N]; 

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> e[i][j];

    memset(f, 0x3f, sizeof f);
    f[1][0] = 0; // st仅包含 0 时，当终点为 0 时有效，排列权值为 0 

    for (int st = 2; st < (1 << n); ++st) 
        if (st & 1) // 以 0 为起点，0 必须包含
            for (int i = 0; i < n; ++i) // 落点
                if ((st >> i) & 1) 
                    for (int j = 0; j < n; ++j) // 前一步的落点
                        if (((st >> j) & 1) && j != i) 
                            f[st][i] = min(f[st][i], f[st ^ (1 << i)][j] + e[j][i]);

    cout << f[(1 << n) - 1][n - 1];
    
    return 0;
}