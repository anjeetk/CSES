#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> pli;
const ll INF = 1e18; // use 1e18 since weights can be large

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<pair<int, int>>> graph(n + 1);
	for (int i = 0; i < m; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({b, c}); // directed edge
	}

	vector<ll> dist(n + 1, INF);
	dist[1] = 0;

	priority_queue<pli, vector<pli>, greater<pli>> pq;
	pq.push({0, 1});

	while (!pq.empty())
	{
		auto [d, u] = pq.top();
		pq.pop();

		if (d != dist[u])
			continue; // skip outdated entries

		for (auto [v, w] : graph[u])
		{
			if (dist[u] + w < dist[v])
			{
				dist[v] = dist[u] + w;
				pq.push({dist[v], v});
			}
		}
	}

	for (int i = 1; i <= n; i++)
		cout << dist[i] << " ";
	cout << "\n";

	return 0;
}
