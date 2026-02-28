#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm>
using namespace std;

struct Node {
    int x, y, dist;
};

int row[] = {-1, 0, 0, 1};
int col[] = {0, -1, 1, 0};

bool isValid(vector<vector<int>> const &maze, vector<vector<bool>> &visited, int r, int c) {
    int M = maze.size();
    int N = maze[0].size();
    return (r >= 0 && r < M) && (c >= 0 && c < N) && maze[r][c] == 1 && !visited[r][c];
}

vector<pair<int, int>> findTheShortestPath(vector<vector<int>> const &maze, pair<int, int> &src, pair<int, int> &dest) {
    if (maze.empty() || maze[src.first][src.second] == 0) {
        return {}; // 返回一个空的路径
    }
    
    int M = maze.size();
    int N = maze[0].size();

    vector<vector<bool>> visited(M, vector<bool>(N, false));
    vector<vector<pair<int, int>> > parent(M, vector<pair<int, int>>(N, make_pair(-1, -1)));

    queue<Node> q;

    int i = src.first;
    int j = src.second;

    visited[i][j] = true;
    q.push({i, j, 0});

    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        
        int i = node.x, j = node.y, dist = node.dist;

        if (i == dest.first && j == dest.second) {
            // 找到最短路径后，通过 parent 矩阵回溯路径
            vector<pair<int, int>> path;
            while (i != -1 && j != -1) {
                path.push_back(make_pair(i, j));
                int new_i = parent[i][j].first;
                int new_j = parent[i][j].second;
                i = new_i;
                j = new_j;
            }
            reverse(path.begin(), path.end()); // 倒转路径
            return path;
        }

        for (int k = 0; k < 4; k++) {
            if (isValid(maze, visited, i + row[k], j + col[k])) {
                visited[i + row[k]][j + col[k]] = true;
                parent[i + row[k]][j + col[k]] = make_pair(i, j); // 记录父节点
                q.push({i + row[k], j + col[k], dist + 1});
            }
        }
    }
    
    return {}; // 没有找到路径，返回一个空的路径
}
