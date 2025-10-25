#include <bits/stdc++.h>
using namespace std;

vector<vector<bool>> visited;

void markConnected(vector<vector<char>> &graph, int x, int y, int n, int m)
{
    int arr[] = {0, 1, 0, -1, 0};
    for (int i = 0; i < 4; i++)
    {
        int nx = arr[i] + x;
        int ny = arr[i + 1] + y;

        if (nx < 0 || ny < 0 || nx >= n || ny >= m || visited[nx][ny] || graph[nx][ny] != '.')
            continue;
        visited[nx][ny] = true;
        markConnected(graph, nx, ny, n, m);
    }
    return;
}

void solve()
{
    int n;
    int m;
    cin >> n >> m;
    visited.assign(n, vector<bool>(m, false));
    vector<vector<char>> graph(n, vector<char>(m));
    int count = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> graph[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (graph[i][j] == '.' && !visited[i][j])
            {
                count++;
                markConnected(graph, i, j, n, m);
            }

    cout << count << endl;
}

int main()
{
    solve();

    return 0;
}