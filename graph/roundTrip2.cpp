#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<ll>> graph;
vector<int> vis, parent;
int startNode = -1, endNode = -1;

bool dfs(int node)
{
    vis[node] = 1; // visiting
    for (auto next : graph[node])
    {
        if (vis[next] == 0)
        {
            parent[next] = node;
            if (dfs(next))
                return true;
        }
        else if (vis[next] == 1)
        {
            startNode = next;
            endNode = node;
            return true;
        }
    }
    vis[node] = 2; // finished
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    graph.assign(n + 1, {});
    vis.assign(n + 1, 0);
    parent.assign(n + 1, -1);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }

    for (int i = 1; i <= n; i++)
    {
        if (vis[i] == 0 && dfs(i))
            break;
    }

    if (startNode == -1)
    {
        cout << "IMPOSSIBLE";
        return 0;
    }

    vector<int> cycle;
    cycle.push_back(startNode);
    for (int v = endNode; v != startNode; v = parent[v])
        cycle.push_back(v);
    cycle.push_back(startNode);
    reverse(cycle.begin(), cycle.end());

    cout << cycle.size() << "\n";
    for (auto c : cycle)
        cout << c << " ";
    cout << "\n";
}
