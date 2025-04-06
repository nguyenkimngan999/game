//Xử lý logic game
#ifndef GAME_H
#define GAME_H

const int size = 4;
extern int matrix[size][size];
extern long long score;

class Game 
{
    private:
        bool check;  
        int data[size];
        int front, rear;
    public:
        
        long long moveleft(int row[size]);
        void moveleftall();
        void moveright(int col[size]);
        void moverightall();
        void moveup();
        void movedown();
        bool canMove();
        bool isgameover();
        void hand(bool& check);
        void addNewTile();
        bool isWinGame();
};

#endif 
