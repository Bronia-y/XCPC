#include <bits/stdc++.h>
using namespace std;
using PII = pair<int, int>;

const int N = 1.5e5 + 10;

int n, m, k;
int s, t;

vector<PII> e[N];

bool st[N];
int dist[N];

void dijkstra() {
	memset(dist, 0x3f, sizeof dist);
	dist[s] = 0;
	
	priority_queue<PII, vector<PII>, greater<PII>> q;
	q.emplace(0, s);
	
	while (q.size()) {
		auto [w, x] = q.top(); q.pop();
		
		if (st[x]) continue;
		st[x] = true;
		
		for (auto [w, y] : e[x]) {
			if (dist[x] + w < dist[y]) {
				dist[y] = dist[x] + w;
				q.emplace(dist[y], y);
			}
		}
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	
	cin >> n >> m >> k;
	cin >> s >> t;
	
	for (int i = 1; i <= m; ++i) {
		int a, b, w;
		cin >> a >> b >> w;
		e[a].emplace_back(w, b);
		e[b].emplace_back(w, a);
		
		for (int j = 1; j <= k; ++j) {
			int x = a + n, y = b + n;
			
			e[x].emplace_back(w, y);
			e[y].emplace_back(w, x);
			
			e[a].emplace_back(0, y);
			e[b].emplace_back(0, x);
			a = x, b = y;
		}
	}
	
	dijkstra();
	
	int ret = 1e9;
	for (int i = 0; i <= k; ++i)
		ret = min(ret, dist[t + i * n]);
		
	cout << ret << endl;
}