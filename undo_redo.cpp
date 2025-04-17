#include "undo_redo.h"
#include "game.h"
#include "config.h"
#include <iostream>

Stack undostack;
Stack redostack;

void undo(int b[MAX][MAX], long long& score) {
    if(undostack.empty()) {
        std::cout << "Khong the undo!\n";
    }
    redostack.push(b, score);
    undostack.pop(b, score);
}

void redo(int b[MAX][MAX], long long& score) {
    if(redostack.empty()) {
        std::cout << "Khong the redo!\n";
    }
    undostack.push(b, score);
    redostack.pop(b, score);
}

//Lưu trạng thái trước khi di chuyển
void saveState(int b[MAX][MAX], long long score) {
    undostack.push(b, score);
    redostack.clear();
}
