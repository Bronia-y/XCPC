// 蒟蒻 SOL 居然觉得数很萌！

// 好在在他眼里，并不是所有数都是萌的。只有满足“存在长度至少为 2 的回文子串”的数是萌的——
// 也就是说，101 是萌的，因为 101 本身就是一个回文数；110 是萌的，因为包含回文子串 11；
// 但是 102 不是萌的，1201 也不是萌的。

// 现在 SOL 想知道从 l 到 r 的所有整数中有多少个萌数。

// 由于答案可能很大，所以只需要输出答案对 1000000007（1e9+7）的余数。

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 1e3 + 10, INF = 0x3f3f3f3f, MOD = 1e9 + 7;

LL f[N][10][10][2][2][2];
int a[N], n;

// p1 p2 p
// f1 表示 p1 为非前导0合法位
// f2 表示 p2 为非前导0合法位
// ff 是萌数，数字合法
LL dfs(int p, int p1, int p2, bool f1, bool f2, bool ff, bool limit, bool zero) {
    if (p == 0) return ff;
    if (!limit && ~f[p][p1][p2][f1][f2][ff]) return f[p][p1][p2][f1][f2][ff];

    LL ret = 0;
    int up = limit ? a[p] : 9;

    for (int i = 0; i <= up; ++i) {
        ret = (ret + dfs(p - 1, p2, i, f2, !(zero && i == 0), 
        ff || i == p1 && f1 || i == p2 && f2, limit && i == a[p], zero && i == 0)) % MOD;
    }

    if (!limit) return f[p][p1][p2][f1][f2][ff] = ret;
    else return ret;
}

LL calc(string x) {
    if (x.size() <= 1) return 0;

    memset(f, -1, sizeof f); 
    n = x.size(); x = ' ' + x;
    for (int i = 1; i <= n; ++i) a[i] = x[n - i + 1] - '0'; 

    return dfs(n, 0, 0, false, false, false, true, true);
}

bool cheak(string s) {
    int n = s.size(); 
    s = ' ' + s;
    if (s[2] == s[1]) return true;
    for (int i = 3; i <= n; ++i) 
        if (s[i] == s[i - 1] || s[i] == s[i - 2]) return true;
    return false;
}

int main() {
    string x, y; cin >> x >> y;
    LL ret = ((calc(y) - calc(x)) % MOD + MOD) % MOD;
    if (cheak(x)) ret = (ret + 1) % MOD;
    cout << ret;
    return 0;
}