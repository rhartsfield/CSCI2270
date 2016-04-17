#ifndef BOARD_H
#define BOARD_H
#include "ConfigTree.h"

class Board
{
    public:
        bool gameOver = false;
        bool firstTurn = true;
        Position config[9];
        void displayBoard();
        void playerTurn();
        void computerTurn();
        void decideWinner();
        Board();
        ~Board();
    protected:
    private:
        Outcome checkStatus();
        void takeMove();
        void buildConfigTree();
        int findNextMove();
        ConfigTree configTree;
        Outcome result;
};

#endif // BOARD_H
