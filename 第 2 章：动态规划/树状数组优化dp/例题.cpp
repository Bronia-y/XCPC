#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
using namespace std;
const int N = 2e5 + 10, INF = 0x3f3f3f3f, m = 1e9 + 9;
int a[N], n;
int pre[N];

int disc[N], pos;
map<int, int> mp;

void init() {
    for (int i = 0; i <= n; ++i) disc[++pos] = pre[i];
    sort(disc + 1, disc + pos + 1);
    pos = unique(disc + 1, disc + pos + 1) - (disc + 1);
    for (int i = 1; i <= pos; ++i) mp[disc[i]] = i;
}

int s[N]; // pos 项

// f[p] += x
void modify(int p, int x) {
    for (int i = p; i <= pos; i += lowbit(i)) s[i] = (s[i] + x) % m;
}

int query(int p) {
    int sm = 0;
    for (int i = p; i; i -= lowbit(i)) sm = (sm + s[i]) % m;
    return sm;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) pre[i] = pre[i - 1] + a[i];
    init();
    int ret = 0;

    // f[0] += 1
    modify(mp[0], 1);
    for (int i = 1; i <= n; ++i) {
        int x = mp[pre[i]];

        // f[pre[i]] += (f[-无穷] ... f[-1], f[0], f[1], ... f[pre[i]])
        if (i == n) ret = query(x);
        modify(x, query(x));
    }
    cout << ret;
    
    return 0;
}