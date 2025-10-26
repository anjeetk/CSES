#include <bits/stdc++.h>
using namespace std;

vector<int> parent;
vector<bool> visited;
int start_node, end_node;
bool found = false;

void dfs(vector<vector<int>> &graph, int v, int p)
{
    visited[v] = true;
    parent[v] = p;

    for (int u : graph[v])
    {
        if (u == p)
            continue;

        if (visited[u])
        {
            start_node = u;
            end_node = v;
            found = true;
            return;
        }
        else
        {
            dfs(graph, u, v);
            if (found)
                return;
        }
    }
}

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n + 1);
    visited.assign(n + 1, false);
    parent.assign(n + 1, -1);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
        {
            dfs(graph, i, -1);
            if (found)
                break;
        }
    }

    if (!found)
    {
        cout << "IMPOSSIBLE\n";
        return;
    }

    vector<int> cycle;
    cycle.push_back(start_node);
    for (int v = end_node; v != start_node; v = parent[v])
        cycle.push_back(v);
    cycle.push_back(start_node);

    if ((int)cycle.size() - 1 < 3)
    {
        cout << "IMPOSSIBLE\n";
        return;
    }

    cout << cycle.size() << "\n";
    for (int v : cycle)
        cout << v << " ";
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
