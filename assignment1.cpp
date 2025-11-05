/*
NAME:-SHIVANJALI SANDIP BHOSALE.
PRN:-123B1F009.
*/
/*
Design and implement a sorting algorithm using Merge Sort to efficiently arrange customer
orders based on their timestamps. The solution should handle a large dataset (up to 1 million
orders) with minimal computational overhead. Additionally, analyze the time complexity and
compare it with traditional sorting techniques.
*/

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Class representing a single customer order
class CustomerOrder
{
public:
    long long orderID;
    long long timeStamp;
    string customerName;

    CustomerOrder(long long id = 0, long long time = 0, string name = "")
        { orderID=id, timeStamp=time, customerName=name ;}
};

// Class to manage a collection of orders and sort them
class CustomerOrderManager
{
private:
    vector<CustomerOrder> orders;

    // Merge two sorted sections
    void merge(vector<CustomerOrder> &temp, int start, int mid, int end)
    {
        int i = start, j = mid + 1, k = start;

        while (i <= mid && j <= end)
        {
            if (orders[i].timeStamp <= orders[j].timeStamp)
                temp[k++] = orders[i++];
            else
                temp[k++] = orders[j++];
        }

        while (i <= mid)
            temp[k++] = orders[i++];
        while (j <= end)
            temp[k++] = orders[j++];

        for (int idx = start; idx <= end; ++idx)
            orders[idx] = temp[idx];
    }

    // Recursive merge sort
    void mergeSortRecursive(vector<CustomerOrder> &temp, int start, int end)
    {
        if (start >= end)
            return;

        int mid = start + (end - start) / 2;
        mergeSortRecursive(temp, start, mid);
        mergeSortRecursive(temp, mid + 1, end);
        merge(temp, start, mid, end);
    }

public:
    // Initialize with predefined orders
    void initializeOrders()
    {
        orders = {
            CustomerOrder(201, 167900, "Arjun"),
            CustomerOrder(105, 167820, "Priya"),
            CustomerOrder(308, 167950, "Rohan"),
            CustomerOrder(150, 167845, "Meera"),
            CustomerOrder(401, 167830, "Ananya")};
    }

    // Public function to sort orders
    void sortOrders()
    {
        vector<CustomerOrder> temp(orders.size());
        mergeSortRecursive(temp, 0, orders.size() - 1);
    }

    // Display all orders
    void displayOrders() const
    {
        cout << "\n--- Sorted Orders List ---\n";
        for (const auto &order : orders)
        {
            cout << "Order ID: " << order.orderID
                 << " | Timestamp: " << order.timeStamp
                 << " | Customer: " << order.customerName << '\n';
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    CustomerOrderManager manager;
    manager.initializeOrders();

    auto startTime = chrono::high_resolution_clock::now();
    manager.sortOrders();
    auto endTime = chrono::high_resolution_clock::now();

    chrono::duration<double> duration = endTime - startTime;

    cout << "Orders sorted by timestamp successfully!\n";
    cout << "Time taken: " << duration.count() << " seconds\n";

    manager.displayOrders();

    return 0;
}


