#include"sort.h"
void shakerSort(int a[], int n)
{
	int left = 0;
	int right = n - 1;
	int k = 0;
	for (int i = left; i <= right; i++)
	{
		bool swapped = false;
		for (int j = left; j < right; j++)
			if (a[j] > a[j + 1])
			{
				swapped = true;
				HoanVi(a[j], a[j + 1]);
				k = j;
			}
		if (!swapped)
			return;
		right = k;
		swapped = false;
		for (int j = right; j > left; j--)
			if (a[j] < a[j - 1])
			{
				swapped = true;
				HoanVi(a[j], a[j - 1]);
				k = j;
			}
		if (!swapped)
			return;
		left = k;
	}
}