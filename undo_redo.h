#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include <iostream>
#include "config.h"

// Node lưu trạng thái ma trận
struct Node {
    int a[MAX][MAX];
    long long score;
    Node* next;
};

// Stack quản lý các trạng thái
struct Stack {
    Node* top = nullptr;

    // Lưu trạng thái hiện tại của ma trận
    void push(int board[MAX][MAX], long long current_score) {
        Node* newNode = new Node;
        for (int i = 0; i < sizet; ++i) {
            for (int j = 0; j < sizet; ++j) {
                newNode->a[i][j] = board[i][j];
            }
        }
        newNode->score = current_score;
        newNode->next = top;
        top = newNode;
    }

    // Lấy trạng thái gần nhất ra khỏi stack
    bool pop(int board[MAX][MAX], long long& current_score) {
        if (!top) return false;

        for (int i = 0; i < sizet; ++i) {
            for (int j = 0; j < sizet; ++j) {
                board[i][j] = top->a[i][j];
            }
        }
        Node* tmp = top;
        current_score = tmp->score;
        top = top->next;
        delete tmp;
        return true;
    }

    bool empty() {
        return top == nullptr;
    }

    // Xóa toàn bộ stack
    void clear() {
        while (top) {
            Node* tmp = top;
            top = top->next;
            delete tmp;
        }
    }
};

// Hai ngăn xếp toàn cục dùng cho undo và redo
extern Stack undostack;
extern Stack redostack;

// Hàm thao tác undo/redo
void saveState(int b[MAX][MAX], long long score);
void undo(int b[MAX][MAX], long long& score);
void redo(int b[MAX][MAX], long long& score);

#endif
