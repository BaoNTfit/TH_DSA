#include <iostream>  
using namespace std;

// Function to determine how many days are needed with a given capacity
int Needed(int* weights, int n, int capacity) {
    int days = 1;          // Start on day 1
    int currentLoad = 0;   // Current load for the day

    for(int i = 0; i < n; i++) {
        // If adding this package exceeds capacity, start a new day
        if(currentLoad + weights[i] > capacity) {
            days++;
            currentLoad = weights[i];
        } else {
            // Otherwise, continue adding to the current day
            currentLoad += weights[i];
        }
    }
    return days;
}

int Binary (int a[], int n, int D) {
    int maxWeight = 0;
    long long sumWeights = 0;
    // Sum the total weights and the maxWeight
    for(int i = 0; i < n; i++) {
        if(a[i] > maxWeight) {
            maxWeight = a[i];
        }
        sumWeights += a[i];
    }
    // Binary search bounds
    long long left = maxWeight;
    long long right = sumWeights;

    while(left < right) {
        long long mid = (left + right) / 2;
        
        // Check how many days needed with capacity = mid
        int needed = Needed(a, n, (int)mid);
        
        // If we can ship within D days, try smaller capacity
        if(needed <= D) {
            right = mid;
        } 
        // Otherwise, need a larger capacity
        else {
            left = mid + 1;
        }
    }

    // 'left' is now the minimal capacity to ship within D days
    return left;
}
int main() {
    int n;
    cin >> n;  // Number of packages

    // Allocate dynamic array for weights
    int* weights = new int[n];
    // Read package weights
    for(int i = 0; i < n; i++) cin >> weights[i];
    int D; // number of days
    cin >> D;

    cout << Binary(weights,n,D);

    delete[] weights;
    return 0;
}
