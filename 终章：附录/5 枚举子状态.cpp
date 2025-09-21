#include <bits/stdc++.h>
using namespace std;

void func(int k) {// 总位数
	for (int x = 0; x < (1 << k); ++x) // 枚举所有状态
	{
		// 枚举 x 的所有子状态 y 
		for (int y = x; ; y = (y - 1) & x) // 正常减一，然后 & x 消除多借的位
		{

			if (y == 0) break;
		}
	}
}