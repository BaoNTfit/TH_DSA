#include <iostream>  
using namespace std;

bool Check(int a[], int n, int D, int capacity) {

    int days = 1, temp = 0;
    for (int i = 0; i < n; i++) {
        if (temp + a[i] > capacity) {
            days++;
            temp = a[i];  
            if (days > D) return false;
        } else {
            temp += a[i];
        }
    }
    return true;
}

int Bruteforce(int* a, int n, int D) {
    int maxWeight = 0, sumWeights = 0;
    for (int i = 0; i < n; i++) {
        maxWeight = max(maxWeight, a[i]);
        sumWeights += a[i];
    }

    int capacity = maxWeight;
    while (!Check(a, n, D, capacity)) {
        capacity++;  // Increase capacity until false
    }

    return capacity;
}

// Another approaches
// Function to determine how many days are needed with a given capacity
int CountDays(int* weights, int n, int capacity) {
    int days = 1;          
    int temp = 0;  

    for(int i = 0; i < n; i++) {
        if(temp + weights[i] > capacity) {
            days++;
            temp = weights[i];
        } else {
            temp += weights[i];
        }
    }
    return days;
}
// BinaryLoop Approach 
int Binary (int a[], int n, int D) {
    int maxWeight = 0;
    long long sumWeights = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] > maxWeight) {
            maxWeight = a[i];
        }
        sumWeights += a[i];
    }

    // Binary search 
    long long left = maxWeight;
    long long right = sumWeights;

    while(left < right) {
        long long mid = (left + right) / 2;
        int needed = CountDays(a, n, (int)mid);
        if(needed <= D) {
            right = mid;
        } 
        else {
            left = mid + 1;
        }
    }

    // left == right is now the minimal capacity to ship within D days
    return left;
}
int main() {
    int n;
    cin >> n;  

    int* weights = new int[n];
    for(int i = 0; i < n; i++) cin >> weights[i];
    int D;
    cin >> D;
    //cout << Bruteforce(weights,n,D);
    cout << Binary(weights,n,D);
    delete[] weights;
    return 0;
}
