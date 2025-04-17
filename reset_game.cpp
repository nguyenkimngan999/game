#include "reset_game.h"
#include "undo_redo.h"
#include "game.h"

void reset(Stack& undostack, Stack& redostack, long long& score) {
    undostack.clear();
    redostack.clear();
    score = 0;
}