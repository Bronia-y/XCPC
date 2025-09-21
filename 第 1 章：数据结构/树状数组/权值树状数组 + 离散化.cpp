#include <bits/stdc++.h>
using namespace std;
using LL = long long;

#define lowbit(x) (x & -x)

const int N = 1e6 + 10;

int disc[N], pos;
LL s[N];
int a[N], n;

int id(int x) {
	int l = 1, r = pos;
	while (l < r) {
		int m = l + r >> 1;
		if (disc[m] >= x) r = m;
		else l = m + 1;
	}
	return l;
}

void modify(int p, int x) {
	for (int i = p; i <= pos; i += lowbit(i)) s[i] += x;
}

LL query(int x) {
	LL ret = 0;
	for (int i = x; i; i -= lowbit(i)) ret += s[i];
	return ret;
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);

	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int x; cin >> x;
		a[i] = x; disc[++pos] = x;
	}

	sort(disc + 1, disc + pos + 1);
	pos = unique(disc + 1, disc + pos + 1) - (disc + 1);

	LL ret = 0;
	for (int i = 1; i <= n; ++i) {
		int k = id(a[i]);
		ret += query(pos) - query(k);
		modify(k, 1);
	}
	cout << ret << endl;

	return 0;
}