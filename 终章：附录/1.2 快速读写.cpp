#include <bits/stdc++.h>

inline int read() {
	int ret = 0;
	char ch = getchar();
	int flag = 1; // 标记正负

	// 跳过非数字字符
	while (ch < '0' || ch > '9') {
		if (ch == '-') flag = -1; // 处理负号
		ch = getchar();
	}

	while (ch >= '0' && ch <= '9') {
		ret = ret * 10 + ch - '0'; // 秦九韶
		ch = getchar();
	}

	return ret * flag;
}

inline void print(int x) {
	// 处理负号
	if (x < 0) {
		putchar('-');
		x = -x;
	}
	// 先处理前面的位
	if (x / 10) print(x / 10);

	// 处理个位
	putchar('0' + x % 10);
}