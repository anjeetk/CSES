#include <bits/stdc++.h>
using namespace std;

vector<int> visited;
bool isPossible = true;

void markConnected(vector<vector<int>> &graph, int src, int team)
{
    if (visited[src] == 1 - team)
    {
        isPossible = false;
        return;
    }
    if (visited[src] != -1)
        return;
    visited[src] = team;
    for (auto num : graph[src])
        markConnected(graph, num, 1 - team);
}

void solve()
{
    int n, m;
    cin >> n >> m;
    visited.assign(n + 1, -1);

    int a, b;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        if (visited[i] != -1)
            continue;
        markConnected(graph, i, 0);
        if (!isPossible)
        {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    }

    for (int i = 1; i <= n; i++)
        cout << visited[i] + 1 << " ";
    cout << endl;
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
