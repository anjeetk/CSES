#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<int>> graph;
vector<ll> dp;
vector<int> vis;
int n, m;
const int mod = 1e9 + 7;

ll dfs(int src)
{
    if (src == n)
        return 1;
    if (dp[src] != -1)
        return dp[src];

    ll ways = 0;
    vis[src] = 1;
    for (int nxt : graph[src])
    {
        if (!vis[nxt])
        {
            ways = (ways + dfs(nxt)) % mod;
        }
    }
    vis[src] = 0;
    return dp[src] = ways;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    graph.assign(n + 1, {});
    dp.assign(n + 1, -1);
    vis.assign(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }

    cout << dfs(1) << "\n";
    return 0;
}
