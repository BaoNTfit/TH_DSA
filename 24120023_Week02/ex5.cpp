#include<iostream>
#include<algorithm>
using namespace std;

int BinarySearch(int arr[], int start, int end, int value) {
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
int FindMinimalSubArray(int* nums, int n,int target) {
    if (n == 0) return 0; 

    int* prefix = new int[n + 1];
    prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + nums[i - 1];
    }

    int min_length = n + 1; 

    for (int i = 0; i < n; i++) {
        int needed = prefix[i] + target; 
        int k = BinarySearch(prefix, i + 1, n + 1, needed);
        if (k <= n) { 
            int length = k - i;
            min_length = min(min_length, length);
        }
    }

    delete[] prefix; 
    return min_length > n ? 0 : min_length; 
}

// Bruteforce ban dau
int bruteforce(int a[],int n,int target){
    int sum = 0;
    for (int i = 0; i < n; i++) sum+=a[i];
    if (sum < target) return 0;

    int ans = n + 1;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        for (int j = i; j < n; j++) {
            temp += a[j];
            if (temp >= target) {
                int length = j - i + 1;
                ans = min(ans, length);
                break; 
            }
        }
    }
    return ans;
}

// Phuong phap dua theo danh gia bai toan ( search them tu chatGPT )
int SlidingWindows(int nums[], int n, int target){
    if (n==0) return 0;
    int min_length = INT_MAX;
    int sum = 0;
    int left = 0; 
    
    for(int right = 0; right < n; right++) {
        sum += nums[right];
        while (sum >= target && left <= right) {
            min_length = min(min_length, right-left+1);
            sum -= nums[left];
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
    cout << FindMinimalSubArray(nums,n,target);
    //cout << bruteforce(nums, n, target) << " " << SlidingWindows(nums, n, target);
    delete [] nums;
    return 0;
}