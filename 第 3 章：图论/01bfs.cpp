void _01bfs() {
    vector<int> dist(n + 10, INF);
    dist[1] = 0;

    deque<int> q;
    q.emplace_back(1);

    vector<bool> st(n + 10, false);

    while (q.size()) {
        auto x = q.front(); q.pop_front();

        if (st[x]) continue;
        st[x] = true;

        for (auto [y, w] : e[x]) {
            if (dist[x] + w < dist[y]) {
                dist[y] = dist[x] + w;
                if (w == 0) q.push_front(y);
                else q.push_back(y);
            }
        }
    }
}