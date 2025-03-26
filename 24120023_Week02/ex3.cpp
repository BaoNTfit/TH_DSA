#include <iostream>
using namespace std;
int MinElementInRotatedSort(int a[], int n);
int main()
{
    int n;
    cin >> n;

    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << MinElementInRotatedSort(a, n);
    return 0;
}
int MinElementInRotatedSort(int a[], int n)
{
    int left = 0, right = n - 1;
    if (a[left] < a[right])
        return a[left];
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (a[mid] <= a[left] && a[mid] <= a[right])
            return a[mid];
        if (a[left] > a[right])
        {
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
}
