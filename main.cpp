#include "game.h"
#include "board.h"
#include "undo_redo.h"
#include "config.h"
#include "reset_game.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

int main() {
    std::srand(time(0));
    std::cout << "Welcome to 2048 Game!\n";
    std::cout << "Ban co muon New Game khong: \n";
    std::cout << "Nhap 'Co' hoac 'Khong' : ";
    std::string s;
    std::cin >> s;
    if(s == "Co") {
        reset(undostack, redostack, score);
    }
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
        hand(check, score);
        if(check == true) {
            break;
        }
        board(); // Cập nhật bảng sau mỗi lượt đi
        std::cout << "So diem hien tai cua ban: " << score << std::endl;
    }

    std::cout << "Thanks for playing.\n";
    return 0;
}
