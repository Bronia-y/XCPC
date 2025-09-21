// 返回值：gcd(a, b)
// ax + by = gcd(a, b), 将 x, y 赋值成满足等式的特解
// 特殊判断：gcd(a, 0) = a
LL exgcd(LL a, LL b, LL& x, LL& y) {
    if (b == 0) {
        x = 1; 
        y = 0;
        return a;
    }

    LL x1, y1, d;
    d = exgcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - a / b * y1;
    return d;
}

// 求 a 在 MOD 意义下的乘法逆元 
int re(int a) {
    int x, y;
    exgcd(a, MOD, x, y);
    return (x % MOD + MOD) % MOD;
}

void func() {
    LL a, b, x, y;
    LL d = exgcd(a, b, x, y);

    // 小写表示特解，大写表示通解
    // k 是任意整数
    X = x + k * (b / d)
    Y = y - k * (a / d)
}