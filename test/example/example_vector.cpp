#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> g(n, vector<int>(n, INT_MAX / 2));
        vector<vector<int>> visited(n, vector<int>(n, false));
        for (auto &edge : edges) {
            int i = edge[0], j = edge[1], dis = edge[2];
            g[i][j] = dis;
            g[j][i] = dis;
        }
        for (int i = 0; i < n; i++) {
            vector<int> dist = dijkstra(g, i);
        }

        return 3;
    }

    vector<int> dijkstra(const vector<vector<int>> &g, int s) {
        int n = g.size();
        vector<int> dist(n, INT_MAX / 2);
        vector<int> visited(n, false);

        dist[s] = 0;
        // Iterate n loops
        for (int i = 0; i < n; i++) {
            // 1. find current least distance point
            int t = -1;
            for (int k = 0; k < n; k++) {
                if (!visited[k] && (t == -1 || dist[k] < dist[t])) {
                    t = k;
                }
            }
            // 2. update other nodes distance using this chosen point
            for (int k = 0; k < n; k++) {
                dist[k] = min(dist[k], dist[t] + g[t][k]);
            }

            // 3. move out the chosen point
            visited[t] = true;
        }

        // Print out the result
        for (int i = 0; i < ) {
            cout << dist[i] << " ";
        }
        cout << endl;
        return dist;
    }
};




