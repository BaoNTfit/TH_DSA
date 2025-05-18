#include"sort.h"
void shellSort(int a[], int n)
{
	for (int interval = n / 2; interval > 0; interval /= 2)
	{
		for (int i = interval; i < n; i++)
		{
			int temp = a[i];
			int j = i;
			for (j = i; j >= interval && a[j - interval] > temp; j -= interval)
				a[j] = a[j - interval];
			a[j] = temp;
		}
	}
}