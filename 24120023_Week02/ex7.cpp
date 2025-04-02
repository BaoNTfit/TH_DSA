#include<iostream>
using namespace std;

// Build a sort algorithm
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

    // The first condition
    while(i <= m && j <= e){
        if (buffer[i] <= buffer[j] ) {
            a[k]= buffer[i];
            i++;
        }
        else {
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

// auxiliary function (helper function - combine and recursive )
void mrgSort(int a[], int s, int e) {
    if(s>=e) return;
    int m = (s+e)/2;
    mrgSort(a, s, m);
    mrgSort(a, m+1, e);
    combine(a, s, m, e);
}

void mrgSort(int a[], int n) { // recursion
    mrgSort(a, 0, n-1 );
}

void display (int a[], int left, int mid, int right) {
    cout << "[";
    cout << a[left] << "," << a[mid] << ",";
    cout << a[right] << "]";
}

int BinarySearch(int a[], int start, int end, int target){
    int left = start+1, right = end-1;
    while(left <= right) {
        int mid = (left+right)/2;
        if (a[mid]==target) return mid;
        if (a[mid] < target) left = mid+1;
        else right = mid - 1;
    }
    return -1;
}

void TwoPointers(int a[], int n) {
    int left = 0, right = n-1;
    while(left < right) {
        int temp = 0 -a[left] - a[right];
        int mid = BinarySearch(a,left,right,temp);
        if (mid != -1) display(a,left,mid,right);
        left++; 

        temp = 0 - a[left] - a[right];
        mid = BinarySearch(a,left,right,temp);
        if (mid != -1) display(a,left,mid,right);
        right--;
    }
}
void Triplets (int nums[],int n) {
    cout << "[";
    for (int i = 0; i < n - 2; i++) {
        // Skip duplicates for i as the array is sorted
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                cout << "[" << nums[i] << ", " << nums[left] << ", " << nums[right] << "]" << ",";
                // Move pointers left and right
                left++;
                right--;
                // Skip duplicates for left and right, same as the outer for 
                while (left < right && nums[left] == nums[left - 1]) {
                    left++;
                }
                while (left < right && nums[right] == nums[right + 1]) {
                    right--;
                }
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    cout << "]";
}
void BruteForce(int a[], int n){
    for(int i = 0; i < n; i++) {
        for (int j = i+1; j< n; j++) {
            for(int k = j+1; k < n; k++) {
                if(a[i]+a[k]+a[j]==0) cout << a[i]<< a[j] << a[k] << endl;
            }
        }
    }
}

int main () {
    int n;
    cout << "Nhap So luong phan tu cua mang: ";
    cin >> n;
    int *nums = new int [n];
    for (int i = 0; i < n; i ++) {
        cin >> nums[i];
    }
    mrgSort(nums,n);
    Triplets(nums,n);
    delete [] nums;
    return 0;
}