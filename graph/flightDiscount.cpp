#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> g(n+1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
    }
    
    // dist[node][used_coupon]
    vector<vector<ll>> dist(n+1, vector<ll>(2, INF));
    dist[1][0] = 0;
    
    // min-heap: (cost, node, used_coupon)
    priority_queue<tuple<ll,int,int>, vector<tuple<ll,int,int>>, greater<>> pq;
    pq.emplace(0, 1, 0);

    while (!pq.empty()) {
        auto [cost, u, used] = pq.top(); pq.pop();
        if (cost > dist[u][used]) continue;
        for (auto [v, c] : g[u]) {
            // Go without coupon
            if (dist[v][used] > cost + c) {
                dist[v][used] = cost + c;
                pq.emplace(dist[v][used], v, used);
            }
            // Go with coupon (if not yet used)
            if (!used && dist[v][1] > cost + c/2) {
                dist[v][1] = cost + c/2;
                pq.emplace(dist[v][1], v, 1);
            }
        }
    }
    cout << min(dist[n][0], dist[n][1]) << endl;
    return 0;
}
