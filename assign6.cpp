// assignment - 6: depth first and breadth first

/*
 Write a program to represent input graph using adjacency matrix. 
 * Implement Depth First and breadth first traversal algorithms. 
 * Check if graph is connected, if not find how many connected components it has.
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
    int n; 
    vector<vector<int>> adjMatrix; 
    vector<bool> visited; 
    
public:
    
    Graph(int size) {
        n = size;
        adjMatrix.resize(n, vector<int>(n, 0)); 
        visited.resize(n, false); 
    }

    
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }
    void clear_visited(){
        for (int i = 0; i < n; i++)
            visited[i] = false;
        return;
    }

    void dfs(int vertex) {
        visited[vertex] = true;
        cout << vertex << " ";
        for (int i = 0; i < n; i++) {
            if (adjMatrix[vertex][i] == 1 && !visited[i]) {
                dfs(i);
            }
        }
    }

    // Perform BFS traversal starting from vertex
    void bfs(int vertex) {
        queue<int> q;
        q.push(vertex);
        visited[vertex] = true;
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << curr << " ";
            for (int i = 0; i < n; i++) {
                if (adjMatrix[curr][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }


    bool isConnected() {
        fill(visited.begin(), visited.end(), false); // Reset visited array
        dfs(0); 
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                return false; // If any vertex is not visited, the graph is disconnected
            }
        }
        return true;
    }

    int countConnectedComponents() {
        fill(visited.begin(), visited.end(), false); // Reset visited array
        int components = 0;
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(i); // Perform DFS from unvisited node
                components++;
            }
        }
        return components;
    }

    void display() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    Graph g(n);

    while (true) {
        int choice;
        cout << "\n1. Add Edge\n2. Display Graph\n3. DFS\n4. BFS\n5. Check if Graph is Connected\n6. Count Connected Components\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int u, v;
                cout << "Enter first node: ";
                cin >> u;
                cout << "Enter second node: ";
                cin >> v;
                g.addEdge(u, v);
                break;
            }
            case 2:
                g.display();
                break;
            case 3: {
                int vertex;
                cout << "Enter the root vertex for DFS: ";
                cin >> vertex;
                g.clear_visited();
                g.dfs(vertex);
                cout << endl;
                break;
            }
            case 4: {
                int vertex;
                cout << "Enter the root vertex for BFS: ";
                cin >> vertex;
                g.clear_visited();
                g.bfs(vertex);
                cout << endl;
                break;
            }
            case 5:
                if (g.isConnected()) {
                    cout << "The graph is connected!\n";
                } else {
                    cout << "The graph is not connected!\n";
                }
                break;
            case 6:
                cout << "Number of connected components: " << g.countConnectedComponents() << endl;
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
