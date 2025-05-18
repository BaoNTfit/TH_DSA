#include"sort.h"

// Find out the smallest value 
int locOfSmallest(int a[], int s, int e) {
    int i = s;
    int j = i;
    while(i<e) {
        if(a[i]<a[j]) {
            j = i;
        }
        i++;
    }
    return j;
}

// Sorting algorithm
void SelSort(int a[], int n) {
    int i = 0;
    while(i<n-1){
        int j = locOfSmallest(a,i, n-1);
        HoanVi(a[i], a[j]);
        i++;
    }
}
