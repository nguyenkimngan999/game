#include "game.h"
#include "board.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "undo_redo.h"

int main() {
    std::srand(time(0));
    std::cout << "Welcome to 2048 Game!\n";
    // Khởi tạo bàn cờ ban đầu
    Game game;
    undo_redo s;
    game.addNewTile();
    game.addNewTile();
    bool check = false;
    // Hiển thị bảng đầu tiên
    board();
    // Vòng lặp chính của game (nếu chưa có)
    while (!game.isgameover()) {
        game.hand(check);
        if(check == true) {
            break;
        }
        board(); // Cập nhật bảng sau mỗi lượt đi
        std::cout << "So diem ban da choi: " << score << std::endl;
        std::cout << "Neu ban muon undo thi nhap 'U', con neu muon redo thi nhap 'R'\n";
        std::cout << "Neu khong muon thi nhap 1: ";
        char input;
        std::cin >> input;
        if(input == 'U') {
            s.undo(matrix);
            board();
        } else if(input == 'R') {
            s.redo(matrix);
            board();
        } else {
            continue;
        }
    }

    std::cout << "Thanks for playing.\n";
    return 0;
}
