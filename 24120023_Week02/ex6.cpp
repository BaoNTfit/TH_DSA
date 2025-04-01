#include<iostream>
using namespace std;

bool bruteforce(int a[], int n, int target) {
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++) {
            if (a[i]+a[j]==target) return true;
        }
    }
    return false;
}

bool BinarySearch(int a[], int n, int target) {
    for(int i = 0; i < n; i++){
        int temp = target - a[i];
        int left = i + 1, right = n-1;
        while(left <= right) {
            int mid = (left+right)/2;
            if (a[mid]==temp) return true;
            if (a[mid]>temp) right = mid - 1;
            else left = mid+1;
        }
    }
    return false;
}

int main () {
    int n,target;
    cin >> n;
    int *nums = new int [n];
    for (int i = 0; i < n; i ++) {
        cin >> nums[i];
    }
    cin >> target;
    if(BinarySearch(nums,n,target)==true) cout << "YES";
    else cout << "NO";
    delete [] nums;
    return 0;
}