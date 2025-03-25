#include<iostream>
 #include <string>
 using namespace std;
 void generateBinaryStrings(int n, string str);
 int main() {
     int n;
     cin >> n;
     generateBinaryStrings(n, ""); // Mảng đầu vào là mảng rỗng ( Theo yêu cầu đề về function )
     return 0;
 }
 
 void generateBinaryStrings(int n, string str) {
    // Biến n là biến chặn để thoát recursive 
     if (n == 0) {
         cout << str << endl;
     } else {
         generateBinaryStrings(n - 1, str + '0');
         generateBinaryStrings(n - 1, str + '1');
         /*
         Ý tưởng xây dựng là tạo lần lượt các strings gồm các char được bổ sung liên tục:
         Ta gọi hàm để + '0' hoặc '1' vào string bất kì
         Khi độ dài của string == n thì hoàn thành 1 xâu nhị phân

         Để xây dựng xâu nhị phân theo thứ tự, ta tạo str + '0' trước sau đó đến 1
         Bởi vì 2 hàm generate đều được gọi lồng trong 1 hàm mỗi khi giảm n - 1 đi, 
         hay nói cách khác là generate thêm 1 char nên thứ tự cũng được xen kẽ. 
         
         Debug với n = 2 để hình dung:
         Ta thấy str = ""
         -> str = "0" -> str = "00" ( sẽ cout ra nhưng không ảnh hưởng tiến trình đệ quy)
                      -> str = "01" ( tương tự )
            str = "1" -> str = "10" và "11" 

        Việc đệ quy được gọi chung với nhau 2 lần liên tiếp làm việc mô hình hóa trở nên 
        phức tạp với việc qa mỗi lần đệ quy -> ở dứoi sẽ xuất hiện gấp đôi

        Ý tưởng gốc vẫn là chọn 0 hoặc 1 để cộng vào mảng nên khá đơn giản
        Giả sử là mã thập lục phân thì vẫn như vậy với 16 hàm lồng vào mỗi lần đệ quy
         */
     }
 }
 