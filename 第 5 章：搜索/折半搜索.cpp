#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 2e6, INF = 0x3f3f3f3f;
LL a[100], n; LL k;
LL a1[N], a2[N];
int p1, p2;
LL path;

// 枚举[1, m], 所有可能
void ldfs(int p, int end) {
    if (p == end + 1) {
        a1[++p1] = path;
        return;
    }

    ldfs(p + 1, end);
    path += a[p];
    ldfs(p + 1, end);
    path -= a[p];
}

// 枚举[m + 1, n] 解空间
void rdfs(int p, int end) {
    if (p == end + 1) {
        a2[++p2] = path;
        return;
    }

    rdfs(p + 1, end);
    path += a[p];
    rdfs(p + 1, end);
    path -= a[p];
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int m = n >> 1;
    ldfs(1, m); 
    rdfs(m + 1, n);

    // 拼凑解空间（用双指针，二分，哈希表等暴力优化算法）
    sort(a1 + 1, a1 + p1 + 1, greater<LL>());
    sort(a2 + 1, a2 + p2 + 1);

    LL ret = 0;
    for (int i = 1, j = 1; i <= p1; ++i) {
        while(j <= p2 && a1[i] + a2[j] <= k) ++j;
        ret += j - 1;
    }
    cout << ret << endl;
    
    return 0;
}