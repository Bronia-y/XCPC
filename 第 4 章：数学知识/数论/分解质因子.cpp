void deprime(int x) {
    for (int i = 2; i <= x / i; ++i) {
        if (x % i == 0) {
            p[++pos] = i;
            while (x % i == 0) a[pos]++, x /= i;
        }
    }
    if (x != 1) p[++pos] = x, a[pos] = 1;
}