#include <bits/stdc++.h>
using namespace std;

set<int> st;

void markConnected(vector<vector<int>> &graph, int src)
{
    st.insert(src);
    for (auto num : graph[src])
    {
        if (st.find(num) != st.end())
            continue;
        markConnected(graph, num);
    }
    return;
}

void solve()
{
    int n;
    int m;
    cin >> n >> m;
    vector<vector<int>> graph(n + 1);
    vector<int> ans;

    int count = 0;
    int a, b;

    for (int j = 0; j < m; j++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 1; i <= n; i++)
    {
        if (st.find(i) != st.end())
            continue;
        count++;
        ans.push_back(i);
        markConnected(graph, i);
    }

    cout << count - 1 << endl;

    for (int i = 0; i < ans.size() - 1; i++)
        cout << ans[i] << " " << ans[i + 1] << endl;

    return;
}

int main()
{
    solve();

    return 0;
}