#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL a, b, MOD;

LL qpow(LL a, LL b) {
	LL ret = 1;
	while (b) {
		if (b & 1) ret = ret * a % MOD;

		a = a * a % MOD; b >>= 1;
	}
	return ret;
}

int main() {
	cin >> a >> b >> MOD;
	printf("%d^%d mod %d=%d", a, b, MOD, qpow(a, b));

	return 0;
}