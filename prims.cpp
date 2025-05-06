#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Edge {
public:
    int weight;
    int node;
    int from;
    Edge(int w, int n, int f) {
        weight = w;
        node = n;
        from = f;
    }
};

// Custom comparator for min-heap
class Compare {
public:
    bool operator()(Edge a, Edge b) {
        return a.weight > b.weight;
    }
};

void primMST(int V, vector<vector<vector<int>>>& adj) {
    vector<bool> visited(V, false);
    priority_queue<Edge, vector<Edge>, Compare> pq;
    vector<pair<int, int>> mstEdges;
    int minCost = 0;

    pq.push(Edge(0, 0, -1));  // weight, node, from

    while (!pq.empty()) {
        Edge curr = pq.top();
        pq.pop();

        int u = curr.node;
        int wt = curr.weight;
        int from = curr.from;

        if (visited[u]) continue;

        visited[u] = true;
        minCost += wt;

        if (from != -1) {
            mstEdges.push_back({from, u});  // store real edge used
        }

        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i][0];
            int w = adj[u][i][1];
            if (!visited[v]) {
                pq.push(Edge(w, v, u));  // push with `from = u`
            }
        }
    }

    // Output
    cout << "\nMST Edges (u, v):\n";
    for (auto edge : mstEdges) {
        cout << "(" << edge.first << ", " << edge.second << ")\n";
    }

    cout << "Total Minimum Cost: " << minCost << endl;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<vector<int>>> adj(V);

    cout << "Enter edges in format: u v weight\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    primMST(V, adj);

    return 0;
}
