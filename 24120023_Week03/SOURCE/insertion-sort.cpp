#include"sort.h"

void insertIth(int a[], int n, int i) {
    int key = a[i];
    int j = i-1;
    while (j>=0 && a[j]>key){
        a[j+1] = a[j];
        j--;
    }
    a[j+1] = key;
 }

void insSort(int a[], int n) {
    int i = 1;
    while(i<n) {
        insertIth(a,n,i);
        i++;
    }
}
