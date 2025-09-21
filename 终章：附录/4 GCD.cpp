#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y) {
    return y ? gcd(y, x % y) : x;
}

int main() {
    int ret = 0;
    int x;
    while (cin >> x) ret = gcd(ret, x);
    cout << ret;

    return 0;
}