/*
NAME:-SHIVANJALI SANDIP BHOSALE.
PRN:-123B1F009.
*/
/*
Scenario:
A logistics company, SwiftCargo, specializes in delivering packages across multiple cities.
To optimize its delivery process, the company divides the transportation network into
multiple stages (warehouses, transit hubs, and final delivery points). Each package must
follow the most cost-efficient or fastest route from the source to the destination while
passing through these predefined stages.
As a logistics optimization engineer, you must:
1. Model the transportation network as a directed, weighted multistage graph with
multiple intermediate stages.
2. Implement an efficient algorithm (such as Dynamic Programming or Dijkstra’s
Algorithm) to find the optimal delivery route.
3. Ensure that the algorithm scales for large datasets (handling thousands of cities and
routes).

T.Y. B.Tech Information Technology, PCCoE Pune Page 10
4. Analyze and optimize route selection based on real-time constraints, such as traffic
conditions, weather delays, or fuel efficiency.
Constraints & Considerations:
● The network is structured into N stages, and every package must pass through at least
one node in each stage.
● There may be multiple paths with different costs/times between stages.
● The algorithm should be flexible enough to handle real-time changes (e.g., road
closures or rerouting requirements).
● The system should support batch processing for multiple delivery requests.
*/
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const double INF = 1e9;

// Structure to represent a weighted edge
struct Edge
{
    int to;
    double cost;
};

// Function to find the minimum cost path through multistage graph
pair<double, vector<int>> multistageOptimalPath(
    const vector<vector<vector<Edge>>> &stages)
{

    int N = stages.size();         // number of stages
    vector<vector<double>> dp(N);  // dp[i][j] = min cost to reach node j in stage i
    vector<vector<int>> parent(N); // parent[i][j] = node in stage i-1 giving min cost

    // Initialize DP for stage 0
    int stage0_size = stages[0].size();
    dp[0].resize(stage0_size, 0);
    parent[0].resize(stage0_size, -1);

    // Fill DP for subsequent stages
    for (int i = 1; i < N; i++)
    {
        int stage_size = stages[i].size();
        dp[i].resize(stage_size, INF);
        parent[i].resize(stage_size, -1);

        for (int j = 0; j < stage_size; j++)
        {
            // Check all edges coming from previous stage
            for (int k = 0; k < stages[i - 1].size(); k++)
            {
                for (auto &e : stages[i - 1][k])
                {
                    if (e.to == j)
                    {
                        double cost = dp[i - 1][k] + e.cost;
                        if (cost < dp[i][j])
                        {
                            dp[i][j] = cost;
                            parent[i][j] = k;
                        }
                    }
                }
            }
        }
    }

    // Find minimum cost in last stage
    double minCost = INF;
    int lastNode = -1;
    for (int i = 0; i < dp[N - 1].size(); i++)
    {
        if (dp[N - 1][i] < minCost)
        {
            minCost = dp[N - 1][i];
            lastNode = i;
        }
    }

    // Reconstruct path
    vector<int> path(N);
    int node = lastNode;
    for (int i = N - 1; i >= 0; i--)
    {
        path[i] = node;
        node = parent[i][node];
    }

    return {minCost, path};
}

int main()
{
    int stages_count;
    cout << "Enter number of stages: ";
    cin >> stages_count;

    vector<vector<vector<Edge>>> stages(stages_count);

    // Input number of nodes and edges for each stage
    for (int i = 0; i < stages_count; i++)
    {
        int nodes;
        cout << "Enter number of nodes in stage " << i + 1 << ": ";
        cin >> nodes;
        stages[i].resize(nodes);

        if (i == stages_count - 1)
            continue; // last stage has no outgoing edges

        for (int j = 0; j < nodes; j++)
        {
            int edges;
            cout << "Enter number of outgoing edges from node " << j
                 << " in stage " << i + 1 << ": ";
            cin >> edges;

            for (int k = 0; k < edges; k++)
            {
                int to;
                double cost;
                cout << "  Edge to node in next stage (0-based index) and cost: ";
                cin >> to >> cost;
                stages[i][j].push_back({to, cost});
            }
        }
    }

    // Compute optimal path
    auto result = multistageOptimalPath(stages);
    double minCost = result.first;
    vector<int> path = result.second;

    cout << "\nOptimal path through stages (0-based node indices): ";
    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i] << " ";
    }
    cout << "\nMinimum cost: " << minCost << endl;

    return 0;
}


