#include"sort.h"
void heapRebuild(int a[], int pos, int n)
{

	while (2 * pos + 1 < n)
	{
		int j = 2 * pos + 1;
		if (j < n - 1)
			if (a[j] < a[j + 1])
				j = j + 1;
		if (a[pos] >= a[j])
			return;
		HoanVi(a[pos], a[j]);
		pos = j;
	}
}
void heapConstruct(int a[], int n)
{
	for (int i = (n - 1) / 2; i >= 0; i--)
		heapRebuild(a, i, n);
}
void heapSort(int a[], int n)
{
	heapConstruct(a, n);
	int r = n - 1;
	while (r > 0)
	{
		HoanVi(a[0], a[r]);
		heapRebuild(a, 0, r);
		r--;
	}
}
