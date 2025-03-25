#include <iostream>
using namespace std;
// Function to check if an array is sorted using recursion
bool isSorted(int arr[], int n) {
    // Base: khi n về 0 hoặc 1 thì có nghĩa là hàm đã được sắp xếp
    if (n == 1 || n == 0) return true;
// Chỉ so sánh phần tử đầu của mảng 
    if (arr[0] > arr[1])  return false;

// Đệ quy với phần tử giảm về số lượng, và check các phần tử tiếp theo
    return isSorted(arr + 1, n - 1);
}
/*
    Ý tưởng phần code này của thầy trực quan và đúng tinh thần 
đệ quy nên em xin phép sử dụng luôn ạ. Em cam đoan mình đã đọc kĩ
và suy nghĩ kĩ chứ không phải copy vào cho có ạ.

    Code ngắn và rất dễ hình dung ạ
*/
int main() {
    int n;
    cin >> n;
    int* a = new int [n];
    for (int i = 0; i < n; i ++) cin >> a[i];
    if (isSorted(a, n))
    cout << "The array is sorted.\n";
    else cout << "The array is NOT sorted.\n";
    delete [] a;
    return 0;
}