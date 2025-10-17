/*
Movie Recommendation System Optimization
A popular OTT platform, StreamFlix, offers personalized recommendations by sorting movies
based on user preferences, such as IMDB rating, release year, or watch time popularity.
However, during peak hours, sorting large datasets slows down the system.
As a backend engineer, you must:
● Implement Quicksort to efficiently sort movies based on various user-selected
parameters.
● Handle large datasets containing of movies while maintaining fast response times
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Class representing a Movie
class Movie
{
public:
    string title;
    double imdbRating;
    int releaseYear;
    long long watchTime;

    Movie(string t = "", double r = 0.0, int y = 0, long long w = 0)
    {
        title = t;
        imdbRating = r;
        releaseYear = y;
        watchTime = w;
    }
};

// QuickSort class to sort movies
class QuickSort
{
public:
    // Partition function (pivot is first element)
    int partition(vector<Movie> &arr, int low, int high, int choice)
    {
        Movie pivot = arr[low];
        int i = low + 1;
        int j = high;

        while (true)
        {
            while (i <= high && compare(arr[i], pivot, choice))
                i++;
            while (j >= low && compare(pivot, arr[j], choice))
                j--;

            if (i < j)
                swap(arr[i], arr[j]);
            else
                break;
        }
        swap(arr[low], arr[j]);
        return j;
    }

    // Recursive QuickSort
    void quickSort(vector<Movie> &arr, int low, int high, int choice)
    {
        if (low < high)
        {
            int pivotIndex = partition(arr, low, high, choice);
            quickSort(arr, low, pivotIndex - 1, choice);
            quickSort(arr, pivotIndex + 1, high, choice);
        }
    }

private:
    // Comparison function based on user choice
    bool compare(Movie &a, Movie &b, int choice)
    {
        if (choice == 1)
            return a.imdbRating < b.imdbRating; // Sort by Rating descending
        if (choice == 2)
            return a.releaseYear < b.releaseYear; // Sort by Release Year descending
        return a.watchTime < b.watchTime;         // Sort by Watch Time descending
    }
};

int main()
{
    int n;
    cout << "Enter total number of movies: ";
    cin >> n;

    vector<Movie> movies;
    for (int i = 0; i < n; ++i)
    {
        cin.ignore(); // Clear buffer for getline
        string title;
        double rating;
        int year;
        long long watch;
        cout << "\nMovie " << i + 1 << " details:\n";
        cout << "Title: ";
        getline(cin, title);
        cout << "IMDB Rating: ";
        cin >> rating;
        cout << "Release Year: ";
        cin >> year;
        cout << "Watch Time (in hours): ";
        cin >> watch;
        movies.push_back(Movie(title, rating, year, watch));
    }

    cout << "\nChoose sorting parameter:\n1 - IMDB Rating\n2 - Release Year\n3 - Watch Time\nYour choice: ";
    int choice;
    cin >> choice;

    QuickSort sorter;
    sorter.quickSort(movies, 0, n - 1, choice);

    cout << "\n--- Sorted Movies ---\n";
    for (auto &m : movies)
    {
        cout << m.title
             << " | Rating: " << m.imdbRating
             << " | Year: " << m.releaseYear
             << " | Watch Time: " << m.watchTime << " hrs" << endl;
    }

    return 0;
}

