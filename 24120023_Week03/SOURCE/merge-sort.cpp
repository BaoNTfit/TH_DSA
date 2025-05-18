#include"sort.h"
//O(nlogn) -> much faster 
vector<pair<int, int> > swaps;

void combine(int a[], int s, int m, int e) {
    int* buffer = new int [e+1]; // for the total size of the merged array
    int k = s;
    while(k<=e) {
        buffer[k] = a[k];
        k = k+1;
    }
    int i = s;
    int j = m+1;
    k = s;
    int first,second;
    // The first condition
    while(i <= m && j <= e){
        if (buffer[i] <= buffer[j] ) {
            a[k]= buffer[i];
            i++;
        }
        else {
            first = k, second = j;
            swaps.push_back(make_pair(first, second));
            a[k] = buffer[j];
            j++;
        }
        k++;
    }
    // The second condition ( if either smaller )
    while( i <= m) {
        a[k] = buffer[i];
        k++;
        i++;
    }
    while( j <= e) {
        a[k] = buffer[j];
        k++;
        j++;
    }
    delete [] buffer;
}
// auxiliary function (helper function)
void mrgSort(int a[], int s, int e) {
    if(s>=e) return;
    int m = (s+e)/2;
    mrgSort(a, s, m);
    mrgSort(a, m+1, e);
    combine(a, s, m, e);
}

void mrgSort(int a[], int n) { // wrapper function
    mrgSort(a, 0, n-1 );
}
