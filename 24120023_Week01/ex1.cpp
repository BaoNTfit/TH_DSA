#include<iostream>
 using namespace std;
 int fibonacci(int n) {
    //Trường hợp basement để thoát ra 
    //Vì đệ quy 2 lần nên có 2 mốc chặn là 0 và 1
     if (n==0) return 0;
     if (n==1) return 1;
     // Công thức fibo 
     return fibonacci(n-1) +fibonacci(n-2);
 }
 int main () {
     int n;
     cin >> n;
     for(int i = 0; i < n; i++) {
         cout << fibonacci(i) << " ";
     }
     return 0;
 }