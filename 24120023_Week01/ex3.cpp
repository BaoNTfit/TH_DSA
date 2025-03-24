#include<iostream>
 #include <string>
 using namespace std;
 void generateBinaryStrings(int n, string str);
 int main() {
     int n;
     cin >> n;
     generateBinaryStrings(n, ""); // Start with an empty string
     return 0;
 }
 
 
 void generateBinaryStrings(int n, string str) {
     if (n == 0) {
         cout << str << endl;
     } else {
         generateBinaryStrings(n - 1, str + '0');
         generateBinaryStrings(n - 1, str + '1');
     }
 }