#ifndef undo_redo_H
#define undo_redo_H

#include <iostream>
#include "game.h"
#include "config.h"

struct Node
{
    int a[MAX][MAX];
    Node* next;
};

struct Stack
{
    Node* top = nullptr; //Con trỏ đầu của stack;
    //Lưu trạng thái hiện tại của ma trận
    void push(int board[MAX][MAX]) {
        Node* newNode = new Node;
        for(int i = 0; i < sizet; ++i) {
            for(int j = 0; j < sizet; ++j) {
                newNode->a[i][j] = board[i][j];
            }
        }
        newNode->next = top;
        top = newNode;
    }
    //Lấy trạng thái đã lưu gần nhất của ma trận ra
    bool pop(int board[MAX][MAX]) {
        if(!top) {
            return false;
        }
        for(int i = 0; i < sizet; ++i) {
            for(int j = 0; j < sizet; ++j) {
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
        void undo(int b[MAX][MAX]);
        void redo(int b[MAX][MAX]);
        void saveState(int b[MAX][MAX]);
};
#endif
