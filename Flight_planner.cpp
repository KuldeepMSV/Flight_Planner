#include <bits/stdc++.h>

using namespace std;

class FlightPlanner {
private:
    unordered_map<string, vector<pair<string, int>>> graph;

public:
    void addFlight(const string& from, const string& to, int cost) {
        graph[from].push_back({to, cost});
        graph[to].push_back({from, cost}); // Assuming bidirectional flights
    }

    void dijkstra(const string& start) {
        unordered_map<string, int> minCost;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;
        
        for (const auto& city : graph) {
            minCost[city.first] = numeric_limits<int>::max();
        }
        
        minCost[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            auto it = pq.top();
            int cost = it.first;
            string city = it.second;
            pq.pop();
            
            if (cost > minCost[city]) continue;
            
            for (const auto& [neighbor, flightCost] : graph[city]) {
                int newCost = cost + flightCost;
                if (newCost < minCost[neighbor]) {
                    minCost[neighbor] = newCost;
                    pq.push({newCost, neighbor});
                }
            }
        }
        
        for (const auto& [city, cost] : minCost) {
            cout << "Minimum cost to " << city << " from " << start << " is " << cost << "\n";
        }
    }

    void bfs(const string& start) {
        queue<string> q;
        unordered_map<string, bool> visited;
        
        q.push(start);
        visited[start] = true;
        
        while (!q.empty()) {
            string city = q.front();
            q.pop();
            cout << city << " -> ";
            
            for (const auto& [neighbor, _] : graph[city]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "End\n";
    }
};

int main() {
    FlightPlanner planner;
    planner.addFlight("New York", "Los Angeles", 300);
    planner.addFlight("New York", "Chicago", 100);
    planner.addFlight("Chicago", "Los Angeles", 200);
    planner.addFlight("Los Angeles", "Houston", 250);
    planner.addFlight("Chicago", "Houston", 150);
    
    cout << "Dijkstra's Algorithm for minimum cost flights:\n";
    planner.dijkstra("New York");
    
    cout << "\nBFS Traversal of Cities:\n";
    planner.bfs("New York");
    
    return 0;
}