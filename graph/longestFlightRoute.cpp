#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> graph(n + 1);
    vector<int> in_degree(n + 1, 0); // For topological sort
    ll a, b;

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        in_degree[b]++; // Increment in-degree of the destination node
    }

    queue<ll> q;
    for (int i = 1; i <= n; i++)
    {
        if (in_degree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<ll> dist(n + 1, -1);
    vector<ll> parent(n + 1, 0);

    // ********************
    // THE FIX IS HERE:
    // We unconditionally set the path length from 1 to 1 as 1.
    // The topological sort will ensure we process nodes in the
    // correct order even though '1' has incoming edges.
    dist[1] = 1;
    // ********************

    vector<ll> topo_order;
    while (!q.empty())
    {
        ll u = q.front();
        q.pop();
        topo_order.push_back(u);

        // This check is the core of the DP:
        // If node 'u' is unreachable from '1', we can't extend a path from it.
        // (This correctly handles nodes 2 and 3 in your example)
        if (dist[u] == -1)
        {
            // This node isn't part of any path starting from '1'.
            // But we still need to process its children for the topo-sort.
            for (ll v : graph[u])
            {
                in_degree[v]--;
                if (in_degree[v] == 0)
                {
                    q.push(v);
                }
            }
            continue; // Skip the DP logic
        }

        // If we get here, dist[u] is valid (it's reachable from 1)
        for (ll v : graph[u])
        {
            // Relax the edge
            if (dist[v] < dist[u] + 1)
            {
                dist[v] = dist[u] + 1;
                parent[v] = u;
            }

            in_degree[v]--;
            if (in_degree[v] == 0)
            {
                q.push(v);
            }
        }
    }

    if (dist[n] == -1)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        cout << dist[n] << endl; // Length of the path

        // Reconstruct the path
        vector<ll> path;
        ll curr = n;
        while (curr != 0)
        {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());

        // We must also check if the reconstructed path actually starts at 1
        // (It's possible to reach 'n' but not from '1')
        if (path.empty() || path[0] != 1)
        {
            cout << "IMPOSSIBLE" << endl;
        }
        else
        {
            for (auto num : path)
            {
                cout << num << " ";
            }
            cout << endl;
        }
    }

    return 0;
}