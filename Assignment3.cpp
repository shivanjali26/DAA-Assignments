/*
NAME:-SHIVANJALI SANDIP BHOSALE.
PRN:-123B1F009.
*/
/*Scenario : Emergency Relief Supply Distribution A devastating flood has hit multiple villages in a remote area,and the government,along with NGOs,is organizing an emergency relief operation.A rescue team has a limited - capacity boat that can carry a maximum weight of W kilograms.The boat must transport critical supplies,including food,medicine,and drinking water,from a relief center to the affected villages.Each type of relief item has :
● A weight(wi) in kilograms.
● Utility value(vi) indicating its importance(e.g., medicine has higher value than food).
● Some items can be divided into smaller portions(e.g., food and water), while others must be taken as a whole(e.g., medical kits).
As the logistics manager, you must : 
1. Implement the Fractional Knapsack algorithm to maximize the total utility value of the supplies transported.
2. Prioritize high - value items while considering weight constraints.
3. Allow partial selection of divisible items(e.g., carrying a fraction of food packets).
4. Ensure that the boat carries the most critical supplies given its weight limit W.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;


class ReliefItem
{
public:
    double weight;
    double utility; 
    bool divisible; 
    string name;    

    ReliefItem(string n, double w, double u, bool d)
        : name(n), weight(w), utility(u), divisible(d) {}

    double utilityPerWeight() const
    {
        return (weight == 0) ? 0 : (utility / weight);
    }
};

bool compareItems(const ReliefItem &a, const ReliefItem &b)
{
    return a.utilityPerWeight() > b.utilityPerWeight();
}

double fractionalKnapsack(double maxWeight, vector<ReliefItem> &items)
{
    sort(items.begin(), items.end(), compareItems);

    cout << fixed << setprecision(2);
    cout << "\nItems sorted by utility/weight ratio (descending):\n";
    cout << left << setw(12) << "Item"
         << setw(10) << "Weight"
         << setw(10) << "Utility"
         << setw(12) << "Divisible"
         << setw(15) << "Utility/Weight" << endl;
    for (const auto &item : items)
    {
        cout << left << setw(12) << item.name
             << setw(10) << item.weight
             << setw(10) << item.utility
             << setw(12) << (item.divisible ? "Yes" : "No")
             << setw(15) << item.utilityPerWeight() << endl;
    }

    double totalUtility = 0.0;
    double remainingCapacity = maxWeight;

    vector<pair<string, double>> takenItems; 

    for (const auto &item : items)
    {
        if (remainingCapacity <= 0)
            break;

        if (item.divisible)
        {
            double takeWeight = min(item.weight, remainingCapacity);
            double fractionTaken = takeWeight / item.weight;

            totalUtility += takeWeight * item.utilityPerWeight();
            remainingCapacity -= takeWeight;

            takenItems.push_back({item.name, fractionTaken});
        }
        else
        {
            if (item.weight <= remainingCapacity)
            {
                totalUtility += item.utility;
                remainingCapacity -= item.weight;
                takenItems.push_back({item.name, 1.0}); 
            }
        }
    }

    cout << "\n Items Loaded onto Boat \n";
    cout << left << setw(12) << "Item"
         << setw(15) << "Fraction Taken"
         << setw(15) << "Utility Gained" << endl;

    for (const auto &taken : takenItems)
    {
        string itemName = taken.first;
        double fraction = taken.second;

        for (const auto &it : items)
        {
            if (it.name == itemName)
            {
                double gainedUtility = fraction * it.utility;
                cout << left << setw(12) << itemName
                     << setw(15) << fraction
                     << setw(15) << gainedUtility << endl;
                break;
            }
        }
    }

    cout << "Total Utility: " << totalUtility << endl;
    cout << "Unused Capacity: " << remainingCapacity << " kg\n";

    return totalUtility;
}

int main()
{
    double boatCapacity;
    int numItems;

    cout << "Enter boat maximum weight capacity (kg): ";
    cin >> boatCapacity;

    cout << "Enter number of relief items: ";
    cin >> numItems;

    vector<ReliefItem> items;
    items.reserve(numItems);

    for (int i = 0; i < numItems; i++)
    {
        string name;
        double weight, utility;
        int divisibleFlag;

        cout << "\nEnter details for item " << i + 1 << ":\n";
        cout << "Item name: ";
        cin >> name;
        cout << "Weight (kg): ";
        cin >> weight;
        cout << "Utility value: ";
        cin >> utility;
        cout << "Divisible? (1 for yes, 0 for no): ";
        cin >> divisibleFlag;

        items.emplace_back(name, weight, utility, divisibleFlag == 1);
    }

    double maxUtility = fractionalKnapsack(boatCapacity, items);

    cout << "\nMaximum utility value the boat can carry: " << maxUtility << endl;

    return 0;
}
