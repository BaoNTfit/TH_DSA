#include<iostream>
using namespace std;
const int N = 8;
int board[N][N] = {0}; // 8x8 Chessboard
int solutions = 0; // Count valid solutions
// Function to check if a queen can be placed at board[row][col]

bool isSafe(int row, int col) {
    for(int i = 0; i < row;i++) {

        // Kiểm tra cột
        if(board[i][col] == 1) return false;

        // Kiểm tra 2 đường chéo
        if(col - (row - i) >= 0 && board[i][col - (row - i)] == 1) return false;
        if(col + (row - i) < N && board[i][col + (row - i)] == 1 ) return false;

        // Không kiểm tra hàng vì for theo từng hàng để đặt Quân Hậu rồi
    }
    return true;
}

// Backtracking function to place queens 
void solveNQueens(int row) {
    if (row == N) {
        // All queens placed successfully 
        solutions++;
        return;
    }
    for (int col = 0; col < N; col++) {
        if(isSafe(row,col)) {
            board[row][col] = 1; // place queen
            solveNQueens(row+1); // Recur for next row

            board[row][col] = 0; // Backtrack
        }
    }
}


int main () {
    solveNQueens(0);
    cout << solutions << endl;
}

/* 
Phần trên là đoạn code gốc của bài thầy ạ ( Em xin phép sử dụng lại ạ )

Em xin phép trình bày phần ý tưởng như sau: 
- Đầu tiên là hàm kiểm tra IsSafe, tạo ra để kiểm tra xem yêu cầu đề bài, với tính chất an toàn là
không nằm trên vùng đã xuất hiện của 1 quân hậu khác. Ta kiểm tra điều này với 3 lệnh if và thao
tác trên mảng 2 chiều ( vì chạy theo đường chéo nên biến tọa độ j phụ thuộc theo i).
- Hàm quan trọng sử dụng BackTracking 
    Ý tưởng xây dựng ban đầu vẫn là chạy theo từng hàng cho nên ta tiếp cận hàm đệ quy theo hướng đó
luôn với biến row là biến chặn và thoát hàm khi row == n ( basement )

Trong quá trình thực hiện ta lặp lại việc tìm kiếm các vị trí có thể đặt khác cùng với vòng for
song song với đó là kiểm tra quay lui. Bởi lẽ khi nhánh đệ quy ở hàm tiếp theo hoàn tất hàm sẽ quay 
lại hàng hiện tại và xóa con hậu vừa gán đi và gán lại bằng 0 ( để thực hiện cho lần kiểm tra tiếp theo )
bởi lẽ vị trí đó vẫn là địa điểm an toàn ( theo hàm isSafe đã kiểm tra )

Hay đơn giản là: 
Tiến lên phía trước: Thử đặt quân hậu ở một cột của hàng hiện tại, 
nếu an toàn thì tiến tới hàng tiếp theo.
Quay lui: Nếu không thể đặt quân hậu ở bất kỳ cột nào của hàng tiếp theo mà không gây xung đột, quay lại hàng trước đó và thử cột khác.
Quá trình này lặp lại cho đến khi thử hết tất cả các khả năng, đảm bảo tìm được mọi giải pháp hợp lệ.

*/