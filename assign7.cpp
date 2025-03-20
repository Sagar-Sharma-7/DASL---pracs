#include "bits/stdc++.h"
using namespace std;

// dsu
int find_set(int v, vector<int>& parent) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v], parent);
}

void union_set(int a, int b, vector<int>& parent) {
    a = find_set(a, parent);
    b = find_set(b, parent);
    if (a != b)
        parent[b] = a;
}

class Graph {
    int n; 
    vector<vector<int>> weight; // Adjacency matrix for storing costs between offices
    
public:
    Graph(int size) {
        n = size;
        weight.resize(n, vector<int>(n, INT_MAX));
    }
    
    void addEdge(int u, int v, int wt) {
        weight[u][v] = wt;
        weight[v][u] = wt;
    }

    void display() {
        cout << "Cost Matrix (Phone line costs):\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (weight[i][j] == INT_MAX)
                    cout << "-1 ";
                else
                    cout << weight[i][j] << " ";
            }
            cout << "\n";
        }
    }

    // Prim's Algorithm (for Minimum Spanning Tree)
    void prims() {
        vector<int> parent(n, -1);
        vector<int> key(n, INT_MAX);
        vector<bool> inMST(n, false);
        key[0] = 0; // Starting with the first office (0-indexed)
        
        for (int count = 0; count < n - 1; count++) {
            int u = -1;
            // Find the vertex with the minimum key value that is not in MST
            for (int v = 0; v < n; v++) {
                if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }

            inMST[u] = true;

            // Update the key values of adjacent vertices of the selected vertex
            for (int v = 0; v < n; v++) {
                if (weight[u][v] != INT_MAX && !inMST[v] && weight[u][v] < key[v]) {
                    key[v] = weight[u][v];
                    parent[v] = u;
                }
            }
        }

        // Output the edges of the MST
        cout << "Minimum Spanning Tree (using Prim's Algorithm):\n";
        int total_cost = 0;
        for (int i = 1; i < n; i++) {
            cout << "Office " << parent[i] << " - Office " << i << " : Cost = " << weight[i][parent[i]] << "\n";
            total_cost += weight[i][parent[i]];
        }
        cout << "Total Cost: " << total_cost << "\n";
    }

    // Kruskal's Algorithm (for Minimum Spanning Tree)
    void kruskals() {
        vector<pair<int, pair<int, int>>> edges;
        vector<int> parent(n);
        
        // Initialize disjoint set
        for (int i = 0; i < n; i++) parent[i] = i;
        
        // Store all edges
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (weight[i][j] != INT_MAX) {
                    edges.push_back({weight[i][j], {i, j}});
                }
            }
        }
        
        // Sort edges by weight
        sort(edges.begin(), edges.end());

        int total_cost = 0;
        cout << "Minimum Spanning Tree (using Kruskal's Algorithm):\n";
        
        // Apply Kruskal's algorithm
        for (auto& edge : edges) {
            int wt = edge.first;
            int u = edge.second.first;
            int v = edge.second.second;
            
            // If including this edge doesn't form a cycle
            if (find_set(u, parent) != find_set(v, parent)) {
                union_set(u, v, parent);
                cout << "Office " << u << " - Office " << v << " : Cost = " << wt << "\n";
                total_cost += wt;
            }
        }

        cout << "Total Cost: " << total_cost << "\n";
    }
};

int main() {
    int n; 
    cout << "Enter the number of offices: ";
    cin >> n;

    Graph graph(n);

    while (true) {
        int choice;
        cout << "\n----------------- Main Menu -----------------\n";
        cout << "1. Add Edge (Add Phone Line)\n";
        cout << "2. Display Cost Matrix\n";
        cout << "3. Prim's Algorithm (Minimum Cost Network)\n";
        cout << "4. Kruskal's Algorithm (Minimum Cost Network)\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: "; 
        cin >> choice;

        switch (choice) {
            case 1: {
                int u, v, wt;
                cout << "Enter the first office (0-indexed): "; cin >> u;
                cout << "Enter the second office (0-indexed): "; cin >> v;
                cout << "Enter the cost to connect these offices: "; cin >> wt;
                graph.addEdge(u, v, wt);
                break;
            }
            case 2: {
                graph.display();
                break;
            }
            case 3: {
                graph.prims();
                break;
            }
            case 4: {
                graph.kruskals();
                break;
            }
            case 5:
                return 0;
        }
    }

    return 0;
}
