#include <iostream>
#include <omp.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
using namespace std;
//if you want to change array size you must directly change the value of n in the source code (gives error otherwise)
const int n = 120000;
int main()
{
    int threadsize;
    cout << "You have " << omp_get_max_threads() << " threads you can use on this machine. Please enter how many threads you would like to use for this parallel program.\n";
    cin >> threadsize;
    while (threadsize < 0 || threadsize > omp_get_max_threads()) {
        cout << "Please enter a number between 1 and " << omp_get_max_threads() << endl;
        cin >> threadsize;
    }

    
    int arr[n];
    int arr1[n];
    cout << "Starting non-parallel bubble sort:\n";
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
    for (int i = 0; i < n; i++) {
        arr1[i] = arr[i];
    }

    clock_t time_req1;
    time_req1 = clock();
    for (int i = 0; i < n; i++)
    {
        int first = i % 2;
        for (int j = first; j < n - 1; j += 2)
        {

            if (arr1[j] > arr1[j + 1])
            {
                std::swap(arr1[j], arr1[j + 1]);
            }
        }
    }

    time_req1 = clock() - time_req1;
    std::cout << "Processing time for normal bubble of array size " << n << ": " << (float)time_req1 / CLOCKS_PER_SEC << " seconds\n";
    cout << "Starting parallel bubble sort with a thread number of " << omp_get_max_threads() << endl;
    clock_t time_req;
    time_req = clock();
    for (int i = 0; i < n; i++)
    {

        int first = i % 2;

        omp_set_num_threads(threadsize);
#pragma omp parallel for default(none),shared(arr,first)

        for (int j = first; j < n - 1; j += 2)
        {

            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    time_req = clock() - time_req;
    std::cout << "Processing time for normal bubble of array size " << n << " with " << omp_get_max_threads() << " threads: " << (float)time_req / CLOCKS_PER_SEC << " seconds\n";
    cout << "Would you like to print the first 100 items of either the parallel or non parallel array? (1 for parallel, 2 for sequential, any other number for no ";
    int choice;
    cin >> choice;
        if (choice == 1) {
            for (int i = 0; i < 100; i++) {
                cout << arr[i] << endl;
            }
    }
        else if (choice == 2) {
            for (int i = 0; i < 100; i++) {
                cout << arr1[i] << endl;
            }
        }
        cout << "Goodbye!\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
