#include<iostream>
using namespace std;
int main () {
    int n,days;
    cin >> n;
    int *nums = new int [n];
    for (int i = 0; i < n; i ++) {
        cin >> nums[i];
    }
    cin >> days;
    cout << (nums,n,days);
    delete [] nums;
    return 0;
}