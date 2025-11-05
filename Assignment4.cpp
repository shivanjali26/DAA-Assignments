/*
NAME:-SHIVANJALI SANDIP BHOSALE.
PRN:-123B1F009.
*/
/*
Scenario: Smart Traffic Management for Emergency Vehicles
A smart city is implementing an intelligent traffic management system to assist ambulances
in reaching hospitals as quickly as possible. The city’s road network is represented as a
graph, where:
● Intersections (junctions) are nodes.
● Roads between intersections are edges with weights representing travel time (in minutes)
considering traffic congestion.
An ambulance is currently at Source (S) and needs to reach the nearest hospital (Destination
D) in the shortest possible time. Due to dynamic traffic conditions, the weight of each road
segment may change in real time.
As a transportation engineer, you are assigned to:
1. Implement Dijkstra’s algorithm to find the shortest path from the ambulance's current
location (S) to all possible hospitals.
2. Account for dynamic weight updates as traffic conditions change.
3. Optimize the system to work efficiently for a large city with thousands of intersections
and roads.
4. Provide a visual representation of the optimal path for navigation.
Expected Outcome:
The system should suggest the quickest route for the ambulance, updating dynamically
based on real-time traffic conditions, ensuring minimal response time to emergencies.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const double INF = 1e9;

// Structure for road
struct Road
{
    int to;
    double travelTime;
};

// Graph representing the city
class CityGraph
{
public:
    int intersections;
    vector<vector<Road>> adj;

    CityGraph(int n)
    {
        intersections = n;
        adj.resize(n);
    }

    void addRoad(int u, int v, double time)
    {
        adj[u].push_back({v, time});
        adj[v].push_back({u, time});
    }

    void updateRoad(int u, int v, double newTime)
    {
        for (auto &r : adj[u])
            if (r.to == v)
                r.travelTime = newTime;
        for (auto &r : adj[v])
            if (r.to == u)
                r.travelTime = newTime;
    }
};

// Dijkstra's algorithm
pair<vector<double>, vector<int>> dijkstra(CityGraph &city, int source)
{
    int V = city.intersections;
    vector<double> dist(V, INF);
    vector<int> parent(V, -1);
    dist[source] = 0;

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    pq.push({0, source});

    while (!pq.empty())
    {
        pair<double, int> top = pq.top();
        pq.pop();
        double d = top.first;
        int u = top.second;

        if (d > dist[u])
            continue;

        for (auto &r : city.adj[u])
        {
            int v = r.to;
            double w = r.travelTime;

            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return {dist, parent};
}

// Reconstruct path
vector<int> reconstructPath(int dest, const vector<int> &parent)
{
    vector<int> path;
    for (int v = dest; v != -1; v = parent[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    int V, E;
    cout << "Enter number of intersections and roads: ";
    cin >> V >> E;

    CityGraph city(V);

    cout << "Enter roads (u v travel_time):\n";
    for (int i = 0; i < E; i++)
    {
        int u, v;
        double w;
        cin >> u >> v >> w;
        city.addRoad(u, v, w);
    }

    int source;
    cout << "Enter ambulance starting intersection: ";
    cin >> source;

    int H;
    cout << "Enter number of hospitals: ";
    cin >> H;
    vector<int> hospitals(H);
    cout << "Enter hospital intersections:\n";
    for (int i = 0; i < H; i++)
        cin >> hospitals[i];

    // First Dijkstra run
    auto result = dijkstra(city, source);
    vector<double> dist = result.first;
    vector<int> parent = result.second;

    int nearestHospital = -1;
    double minTime = INF;
    for (int h : hospitals)
    {
        if (dist[h] < minTime)
        {
            minTime = dist[h];
            nearestHospital = h;
        }
    }

    cout << "\nBefore traffic update:\n";
    cout << "Nearest hospital: " << nearestHospital
         << " (Travel time: " << minTime << " minutes)\n";
    vector<int> path = reconstructPath(nearestHospital, parent);
    cout << "Optimal path: ";
    for (int node : path)
        cout << node << " ";
    cout << endl;

    // Traffic update
    cout << "\nEnter road to update travel time (u v new_time), or -1 to skip: ";
    int u, v;
    double newTime;
    cin >> u;
    if (u != -1)
    {
        cin >> v >> newTime;
        city.updateRoad(u, v, newTime);

        // Recompute
        result = dijkstra(city, source);
        dist = result.first;
        parent = result.second;

        nearestHospital = -1;
        minTime = INF;
        for (int h : hospitals)
        {
            if (dist[h] < minTime)
            {
                minTime = dist[h];
                nearestHospital = h;
            }
        }

        cout << "\nAfter traffic update:\n";
        cout << "Nearest hospital: " << nearestHospital
             << " (Travel time: " << minTime << " minutes)\n";
        path = reconstructPath(nearestHospital, parent);
        cout << "Optimal path: ";
        for (int node : path)
            cout << node << " ";
        cout << endl;
    }

    return 0;
}


