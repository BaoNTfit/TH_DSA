#include <iostream>
using namespace std;
int LinearSearch(int a[], int n, int k);

int main()
{
    int n, k;
    cin >> n >> k;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << LinearSearch(a, n, k);
    delete[] a;
    return 0;
}

int LinearSearch(int a[], int n, int k)
{
    for (int i = 0; i < n; i++)
    {
        if (a[i] == k)
            return i;
    }
    return -1;
}