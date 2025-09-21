vector<PII> e[N];
int dist[N];
int st[N];
int cnt[N];

bool spfa() {
    queue<int> q; q.emplace(0);
    st[0] = true;
    
    memset(dist, -0x3f, sizeof dist);
    dist[0] = 0;

    while (q.size()) {
        auto x = q.front(); q.pop();
        st[x] = false;

        for (auto [y, w] : e[x]) {
            if (dist[x] + w > dist[y]) {
                dist[y] = dist[x] + w;

                cnt[y] = cnt[x] + 1;
                if (cnt[y] >= n + 1) return false;

                if (!st[y]) q.emplace(y), st[y] = true;
            }
        }
    }

    return true;
}