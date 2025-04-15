#include "undo_redo.h"
#include "game.h"
#include "config.h"
#include <iostream>

Stack undostack;
Stack redostack;

void undo(int b[MAX][MAX]) {
    if(undostack.empty()) {
        std::cout << "Khong the undo!\n";
    }
    redostack.push(b);
    undostack.pop(b);
}

void redo(int b[MAX][MAX]) {
    if(redostack.empty()) {
        std::cout << "Khong the redo!\n";
    }
    undostack.push(b);
    redostack.pop(b);
}

//Lưu trạng thái trước khi di chuyển
void saveState(int b[MAX][MAX]) {
    undostack.push(b);
    redostack.clear();
}
