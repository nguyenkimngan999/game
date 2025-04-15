#ifndef GAME_H
#define GAME_H

#include "undo_redo.h"
#include "config.h"

// Biến toàn cục
extern int matrix[MAX][MAX];
extern long long score;

// Biến liên quan đến xử lý hàng đợi hoặc hiệu ứng
extern bool check;
extern int data[MAX];
extern int front, rear;

// Di chuyển
long long moveleft(int row[MAX]);
void moveleftall();
void moveright(int row[MAX]);
void moverightall();
void moveup();
void movedown();

// Trạng thái trò chơi
bool canMove();
bool isgameover();
bool isWinGame();

// Hành động
void hand(bool& check);
void addNewTile();

#endif
