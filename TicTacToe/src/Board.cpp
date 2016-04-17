#include "Board.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <limits>

Board::Board()
{
    for (int i = 0; i < 9; i++) {
        config[i] = EMPTY;
    }
    result = CONT;
    //ctor
}

Board::~Board()
{
    //dtor
}

void Board::displayBoard() {
    char digits[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int i = 0;
    std::cout << "--Tic-Tac-Toe--" << std::endl << std::endl;
    std::cout << "   ";
    for (;i < 9; i++) {
        char display;
        if (config[i] == XMOVE) {
            display = 'X';
        }
        else if (config[i] == OMOVE) {
            display = 'O';
        }
        else {
            display = digits[i];
        }
        if (i == 4 || i == 1 || i == 7) {
            std::cout << " | " << display << " | ";
        }
        else{
            std::cout << display;
        }
        if (i == 2 || i == 5) {
            std::cout << std::endl << "   ---------" << std::endl << "   ";
        }
    }
    std::cout << std::endl << std::endl;
}

void Board::playerTurn() {
    int i;
    bool firstTurn = true;
    for (int i = 0; i < 9; i++) {
        if (config[i] != EMPTY) {
            firstTurn = false;
        }
    }
    std::cout << "Where do you want to move?" <<std::endl;
    std::cin >> i;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (i < 1 || i > 9 || config[i-1] != EMPTY) {
        std::cout << "Enter a valid position." << std::endl;
        playerTurn();
    }
    else{
        config[i-1] = XMOVE;
        if (firstTurn) {
            buildConfigTree();
        }
        std::cout << "\033[2J\033[1;1H";
        displayBoard();
        result = checkStatus();
        if (result != CONT) {
            gameOver = true;
        }
    }
}

void Board::computerTurn() {
    bool moved = false;
    for (int i = 0; i < 9; i++) {
        if (config[i] == EMPTY && !moved) {
            config[i] = OMOVE;
            moved = true;
        }
    }
    int index = findNextMove();
    std::cout << "\033[2J\033[1;1H";
    displayBoard();
    result = checkStatus();
    if (result != CONT) {
        gameOver = true;
    }
}

int Board::findNextMove() {
    return configTree.nextMove();
}

Outcome Board::checkStatus() {
    //First check horizontals
    if (config[0] == config[1] && config[1] == config[2]) {
        if (config[0] == OMOVE) {
            return COMP;
        }
        if (config[0] == XMOVE) {
            return PLAYER;
        }
    }
    else if (config[3] == config[4] && config[4] == config[5]) {
        if (config[3] == OMOVE) {
            return COMP;
        }
        if (config[3] == XMOVE) {
            return PLAYER;
        }
    }
    else if (config[6] == config[7] && config[7] == config[8]) {
        if (config[6] == OMOVE) {
            return COMP;
        }
        if (config[6] == XMOVE) {
            return PLAYER;
        }
    }
    //Next check verticals
    else if (config[0] == config[3] && config[3] == config[6]) {
        if (config[0] == OMOVE) {
            return COMP;
        }
        if (config[0] == XMOVE) {
            return PLAYER;
        }
    }
    else if (config[1] == config[4] && config[4] == config[7]) {
        if (config[1] == OMOVE) {
            return COMP;
        }
        if (config[1] == XMOVE) {
            return PLAYER;
        }
    }
    else if (config[2] == config[5] && config[5] == config[8]) {
        if (config[2] == OMOVE) {
            return COMP;
        }
        if (config[2] == XMOVE) {
            return PLAYER;
        }
    }
    //Now check diagonals
    else if (config[0] == config[4] && config[4] == config[8]) {
        if (config[0] == OMOVE) {
            return COMP;
        }
        if (config[0] == XMOVE) {
            return PLAYER;
        }
    }
    else if (config[2] == config[4] && config[4] == config[6]) {
        if (config[2] == OMOVE) {
            return COMP;
        }
        if (config[2] == XMOVE) {
            return PLAYER;
        }
    }

    //Check for cat's game
    bool cats = true;
    for (int i = 0; i < 9; i++) {
        if (config[i] == EMPTY) {
            cats = false;
        }
    }
    if (cats) {
        return CATS;
    }
    return CONT;
}

void Board::decideWinner(){
    if (result == CATS) {
        std::cout << "Cat's Game!" << std::endl;
    }
    else if (result == PLAYER) {
        std::cout << "Congratulations, you win!" << std::endl;
    }
    else {
        std::cout << "Sorry, you lose!" << std::endl;
    }
}

void Board::buildConfigTree(){
    configTree.firstMove(config);
    configTree.populate();
}
