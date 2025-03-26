#include <iostream>
using namespace std;
int SentinelLinearSearch(int a[], int n, int k);
int main()
{
    int n, k;
    cin >> n >> k;

    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << SentinelLinearSearch(a, n, k);
    return 0;
}

int SentinelLinearSearch(int a[], int n, int k)
{
    int last = a[n - 1]; // Store the last element
    a[n - 1] = k;        // Set the sentinel

    int i = 0;
    while (a[i] != k)
        i++;
    a[n - 1] = last; // Restore the last element

    if (i < n - 1 || a[n - 1] == k)
        return i;
    return -1;
}
