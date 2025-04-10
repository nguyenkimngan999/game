#include "undo_redo.h"
#include "game.h"
#include "config.h"
#include <iostream>

void undo_redo::undo(int b[size][size]) {
    if(undostack.empty()) {
        std::cout << "Khong the undo!\n";
    }
    redostack.push(b);
    undostack.pop(b);
}

void undo_redo::redo(int b[size][size]) {
    if(redostack.empty()) {
        std::cout << "Khong the redo!\n";
    }
    undostack.push(b);
    redostack.pop(b);
}

//Lưu trạng thái trước khi di chuyển
void undo_redo::saveState(int b[size][size]) {
    undostack.push(b);
    redostack.clear();
}
