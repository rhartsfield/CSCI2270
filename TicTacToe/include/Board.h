#ifndef BOARD_H
#define BOARD_H
#include "ConfigTree.h"

class Board
{
    public:
        bool gameOver = false;
        bool firstTurn = true;
        void displayBoard();
        void playerTurn();
        void computerTurn();
        void decideWinner();
        void clearScreen();
        Board();
        ~Board();
    protected:
    private:
        Outcome getStatus();
        void takeMove(int index, Position nextMove);
        Position *getConfig();
        void buildConfigTree(int index);
        int findNextMove();
        ConfigTree configTree;
        Outcome result;
};

#endif // BOARD_H
