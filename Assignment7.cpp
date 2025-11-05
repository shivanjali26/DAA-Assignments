/*
NAME:-SHIVANJALI SANDIP BHOSALE.
PRN:-123B1F009.
*/
#include <bits/stdc++.h>
using namespace std;

class ExamScheduler
{
private:
    int numCourses;
    vector<vector<int>> adj; 
    vector<int> color;       
    vector<int> courseSize;  

public:
    ExamScheduler(int n) : numCourses(n)
    {
        adj.resize(n);
        color.assign(n, -1);
        courseSize.assign(n, 0);
    }

   
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

 
    void setCourseSize(int course, int size)
    {
        courseSize[course] = size;
    }

    // 1. GREEDY COLORING 
    int greedyColoring()
    {
        color.assign(numCourses, -1);
        vector<bool> available(numCourses, false);

        color[0] = 0;

        for (int u = 1; u < numCourses; u++)
        {
            fill(available.begin(), available.end(), false);

            for (int v : adj[u])
            {
                if (color[v] != -1)
                    available[color[v]] = true;
            }

            int c = 0;
            while (c < numCourses && available[c])
                c++;
            color[u] = c;
        }
        return *max_element(color.begin(), color.end()) + 1;
    }

    // 2. WELSH–POWELL ALGORITHM 
    int welshPowellColoring()
    {
        color.assign(numCourses, -1);

        vector<int> order(numCourses);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b)
             { return adj[a].size() > adj[b].size(); });

        int numColors = 0;
        for (int u : order)
        {
            vector<bool> used(numCourses, false);

            for (int v : adj[u])
                if (color[v] != -1)
                    used[color[v]] = true;

            int c = 0;
            while (c < numCourses && used[c])
                c++;
            color[u] = c;
            numColors = max(numColors, c + 1);
        }
        return numColors;
    }

    // 3. DSATUR ALGORITHM 
    int dsaturColoring()
    {
        color.assign(numCourses, -1);
        vector<int> degree(numCourses);

        vector<unordered_set<int>> neighborColors(numCourses);

        for (int i = 0; i < numCourses; i++)
            degree[i] = adj[i].size();

        int coloredCount = 0;

        int u = max_element(degree.begin(), degree.end()) - degree.begin();
        color[u] = 0;
        coloredCount++;

        while (coloredCount < numCourses)
        {

            for (int v : adj[u])
            {
                if (color[v] != -1)
                    neighborColors[v].insert(color[u]);
            }

            int next = -1, maxSat = -1, maxDeg = -1;
            for (int i = 0; i < numCourses; i++)
            {
                if (color[i] != -1)
                    continue;
                int sat = neighborColors[i].size();
                if (sat > maxSat || (sat == maxSat && degree[i] > maxDeg))
                {
                    maxSat = sat;
                    maxDeg = degree[i];
                    next = i;
                }
            }

            vector<bool> used(numCourses, false);
            for (int v : adj[next])
                if (color[v] != -1)
                    used[color[v]] = true;

            int c = 0;
            while (c < numCourses && used[c])
                c++;
            color[next] = c;

            u = next;
            coloredCount++;
        }

        return *max_element(color.begin(), color.end()) + 1;
    }

    // ROOM ALLOCATION 
    void allocateRooms(int numRooms, int roomCapacity)
    {
        int numSlots = *max_element(color.begin(), color.end()) + 1;
        vector<vector<int>> slotCourses(numSlots);

        for (int i = 0; i < numCourses; i++)
            slotCourses[color[i]].push_back(i);

        cout << "\n Exam Room Allocation \n";
        for (int s = 0; s < numSlots; s++)
        {
            cout << "\nSlot " << s << ":\n";

            int currentRoom = 1;
            int usedCapacity = 0;

            for (int course : slotCourses[s])
            {

                if (usedCapacity + courseSize[course] > roomCapacity)
                {
                    currentRoom++;
                    usedCapacity = 0;
                }

                usedCapacity += courseSize[course];

                cout << "  Room " << currentRoom
                     << " -> Course " << course
                     << " (" << courseSize[course] << " students)\n";
            }
        }
    }
};

// ----------------- DRIVER CODE -----------------
int main()
{
    int n = 6; // example course count
    ExamScheduler scheduler(n);

    // Conflicts (edges)
    scheduler.addEdge(0, 1);
    scheduler.addEdge(0, 2);
    scheduler.addEdge(1, 2);
    scheduler.addEdge(1, 3);
    scheduler.addEdge(3, 4);
    scheduler.addEdge(4, 5);

    // Course sizes
    scheduler.setCourseSize(0, 80);
    scheduler.setCourseSize(1, 50);
    scheduler.setCourseSize(2, 40);
    scheduler.setCourseSize(3, 60);
    scheduler.setCourseSize(4, 90);
    scheduler.setCourseSize(5, 30);

    cout << "Greedy Coloring -> " << scheduler.greedyColoring() << " slots\n";
    cout << "Welsh - Powell Coloring -> " << scheduler.welshPowellColoring() << " slots\n";
    cout << "DSATUR Coloring -> " << scheduler.dsaturColoring() << " slots\n";

    scheduler.allocateRooms(3, 100);

    return 0;
}

