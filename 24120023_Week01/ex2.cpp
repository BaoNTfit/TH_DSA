#include<iostream>
using namespace std;
int factorial(int n) {
    
    // Chặn basement = 0 vì 0! = 1
    if (n == 0) return 1;

    // Công thức giai thừa 
    return factorial(n-1) * n;
}
int main () {
    int n;
    cin >> n;
    cout << factorial(n);
    return 0;
}