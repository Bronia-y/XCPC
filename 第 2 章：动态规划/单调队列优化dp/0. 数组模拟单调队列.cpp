// 实现 长度为k的 连续段的 最大最小值

#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int n, k;
int a[N]; // 单调队列需要维护的序列
// 注意：单调队列存 key
int q[N]; // 单调队列，左头右尾
int h = 1, t = 0; 

// 单调递增求最小
void solve1() {
    for (int i = 1; i <= n; ++i) {
        // push
        while (h <= t && a[q[t]] >= a[i]) --t; // 保持单调性
        q[++t] = i;
        
        while (q[t] - q[h] + 1 > k) {
            // pop
            ++h;
        }

        // 解题
        if (i >= k) cout << a[q[h]] << ' ';
    }
    cout << endl;
}

// 单调递减求最大
void solve2() {
    for (int i = 1; i <= n; ++i) {
        // push
        while (h <= t && a[q[t]] <= a[i]) --t; // 保持单调性
        q[++t] = i;
        
        while (q[t] - q[h] + 1 > k) {
            // pop
            ++h;
        }

        // 解题
        if (i >= k) cout << a[q[h]] << ' ';
    }
    cout << endl;
}


int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    
    solve1();

    h = 1, t = 0; // 清空队列

    solve2();

    return 0;
}