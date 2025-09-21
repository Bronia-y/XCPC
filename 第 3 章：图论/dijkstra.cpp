// 用【1，m】的边建图，从 1->n, 最短路径
// s 为起点，d 为终点（m预处理用的）
int dijkstra(int m, int s, int d) {
    init(m); // 建图
    memset(dist, 0x3f, sizeof dist); 
    dist[s] = 0; 

    // 注意：默认大根堆
    // first: w
    // second: x(节点)
    priority_queue<PII, vector<PII>, greater<PII>> q; q.emplace(0, s);
    while (q.size()) {
        auto [w, x] = q.top(); q.pop();
        if (x == d) return dist[d]; // 终点(x)已更新，撤

        // 防止已更新节点重复松弛
        // st 表示节点是否完成更新
        if (st[x]) continue;
        st[x] = true;

        // x -> y, 用 x 松弛 y
        for (auto [y, w] : e[x]) { 
            if (dist[x] + w < dist[y]) {
                dist[y] = dist[x] + w;
                q.emplace(dist[y], y);
            }
        }
    }
    return INF; // 所有可达点都松弛，但没见到终点，不连通，默认无穷大
}