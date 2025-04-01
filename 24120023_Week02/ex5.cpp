#include<iostream>
using namespace std;

int bruteforce(int a[],int n,int target){
    int ans = n;
    int sum = 0;
    for (int i = 0; i < n; i++) sum+=a[i];
    if (sum < target) return 0;

    for (int i = 0; i < n; i++) {
        int length = 0;
        int temp = 0;
        int j = i;
        while(temp<target){
            temp = temp + a[j];
            j++;
            length++;
        }
        if(ans > length) ans = length;
    }
    return ans;
}

int main () {
    int n,target;
    cin >> n >> target;
    int *nums = new int [n];
    for (int i = 0; i < n; i ++) {
        cin >> nums[i];
    }
    cout << bruteforce(nums,n,target);
    delete [] nums;
    return 0;
}