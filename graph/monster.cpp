#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<char>> graph;
vector<vector<int>> monster;
vector<vector<int>> dist;
vector<vector<pair<int, int>>> parent;
vector<int> dx = {0, 1, 0, -1};
vector<int> dy = {1, 0, -1, 0};
string dir = "RDLU";

bool isValid(int x, int y)
{
    return x >= 0 && y >= 0 && x < n && y < m && graph[x][y] != '#';
}

void bfsMonster(queue<pair<int, int>> &q)
{
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k], ny = y + dy[k];
            if (isValid(nx, ny) && monster[nx][ny] > monster[x][y] + 1)
            {
                monster[nx][ny] = monster[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

void bfsPlayer(pair<int, int> start)
{
    queue<pair<int, int>> q;
    q.push(start);
    dist[start.first][start.second] = 0;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();

        if (x == 0 || y == 0 || x == n - 1 || y == m - 1)
        {
            cout << "YES\n";
            string path = "";
            while (parent[x][y] != make_pair(-1, -1))
            {
                auto [px, py] = parent[x][y];
                for (int k = 0; k < 4; k++)
                    if (px + dx[k] == x && py + dy[k] == y)
                        path += dir[k];
                x = px;
                y = py;
            }
            reverse(path.begin(), path.end());
            cout << path.size() << "\n"
                 << path << "\n";
            return;
        }

        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k], ny = y + dy[k];
            if (isValid(nx, ny) && dist[nx][ny] == INT_MAX && dist[x][y] + 1 < monster[nx][ny])
            {
                dist[nx][ny] = dist[x][y] + 1;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }

    cout << "NO\n";
}

void solve()
{
    cin >> n >> m;
    graph.assign(n, vector<char>(m));
    monster.assign(n, vector<int>(m, INT_MAX));
    dist.assign(n, vector<int>(m, INT_MAX));
    parent.assign(n, vector<pair<int, int>>(m, {-1, -1}));

    pair<int, int> start;
    queue<pair<int, int>> q;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> graph[i][j];
            if (graph[i][j] == 'M')
            {
                monster[i][j] = 0;
                q.push({i, j});
            }
            else if (graph[i][j] == 'A')
                start = {i, j};
        }
    }

    bfsMonster(q);
    bfsPlayer(start);
}

int main()
{
    solve();
    return 0;
}
