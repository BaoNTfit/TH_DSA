#include"sort.h"
int partition(int a[], int first, int last)
{
	int pivot = a[(first + last) / 2];
	int i = first;
	int j = last;
	int tmp;
	while (i <= j)
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
void quickSort(int a[], int first, int last)
{
	int index = partition(a, first, last);
	if (first < index - 1)
		quickSort(a, first, index - 1);
	if (index < last)
		quickSort(a, index, last);
}