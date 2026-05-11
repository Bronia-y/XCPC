// modify(i) : f[i] = max(f[i], k)
// query(i) : max(f[1], f[2], ... f[i])
// 考点：维护 f 表，且常常和离散化同时考察
#define lowbit(x) x & -x

int s[N], n; // 维护 f 

void modify(int p, int x) {
    for (int i = p; i <= n; i += lowbit(i)) s[i] = max(s[i], x);
}

int query(int p) {
    int ret = -INF;
    for (int i = p; i; i -= lowbit(i)) ret = max(ret, s[i]);
    return ret;
}