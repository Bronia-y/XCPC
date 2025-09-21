#include <bits/stdc++.h>
using namespace std;
using LL = long long;

const int N = 2e5 + 10; 
const LL INF = 1e18;

LL mx[N][25];

LL query(int l, int r) {
    int k = log2(r - l + 1);
    return max(mx[l][k], mx[r - (1 << k) + 1][k]);
}

// 黑盒：ST表维护的是[1, n] 所有子区间的信息

// x 是尾插后的最后下表
void modify(int x, LL k) {
    // 刷新尾插所造成影响的区间
    mx[x][0] = k;
    for (int j = 1; x - (1 << j) + 1 >= 1; ++j) {
        int i = x - (1 << j) + 1;
        mx[i][j] = max(query(i, x - 1), k);
    }
}

int main() {
    int q, d;
    cin >> q >> d;
    LL end = 0, pre = 0;

    while (q--) {
       
        char op; LL x;
        cin >> op >> x;
        if (op == 'A') modify(++end, (pre + x) % d);
        else cout << (pre = query(end - x + 1, end)) << endl;
    }
    
    return 0;
}