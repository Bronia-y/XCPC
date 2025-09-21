#include <bits/stdc++.h>
using namespace std;
using LL = long long;

LL a, b, MOD;

LL qmul(LL a, LL b) {
	LL ret = 0;
	while (b) {
		if (b & 1) ret = (ret + a) % MOD;

		a = (a << 1) % MOD; b >>= 1;
	}
	// ret = a * b % MOD
	return ret;
}

int main() {
	cin >> a >> b >> MOD;
	cout << qmul(a, b) << endl;

	return 0;
}