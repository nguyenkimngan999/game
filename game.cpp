#include "game.h"
#include "undo_redo.h"
#include "config.h"

#include <algorithm>
#include <iostream>

int matrix[MAX][MAX] = {0}; // Khởi tạo ma trận 

long long score = 0; //Biến dùng để lưu điểm số, mỗi lần gộp
bool check = false; //Biến dùng để kiểm tra 2 phần
Game game;

struct MyQueue {
    int data[MAX]; // dùng đúng kích thước hàng
    int front, rear;

    MyQueue() {
        front = 0;
        rear = 0;
    }

    bool empty() {
        return front == rear;
    }

    void push(int x) {
        if (rear < size) {
            data[rear++] = x;
        }
    }

    int pop() {
        if (!empty()) {
            return data[front++];
        }
        return -1; // lỗi nếu hàng đợi rỗng
    }

    int peek() {
        if (!empty()) {
            return data[front];
        }
        return -1;
    }
};

//hàm xử lí di chuyển của 1 hàng sang trái
long long Game::moveleft(int row[MAX]) {
    MyQueue q;
    for (int i = 0; i < size; i++)
        if (row[i] != 0) q.push(row[i]);

    int index = 0;
    while (!q.empty()) {
        int first = q.pop();
        if (!q.empty() && first == q.peek()) {
            first *= 2;
            score += first;
            q.pop();
        }
        row[index++] = first;
    }
    while (index < size) row[index++] = 0;
    return score;
}

//hàm di chuyển của thao tác sang trái
void Game::moveleftall() {
    for(int i = 0; i < size; ++i) {
        moveleft(matrix[i]);
    }
}

void Game::moveright(int col[MAX] ) {
    int tmp[size] = {0};
    //Sao chép vào mảng để gộp 
    for(int i = 0; i < size; ++i) {
        tmp[i] = col[i];
    }
    //Gộp ô
    std::reverse(tmp, tmp + size);
    Game::moveleft(tmp);
    std::reverse(tmp, tmp + size);
    //Sao chép vào mảng gốc
    for(int i = 0; i < size; ++i) {
        col[i] = tmp[i];
    }
}

void Game::moverightall() {
    for(int i = 0; i < size; ++i) {
        Game::moveright(matrix[i]);
    }
}

void Game::moveup() {
    //Sao chép cột di chuyển
    for(int i = 0; i < size; ++i) {
        int tmp[size] = {0}; 
        // sao chép từng cột
        for(int j = 0; j < size; ++j) {
            tmp[j] = matrix[j][i];
        }
        //Gộp ô
        Game::moveleft(tmp);
        //Cập nhật lại ma trận
        for(int j = 0; j < size; ++j) {
            matrix[j][i] = tmp[j];
        }
    }
}

void Game::movedown() {
    //Sao chép cột di chuyển
    for(int i = 0; i < size; ++i) {
        int tmp[size] = {0}; 
        // sao chép từng cột
        for(int j = 0; j < size; ++j) {
            tmp[j] = matrix[j][i];
        }
        //Gộp ô
        std::reverse(tmp, tmp + size);
        Game::moveleft(tmp);
        std::reverse(tmp, tmp + size);
        //Cập nhật lại ma trận
        for(int j = 0; j < size; ++j) {
            matrix[j][i] = tmp[j];
        }
    }
}

bool Game::canMove() {
    //Kiểm tra xem còn ô trống để di chuyển không
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if(matrix[i][j] == 0) {
                return true;
            }
        }
    }
    //Kiểm tra xem các ô còn lại còn có khả năng gộp không 
    for(int i = 0; i < size; ++i) {
        //Kiểm tra xem hàng ngang còn ô gộp được không
        for(int j = 0; j < size - 1; ++j) {
            if(matrix[i][j] == matrix[i][j + 1]) {
                return true;
            }
        }
    }
    //Kiểm tra xem hàng dọc còn ô gộp được không
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size - 1; ++j) {
            if(matrix[j][i] == matrix[j + 1][i]) {
                return true;
            }
        }
    }
    return false; //Không còn ô di chuyển được và cũng không còn ô có khả năng gộp được
}

bool Game::isgameover() {
    return !Game::canMove(); //Nếu không còn khả năng di chuyển hay gộp nữa thì trò chơi kết thúc 
}

void Game::hand(bool& check, undo_redo& ur) {
    char c;
    std::cout << "Nhap cach di chuyen theo huong dan duoi day: \n\n";
    std::cout << "Nhap W neu muon di chuyen len\n";
    std::cout << "Nhap S neu muon di chuyen xuong\n";
    std::cout << "Nhap A neu muon di chuyen sang trai\n";
    std::cout << "Nhap D neu muon di chuyen sang phai\n";
    std::cout << "\n";
    std::cin >> c;
    c = (char)std::toupper(c); //Biến đổi thanh in hoa nếu người dùng lỡ nhập kí tự thường
    while(c != 'W' && c != 'S' && c != 'A' && c != 'D' && c != 'U' && c != 'R') {
        std::cout << "Ban vua nhap ki tu khong hop le. De tiep tuc tro choi, hay nhap ki tu dung vơi huong dan\n";
        std::cout << "Con neu ban muon ket thuc tro choi thi vui long bam so 0\n";
        std::cin >> c;
        if(c == '0') {
            check = true;
            std::cout << "Tro choi da ket thuc dung voi yeu cau!\n";
            return;
        }
        c = (char)std::toupper(c);
        if(c == 'W' || c == 'A' || c == 'D' || c == 'S') {
            break;
        }
    }
    std::cout << "Nhap U de undo, R de redo\n";
    if (c == 'U') {
        ur.undo(matrix);
        return;
    } else if (c == 'R') {
        ur.redo(matrix);
        return;
    }
    
    // Trong Game::hand()
    if (c == 'A') {
        ur.saveState(matrix); // <- lưu trước khi thay đổi
        game.moveleftall();
    } else if (c == 'D') {
        ur.saveState(matrix);
        game.moverightall();
    } else if (c == 'W') {
        ur.saveState(matrix);
        game.moveup();
    } else if (c == 'S') {
        ur.saveState(matrix);
        game.movedown();
    }
    if(game.isgameover()) {
        std::cout << "\nGAME OVER\n";
    } else if(game.isWinGame()){
        check = true;
        std::cout << "You Win!!!";
        return;
    } else {
        game.addNewTile(); //Thêm ô mới sau mỗi lần di chuyển 
    }
}

void Game::addNewTile() {
    int emptyCells[size * size][2];
    int count = 0;//Dùng để đánh dấu các ô trống
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == 0) {
                emptyCells[count][0] = i;//Đánh dấu hoành độ
                emptyCells[count][1] = j;//Đánh dấu tung độ
                count++;
            }
        }
    }
    if(count == 0) {
        return;
    }
    int idx = rand() % count;
    matrix[emptyCells[idx][0]][emptyCells[idx][1]] = (rand() % 10 == 0) ? 4 : 2;
}

bool Game::isWinGame() {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if(matrix[i][j] == 2048) {
                return true;
            } 
        }
    }
    return false;
}
