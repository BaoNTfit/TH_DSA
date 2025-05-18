#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int partition(vector<int>& a, int low, int high) {
    int pivot = a[(low+high)/2];
	int i = low;
	int j = high;
	int tmp;
	while (i < j)
	{
		while (a[i] < pivot)
			i++;
		while (a[j] > pivot)
			j--;
		if (i <= j) {
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			i++;
			j--;
		}
	}
    
	return i;
}

void quickSort(vector<int> &a, int low, int high) {
    int p;
    cout << low << " " << high << endl;
    if (low < high) p = partition(a, low, high);
    quickSort(a, low, p - 1);
    quickSort(a, p, high);  
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    quickSort(a, 0, n - 1);
    return 0;
}