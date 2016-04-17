#include "Board.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <limits>

Board::Board()
{
//    for (int i = 0; i < 9; i++) {
//        config[i] = EMPTY;
//    }
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
    Position *config = getConfig();
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
    bool firstTurn = true;
    Position *config = getConfig();
    for (int i = 0; i < 9; i++) {
        if (config[i] != EMPTY) {
            firstTurn = false;
        }
    }
    int index;
    std::cout << "Where do you want to move?" <<std::endl;
    std::cin >> index;
    std::cin.clear();
    index -= 1;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (index < 0 || index > 8 || config[index] != EMPTY) {
        std::cout << "Enter a valid position." << std::endl;
        playerTurn();
    }
    else{
        if (firstTurn) {
            buildConfigTree(index);
        }
        else {
            takeMove(index, XMOVE);
        }
        clearScreen();
        displayBoard();
        result = getStatus();
        if (result != CONT) {
            gameOver = true;
        }
    }
}

void Board::computerTurn() {
    if (!gameOver) {
        int index = findNextMove();
        std::cout << "Computer moves to: " << index << std::endl;
        takeMove(index, OMOVE);
        clearScreen();
        displayBoard();
        result = getStatus();
        if (result != CONT) {
            gameOver = true;
        }
    }
}

void Board::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void Board::takeMove(int index, Position nextMove) {
    configTree.setConfig(index, nextMove);
}

int Board::findNextMove() {
    return configTree.nextMove();
}

Outcome Board::getStatus() {
    return configTree.checkCurrent();
}

void Board::buildConfigTree(int index){
    configTree.firstMove(index);
    configTree.populate();
}

Position *Board::getConfig(){
    return configTree.getCurrentConfig();
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
