#include<iostream>
using namespace std;
void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) { // Base
        cout << "Move disk 1 from " << from_rod << 
        " to " << to_rod << endl;
        return;
    }
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    cout << "Move disk " << n << " from " << from_rod << " to " << to_rod << endl;
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}
/* 
Bài toán sử dụng tư tưởng đệ quy thuần với việc phải dịch n-1 tấm trước khi xử lý tấm thứ n
vì vậy ta đệ quy và gọi mỗi lần dịch chuyển 1 tấm. Việc có 2 hàm được gọi trong
là vì phải dịch qua 1 cột trung gian trước khi dịch về lại cột gốc. Vì vậy
về bản chất ta vẫn chỉ gọi 2 phần độc lập, chứ không lồng nhau.

Nguồn tham khảo chính: https://www.geeksforgeeks.org/c-program-for-tower-of-hanoi/
Cùng với kiến thức được học trong môn toán rời rạc ở HK1 

*/
int main() {
    int n;
    cin >> n; 
    towerOfHanoi(n, 'A', 'C', 'B');
    return 0;
}