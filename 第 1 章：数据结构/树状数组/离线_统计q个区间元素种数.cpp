#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) (x & -x)

const int N = 1e6 + 10;
int a[N], n, m;
struct node {
	int id;
	int l, r;
}q[N];

int ret[N]; // ret[k] : 第 k 个问题答案

int mp[N]; // mp[k] : k 上一次出现的位置

int s[N];

// s[x] += k
void modify(int x, int k) {
	for (int i = x; i <= n; i += lowbit(i)) s[i] += k;
}

// return [1, x]
int query(int x) {
	int ret = 0;
	for (int i = x; i; i -= lowbit(i)) ret += s[i];
	return ret;
}

// 贡献法
// 算法原理概述：对于某一个元素 x, 只点亮最右边的 x
// 总述：以cur为右端点的区间一定正确
// 1. 对于 x 最多贡献一次，因为在[1, cur] 之间只保留了 1 个x
// 2. x 不可能不贡献，因为保留的是最右边的 x, 如果[l, cur] 之间有 x, 一定会包含被保留的 x
// 3. 所以对于某一个特定的 x ,贡献且仅贡献一次
void solve() {
	// 优先解决 r 较小的问题
	sort(q + 1, q + m + 1, [] (node l, node r) { return l.r < r.r; } );

	//cur : 将要考虑的元素
	for (int i = 1, cur = 1; i <= m; ++i) {
		auto [id, l, r] = q[i];
		while (cur <= r) {
			int x = a[cur];
			int pre = mp[x];

			if (pre) modify(pre, -1); // 消除前面的
			modify(cur, 1); // 统计现在的

			mp[x] = cur;
			++cur;
		}
		ret[id] = query(r) - query(l - 1);
	}
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) cin >> a[i];
	cin >> m;
	for (int i = 1; i <= m; ++i) {
		auto& [id, l, r] = q[i];
		id = i; cin >> l >> r;
	}

	solve();

	for (int i = 1; i <= m; ++i) cout << ret[i] << endl;
	cout << endl;

	return 0;
}