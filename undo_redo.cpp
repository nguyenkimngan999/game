#include "undo_redo.h"
#include "game.h"
#include <iostream>

void undo_redo::undo(int b[size][size]) {
    redostack.push(b);
    undostack.pop(b);
}

void undo_redo::redo(int b[size][size]) {
    undostack.push(b);
    redostack.pop(b);
}

//Lưu trạng thái trước khi di chuyển
void undo_redo::saveSate(int b[size][size]) {
    undostack.push(b);
    redostack.clear();
}
