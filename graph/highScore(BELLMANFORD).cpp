#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef pair<int, int> pp;

int32_t main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pp>> graph(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].push_back({b, -c}); // negate weight for longest path
    }

    vector<int> dist(n + 1, 1e15);
    dist[1] = 0;

    // Bellman-Ford relaxation (n-1 times)
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (dist[j] == 1e15)
                continue;
            for (auto &it : graph[j])
            {
                int dest = it.first;
                int weight = it.second;
                if (dist[j] + weight < dist[dest])
                {
                    dist[dest] = dist[j] + weight;
                }
            }
        }
    }

    // Detect negative cycles reachable from source that can reach destination
    vector<int> affected(n + 1, 0);
    for (int j = 1; j <= n; j++)
    {
        if (dist[j] == 1e15)
            continue;
        for (auto &it : graph[j])
        {
            int dest = it.first;
            int weight = it.second;
            if (dist[j] + weight < dist[dest])
            {
                affected[j] = 1;
                affected[dest] = 1;
            }
        }
    }

    // Propagate the effect of negative cycles
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (affected[i])
            q.push(i);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto &it : graph[u])
        {
            if (!affected[it.first])
            {
                affected[it.first] = 1;
                q.push(it.first);
            }
        }
    }

    if (affected[n])
    {
        cout << -1 << endl; // infinite score due to positive cycle
    }
    else
    {
        cout << -dist[n] << endl; // negate back for longest path
    }

    return 0;
}
