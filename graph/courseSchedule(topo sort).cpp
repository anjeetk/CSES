#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<vector<ll>> graph;
vector<ll> in_degree;
vector<int> vis;
ll a, b, c, n, m;

bool dfs(int src)
{
    vis[src] = 1;
    bool flag = false;
    for (auto num : graph[src])
    {
        if (vis[num] == 0)
        {
            vis[num]++;
            flag = dfs(num);
        }
        else if (vis[num] == 1)
            return true;
    }
    vis[src] = 2;
    return flag;
}

bool isCycle()
{
    vis.assign(n + 1, 0);
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            if (dfs(i))
                return true;

    return false;
}

void topoSort(vector<ll> &ans)
{
    queue<int> q;

    for (int i = 1; i <= n; i++)
        if (in_degree[i] == 0)
            q.push(i);

    if (q.empty() || isCycle())
    {
        cout << "IMPOSSIBLE" << endl;
        return;
    }

    while (!q.empty())
    {
        int front = q.front();
        q.pop();
        ans.push_back(front);
        for (auto num : graph[front])
        {
            in_degree[num]--;
            if (in_degree[num] == 0)
                q.push(num);
        }
    }
    return;
}

int main()
{
    cin >> n >> m;
    graph.assign(n + 1, {});
    in_degree.assign(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        in_degree[b]++;
    }

    vector<ll> ans;
    topoSort(ans);
    for (auto num : ans)
        cout << num << " ";
    return 0;
}
