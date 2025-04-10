#ifndef undo_redo_H
#define undo_redo_H

#include <iostream>
#include "game.h"
#include "config.h"

struct Node
{
    int a[size][size];
    Node* next;
};

struct Stack
{
    Node* top = nullptr; //Con trỏ đầu của stack;
    //Lưu trạng thái hiện tại của ma trận
    void push(int board[size][size]) {
        Node* newNode = new Node;
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                newNode->a[i][j] = board[i][j];
            }
        }
        newNode->next = top;
        top = newNode;
    }
    //Lấy trạng thái đã lưu gần nhất của ma trận ra
    bool pop(int board[size][size]) {
        if(!top) {
            return false;
        }
        for(int i = 0; i < size; ++i) {
            for(int j = 0; j < size; ++j) {
                board[i][j] = top->a[i][j];
            }
        }
        Node* tmp = top;
        top = top->next;
        delete tmp;
        return true;
    }

    bool empty() {
        return top == nullptr;
    }
    //Xóa trạng thái dùng khi undo và thao tác hoặc ngược lại
    void clear() {
        if(!top) {
            return;
        }
        while(top) {
            Node* tmp = top;
            top = top->next;
            delete tmp;
        }
    }
};

class undo_redo{
    private:
        Stack undostack, redostack;
    public:
        void undo(int b[size][size]);
        void redo(int b[size][size]);
        void saveState(int b[size][size]);
};
#endif
