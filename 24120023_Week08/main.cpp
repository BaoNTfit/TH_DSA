#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <limits>
#include <queue>
#include <algorithm>
using namespace std;
vector<vector<int>> convertMatrixToList(const string &filename);
vector<vector<int>> convertListToMatrix(const string &filename);
bool isDirected(const vector<vector<int>> &adjMatrix);
int countVertices(const vector<vector<int>> &adjMatrix);
int countEdges(const vector<vector<int>> &adjMatrix);
vector<int> getIsolatedVertices(const vector<vector<int>> &adjMatrix);
bool isCompleteGraph(const vector<vector<int>> &adjMatrix);
bool isBipartite(const vector<vector<int>> &adjMatrix);
bool isCompleteBipartite(const vector<vector<int>> &adjMatrix);
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>> &adjMatrix);
vector<vector<int>> getComplementGraph(const vector<vector<int>> &adjMatrix);
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix);

void dfs(int v, const vector<vector<int>>& graph, vector<bool>& visited, vector<vector<int>>& tree);
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start);
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix);

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix);
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix);

vector<vector<int>> convertMatrixToList(const string &filename)
{
    vector<vector<int>> matrix;
    vector<vector<int>> list;
    int n;
    ifstream inp(filename);
    if (!inp.is_open()) {
    cerr << "Cannot open file: " << filename << endl;
    return {};
    }
    inp >> n;
    for (int j = 0; j < n; j++)
    {
        vector<int> line;  
        vector<int> index; 
        for (int i = 0; i < n; i++)
        {
            int temp;
            inp >> temp;
            line.push_back(temp);
            if (temp > 0)
                index.push_back(i);
        }
        matrix.push_back(line);
        list.push_back(index);
    }
    cout << list.size() << endl;
    for (vector<int> x : list)
    {
        cout << x.size() << " ";
        for (int i : x)
            cout << i << " ";
        cout << endl;
    }
    inp.close();
    return list;
}
vector<vector<int>> convertListToMatrix(const string &filename)
{
    vector<vector<int>> matrix;
    int n;
    ifstream inp(filename);
    if (!inp.is_open()) {
    cerr << "Cannot open file: " << filename << endl;
    return {};
    }
    inp >> n;
    for(int i = 0; i < n; i++) {
        int size;
        inp >> size;
        vector<int> line(n,0);
        while(size--){
            int index;
            inp >> index;
            if(index >= 0 && index < n) line[index] = 1;
        }
        matrix.push_back(line);
    }
    for(vector<int> x : matrix) {
        for (int i : x) {
            cout << i << " ";
        }
        cout << endl;
    }
    inp.close();
    return matrix;
}
bool isDirected(const vector<vector<int>> &adjMatrix)
{
    int n = adjMatrix.size();
    for (int i = 0; i < n;i ++) {
        for (int j = i+1; j < n;j++) {
            if(adjMatrix[i][j]!=adjMatrix[j][i]) return true;
        }
    }
    return false;
}
// Dem so luong dinh
int countVertices(const vector<vector<int>> &adjMatrix)
{
    return adjMatrix.size();
}
int countEdges(const vector<vector<int>> &adjMatrix)
{
    int n = adjMatrix.size();
    int count = 0;
    for(int i = 0;i < n; i++ ) {
        for (int j = 0; j < n; j++) count+= adjMatrix[i][j];
    }
    if(isDirected(adjMatrix) == false) count = count/2;
    return count;
}
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix){
    vector<int> ans;
    int n = adjMatrix.size();
    for(int i = 0; i < n; i++) {
        bool hasEdge = false;
        for(int j = 0; j < n; j++) {
            if(adjMatrix[i][j]!=0 || adjMatrix[j][i]!=0) {
                hasEdge = true;
                break;
            }
        }
        if(!hasEdge) ans.push_back(i);
    }
    return ans; 
}
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();

    for (int i = 0; i < n; i++) {
        if (adjMatrix[i][i] != 0) return false; 

        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            if (adjMatrix[i][j] != 1 || adjMatrix[j][i] != 1)
                return false; 
        }
    }
    return true;
}
bool isBipartite(const vector<vector<int>> &adjMatrix){
    int n = adjMatrix.size();
    vector<int> color(n, -1);  // -1: chưa tô màu, 0 và 1 là hai màu khác nhau

    for (int start = 0; start < n; ++start) {
        if (color[start] != -1) continue;

        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] == 0) continue;

                if (color[v] == -1) {
                    color[v] = 1 - color[u];  // tô màu khác với u
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;  // hai đỉnh kề nhau cùng màu → không phải đồ thị hai phía
                }
            }
        }
    }

    return true;
}
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<int> color(n, -1);  // -1: chưa tô màu, 0 và 1 là hai tập

    // Tô màu từng thành phần liên thông (nếu có nhiều)
    for (int start = 0; start < n; ++start) {
        if (color[start] != -1) continue;
        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        return false;  // Không phải đồ thị hai phía
                    }
                }
            }
        }
    }

    // Tập A = màu 0, Tập B = màu 1
    vector<int> A, B;
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) A.push_back(i);
        else B.push_back(i);
    }

    // Kiểm tra kết nối đầy đủ từ A sang B
    for (int u : A) {
        for (int v : B) {
            if (adjMatrix[u][v] == 0) return false;
        }
    }

    // Và từ B sang A (đối xứng trong đồ thị vô hướng)
    for (int u : B) {
        for (int v : A) {
            if (adjMatrix[u][v] == 0) return false;
        }
    }

    // Kiểm tra không có cạnh nội bộ trong A và trong B
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (color[i] == color[j] && adjMatrix[i][j] != 0) return false;
        }
    }

    return true;
}
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>> &adjMatrix){
    int n = adjMatrix.size();
    vector<vector<int>> res(n, vector<int>(n,0));
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(adjMatrix[i][j] == 1 || adjMatrix[j][i] == 1) {
                res[j][i] = res[i][j] = 1;
            }
        }
    }
    return res;
}
vector<vector<int>> getComplementGraph(const vector<vector<int>> &adjMatrix){
    int n = adjMatrix.size();
    vector<vector<int>> res(n,vector<int> (n,0));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjMatrix[i][j] == 0) {
                res[i][j] = res[j][i] = 1; // undirected graph
            }
        }
    }
    for(int i = 0; i < n; i++) {
        res[i][i] = 0;
    }
    return res;
}
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> graph = adjMatrix;
    vector<int> cycle;
    stack<int> st;
    st.push(0); 

    while (!st.empty()) {
        int v = st.top();
        bool hasEdge = false;
        for (int u = 0; u < n; ++u) {
            if (graph[v][u]) {
                // Remove the edge (v, u)
                graph[v][u] = graph[u][v] = 0;
                st.push(u);
                hasEdge = true;
                break;
            }
        }
        if (!hasEdge) {
            cycle.push_back(v);
            st.pop();
        }
    }

    return cycle;  // Cycle in reverse order
}
void dfs(int v, const vector<vector<int>>& graph, vector<bool>& visited, vector<vector<int>>& tree) {
    visited[v] = true;
    int n = graph.size();

    for (int u = 0; u < n; ++u) {
        if (graph[v][u] && !visited[u]) {
            tree[v][u] = tree[u][v] = 1;  // Undirected edge in spanning tree
            dfs(u, graph, visited, tree);
        }
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> spanningTree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);

    dfs(start, adjMatrix, visited, spanningTree);
    return spanningTree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> spanningTree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int v = q.front(); q.pop();

        for (int u = 0; u < n; ++u) {
            if (adjMatrix[v][u] && !visited[u]) {
                visited[u] = true;
                spanningTree[v][u] = spanningTree[u][v] = 1;  // Add undirected edge
                q.push(u);
            }
        }
    }

    return spanningTree;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;

    visited[u] = true;
    q.push(u);

    while (!q.empty()) {
        int curr = q.front(); q.pop();
        if (curr == v) return true;

        for (int i = 0; i < n; ++i) {
            if (adjMatrix[curr][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }

    return false;  
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1); 
    vector<bool> visited(n, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            int weight = adjMatrix[u][v];
            if (weight > 0 && !visited[v]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    vector<int> path;
    if (dist[end] == INT_MAX) return {}; // No path

    for (int v = end; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    return path;
}

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);

    dist[start] = 0;

    // Relax all edges (n - 1) times
    for (int k = 0; k < n - 1; ++k) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX) {
                    if (dist[u] + adjMatrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + adjMatrix[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
    }

    // (Optional) Detect negative weight cycles:
    // for (int u = 0; u < n; ++u) {
    //     for (int v = 0; v < n; ++v) {
    //         if (adjMatrix[u][v] != 0 && dist[u] != INT_MAX &&
    //             dist[u] + adjMatrix[u][v] < dist[v]) {
    //             // Negative cycle detected
    //             return {};
    //         }
    //     }
    // }

    // Reconstruct path
    vector<int> path;
    if (dist[end] == INT_MAX) return {}; // No path found

    for (int v = end; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());

    return path;
}