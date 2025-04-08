#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <set>
using namespace std;

const int MAX = 100;

vector<int> graph[MAX];
int shortestDist[MAX];
vector<vector<int>> validPaths;
int D; // shortest distance from S to F

void bfs(int S, int F, int n) {
    fill(shortestDist, shortestDist + n + 1, -1);
    queue<int> q;
    q.push(S);
    shortestDist[S] = 0;

    while (!q.empty()) {
        int curr = q.front(); q.pop();
        for (int neighbor : graph[curr]) {
            if (shortestDist[neighbor] == -1) {
                shortestDist[neighbor] = shortestDist[curr] + 1;
                q.push(neighbor);
            }
        }
    }
    D = shortestDist[F];
}

// DFS to find all valid paths from S to F
void dfs(int node, int F, int length, vector<int>& path, set<pair<int, int>>& usedEdges) {
    if (length > D + 1) return;
    if (node == F) {
        if (length == D || length == D + 1)
            validPaths.push_back(path);
        return;
    }

    for (int neighbor : graph[node]) {
        pair<int, int> edge = {min(node, neighbor), max(node, neighbor)};
        if (find(path.begin(), path.end(), neighbor) == path.end()) { // avoid cycles
            path.push_back(neighbor);
            usedEdges.insert(edge);
            dfs(neighbor, F, length + 1, path, usedEdges);
            path.pop_back();
            usedEdges.erase(edge);
        }
    }
}

int main() {
    int n, m;
    cout << "Enter number of cities and roads: ";
    cin >> n >> m;

    cout << "Enter roads (e.g., 1 2):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // undirected
    }

    int S, F;
    cout << "Enter Start City (S) and Final City (F): ";
    cin >> S >> F;

    bfs(S, F, n);

    if (D == -1) {
        cout << "No route from " << S << " to " << F << endl;
        return 0;
    }

    vector<int> path = {S};
    set<pair<int, int>> usedEdges;
    dfs(S, F, 0, path, usedEdges);

    cout << "\nValid routes from " << S << " to " << F << " (length " << D << " or " << D + 1 << "):\n";
    for (auto& p : validPaths) {
        for (int city : p)
            cout << city << " ";
        cout << endl;
    }

    cout << "\nTotal valid unique routes: " << validPaths.size() << endl;

    return 0;
}
