#include "game.h"
#include "board.h"
#include "undo_redo.h"
#include "config.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

int main() {
    std::srand(time(0));
    std::cout << "Welcome to 2048 Game!\n";
    std::cout << "Vui long chon kich thuoc mang: ";
    std::cin >> sizet;
    // Khởi tạo bàn cờ ban đầu
    addNewTile();
    addNewTile();
    // check = false;
    // Hiển thị bảng đầu tiên
    board();
    // Vòng lặp chính của game
    while (!isgameover()) {
        hand(check);
        if(check == true) {
            break;
        }
        board(); // Cập nhật bảng sau mỗi lượt đi
        std::cout << "So diem ban da choi: " << score << std::endl;
    }

    std::cout << "Thanks for playing.\n";
    return 0;
}
