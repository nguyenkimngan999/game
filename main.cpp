#include "game.h"
#include "board.h"
#include <iostream>

int main() {
    std::cout << "Welcome to 2048 Game!\n";
    
    // Khởi tạo bàn cờ ban đầu
    addNewTile();
    addNewTile();
    
    // Hiển thị bảng đầu tiên
    board();

    // Vòng lặp chính của game (nếu chưa có)
    while (!isgameover()) {
        hand();
        board(); // Cập nhật bảng sau mỗi lượt đi
    }

    std::cout << "Game Over! Thanks for playing.\n";
    return 0;
}
