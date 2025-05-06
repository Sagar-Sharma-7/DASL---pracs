#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// Custom comparator for min-heap based on distance
class Compare {
public:
    bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.second > b.second;
    }
};

void dijkstra(int V, vector<vector<pair<int, int>>>& adj, int source) {
    vector<int> dist(V, INT_MAX);      // Distance from source
    vector<int> parent(V, -1);         // For path reconstruction
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;

    dist[source] = 0;
    pq.push({source, 0});  // {node, distance}

    while (!pq.empty()) {
        int u = pq.top().first;
        int d = pq.top().second;
        pq.pop();

        // Traverse all neighbors
        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }

    // Print shortest distances and paths
    cout << "\nShortest distances from source " << source << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "To " << i << " = " << dist[i] << ", Path: ";

        stack<int> path;
        for (int v = i; v != -1; v = parent[v])
            path.push(v);

        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
        cout << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<pair<int, int>>> adj(V); // {v, weight}

    cout << "Enter edges in format: u v weight\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        // If graph is undirected, uncomment this:
        // adj[v].push_back({u, w});
    }

    dijkstra(V, adj, 0); // Source = 0

    return 0;
}
