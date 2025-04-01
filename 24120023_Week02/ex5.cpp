#include<iostream>
#include<algorithm>
using namespace std;

// Custom min function to avoid <algorithm>
int min(int a, int b) {
    return a < b ? a : b;
}

// Custom lower_bound function to find the smallest index where arr[index] >= value
int lower_bound(int* arr, int start, int end, int value) {
    while (start < end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] < value) {
            start = mid + 1;
        } else {
            end = mid;
        }
    }
    return start;
}

// Function to find minimal subarray length
int BinaryMethod(int* nums, int n,int target) {
    if (n == 0) return 0; // Handle empty array

    // Allocate prefix sum array dynamically
    int* prefix = new int[n + 1];
    prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + nums[i - 1];
    }

    int min_length = n + 1; // Larger than any possible subarray length

    for (int i = 0; i < n; i++) {
        int needed = prefix[i] + target; // Sum we need to reach or exceed
        int k = lower_bound(prefix, i + 1, n + 1, needed);
        if (k <= n) { // Valid subarray found
            int length = k - i;
            min_length = min(min_length, length);
        }
    }

    delete[] prefix; // Free allocated memory
    return min_length > n ? 0 : min_length; // Return 0 if no subarray found
}

// Bruteforce ban dau
int bruteforce(int a[],int n,int target){
    int sum = 0;
    for (int i = 0; i < n; i++) sum+=a[i];
    if (sum < target) return 0;

    int ans = n + 1; // Larger than any possible subarray length
    for (int i = 0; i < n; i++) {
        int current_sum = 0;
        for (int j = i; j < n; j++) {
            current_sum += a[j];
            if (current_sum >= target) {
                int length = j - i + 1;
                ans = min(ans, length);
                break; 
            }
        }
    }
    return ans;
}

// Phuong phap dua theo danh gia bai toan
int SlidingWindows(int nums[], int n, int target){
    if (n==0) return 0;
    int min_length = INT_MAX;
    int current_sum = 0;
    int left = 0; 
    
    for(int right = 0; right < n; right++) {
        current_sum += nums[right];
        while (current_sum >= target && left <= right) {
            min_length = min(min_length, right-left+1);
            current_sum -= nums[left];
            left++;
        }
    }
    return min_length == INT_MAX ? 0 : min_length;
}

int main () {
    int n,target;
    cout << "Nhap so luong phan tu mang: ";
    cin >> n;
    cout << "Nhap Target: ";
    cin >> target;
    cout << "Nhap cac phan tu mang: ";
    int *nums = new int [n];
    for (int i = 0; i < n; i ++) {
        cin >> nums[i];
    }
    cout << SlidingWindows(nums,n,target);
    //bruteforce(nums, n, target) << " " << BinaryMethod(nums, n, target);
    delete [] nums;
    return 0;
}