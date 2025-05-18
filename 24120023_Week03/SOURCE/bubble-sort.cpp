#include"sort.h"
// Go from the bottom of the array
// Bubble sort
void bubble(int a[], int n){
    int i = n-1;
    while(i>0) {
        if(a[i] < a[i-1]) {
            HoanVi(a[i],a[i-1]);
        }
        i--;
    }
}

// Go again from the head to the end to complete
void bblSort(int a[], int n){
    int i = 0;
    while(i<n) {
        bubble(a,n);
        i++;
    }
}
