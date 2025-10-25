#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int x, y;
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> graph(n, vector<char>(m));
    queue<Node> q;
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    vector<vector<char>> moveDir(n, vector<char>(m));

    int startX, startY, endX, endY;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> graph[i][j];
            if (graph[i][j] == 'A')
            {
                startX = i;
                startY = j;
            }
            if (graph[i][j] == 'B')
            {
                endX = i;
                endY = j;
            }
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
    char dir[] = {'U', 'R', 'D', 'L'};

    q.push({startX, startY});
    visited[startX][startY] = true;

    bool found = false;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        if (x == endX && y == endY)
        {
            found = true;
            break;
        }

        for (int k = 0; k < 4; k++)
        {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                continue;
            if (graph[nx][ny] == '#' || visited[nx][ny])
                continue;

            visited[nx][ny] = true;
            parent[nx][ny] = {x, y};
            moveDir[nx][ny] = dir[k];
            q.push({nx, ny});
        }
    }

    if (!found)
    {
        cout << "NO\n";
        return;
    }

    // reconstruct path
    string path;
    int cx = endX, cy = endY;
    while (!(cx == startX && cy == startY))
    {
        path.push_back(moveDir[cx][cy]);
        auto [px, py] = parent[cx][cy];
        cx = px;
        cy = py;
    }
    reverse(path.begin(), path.end());

    cout << "YES\n";
    cout << path.size() << "\n";
    cout << path << "\n";
}

int main()
{
    solve();
}
