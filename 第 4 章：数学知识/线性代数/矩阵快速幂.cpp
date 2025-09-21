// 做斐波那契时，注意前面几项需要特殊判断，否则会TLE(死循环)

#include <bits/stdc++.h>
using namespace std;
using LL = long long;
const int N = 110, MOD = 1e9 + 7;

// n 是矩阵大小，用矩阵快速幂时，往往需要手动赋值
int n;

// 封装矩阵，实现重载乘法
struct mat {
	int m[N][N];
	mat() {
		memset(m, 0, sizeof m);
	}
	mat operator*(const mat& A)const {
		mat ret;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) 
				for (int k = 1; k <= n; ++k)
					ret.m[i][j] = (ret.m[i][j] + m[i][k] * A.m[k][j]) % MOD;
		return ret;
	}
};

// ret = a ^ k
mat qpow(mat a, LL b) {
	mat ret;
	for (int i = 1; i <= n; ++i) ret.m[i][i] = 1; // 初始化成单位矩阵，方便乘法运算

	while (b) {
		if (b & 1) ret = ret * a;
		b >>= 1; a = a * a;
	}
	return ret;
}

int main() {
	mat a;
	LL b;
	cin >> n >> b;

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> a.m[i][j];

	mat ret = qpow(a, b);

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) cout << ret.m[i][j] << ' ';
		cout << endl;
	}

	return 0;
}