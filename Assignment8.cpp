/*
NAME:-SHIVANJALI SANDIP BHOSALE.
PRN:-123B1F009.
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Node
{
    int level;
    int pathCost;
    int reducedCost;
    int vertex;
    vector<int> path;
    vector<vector<int>> reducedMatrix;

    Node(int n)
    {
        reducedMatrix.assign(n, vector<int>(n));
    }
};

struct Compare
{
    bool operator()(const Node &a, const Node &b)
    {
        return a.reducedCost > b.reducedCost;
    }
};

void copyMatrix(const vector<vector<int>> &src, vector<vector<int>> &dest)
{
    for (int i = 0; i < src.size(); i++)
        for (int j = 0; j < src.size(); j++)
            dest[i][j] = src[i][j];
}

int reduceMatrix(vector<vector<int>> &matrix, int n)
{
    int reductionCost = 0;

    for (int i = 0; i < n; i++)
    {
        int rowMin = INF;
        for (int j = 0; j < n; j++)
            rowMin = min(rowMin, matrix[i][j]);

        if (rowMin != INF && rowMin > 0)
        {
            reductionCost += rowMin;
            for (int j = 0; j < n; j++)
                if (matrix[i][j] != INF)
                    matrix[i][j] -= rowMin;
        }
    }

    for (int j = 0; j < n; j++)
    {
        int colMin = INF;
        for (int i = 0; i < n; i++)
            colMin = min(colMin, matrix[i][j]);

        if (colMin != INF && colMin > 0)
        {
            reductionCost += colMin;
            for (int i = 0; i < n; i++)
                if (matrix[i][j] != INF)
                    matrix[i][j] -= colMin;
        }
    }

    return reductionCost;
}

Node createNode(vector<vector<int>> parentMatrix, vector<int> path,
                int level, int i, int j, int n)
{

    Node node(n);
    copyMatrix(parentMatrix, node.reducedMatrix);

    for (int k = 0; k < n; k++)
        node.reducedMatrix[i][k] = INF;

    for (int k = 0; k < n; k++)
        node.reducedMatrix[k][j] = INF;

    if (level + 1 < n)
        node.reducedMatrix[j][0] = INF;

    node.path = path;
    node.path.push_back(j);
    node.level = level;
    node.vertex = j;

    return node;
}

void solveTSP(vector<vector<int>> costMatrix, int n)
{

    priority_queue<Node, vector<Node>, Compare> pq;

    vector<int> path = {0};

    Node root(n);
    copyMatrix(costMatrix, root.reducedMatrix);

    root.path = path;
    root.level = 0;
    root.vertex = 0;
    root.pathCost = 0;

    root.reducedCost = reduceMatrix(root.reducedMatrix, n);
    pq.push(root);

    int minCost = INF;
    vector<int> finalPath;

    while (!pq.empty())
    {
        Node min = pq.top();
        pq.pop();

        int i = min.vertex;

        if (min.level == n - 1)
        {
            min.path.push_back(0);
            int totalCost = min.pathCost + costMatrix[i][0];

            if (totalCost < minCost)
            {
                minCost = totalCost;
                finalPath = min.path;
            }
            continue;
        }

        for (int j = 0; j < n; j++)
        {
            if (min.reducedMatrix[i][j] != INF)
            {
                Node child = createNode(min.reducedMatrix, min.path,
                                        min.level + 1, i, j, n);

                child.pathCost = min.pathCost + costMatrix[i][j];
                child.reducedCost =
                    child.pathCost + reduceMatrix(child.reducedMatrix, n);

                pq.push(child);
            }
        }
    }

    cout << "\nOptimal Delivery Route (SwiftShip): ";
    for (int x : finalPath)
        cout << x << " ";
    cout << "\nMinimum Total Delivery Cost: " << minCost << "\n";
}

int main()
{
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> costMatrix(n, vector<int>(n));

    cout << "Enter cost matrix (use large number for no direct route):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> costMatrix[i][j];

    solveTSP(costMatrix, n);
    return 0;
}

