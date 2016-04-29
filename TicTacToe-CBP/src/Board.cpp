#include "Board.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <limits>

Board::Board()
{
    result = CONT;
    //ctor
}

Board::~Board()
{
    //dtor
}

bool Board::isGameFinished() {
    /** Returns a bool whether or not win conditions have been met **/
    return gameOver;
}

void Board::displayBoard() {
    /** Displays the current board configuration for the user **/
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
    /** Asks for the player to input a location to place an X
        If it is the first turn, the configuration tree is built,
        otherwise the current configuration is updated **/
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
    /** The computer searches the tree for a move with a high
        win percentage and then updates the current configuration
    **/
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
    /** Clear the screen using some weird string **/
    std::cout << "\033[2J\033[1;1H";
}

void Board::takeMove(int index, Position nextMove) {
    /** Has the configuration tree update the current configuration **/
    configTree.setConfig(index, nextMove);
}

int Board::findNextMove() {
    /** Has the configuration tree search for the next move
        and return the index to place the O **/
    return configTree.nextMove();
}

Outcome Board::getStatus() {
    /** Has the configuration tree check the current config for
        win conditions. Returns the Outcome of the check. **/
    return configTree.checkCurrent();
}

void Board::buildConfigTree(int index){
    /** Initializes the configuration tree by first setting the first
        move to decrease overall size of the tree, then populates
        the rest of the tree **/
    configTree.firstMove(index);
    configTree.populate();
}

Position *Board::getConfig(){
    /** Returns the current configuration, implemented as an array of
        nine Positions **/
    return configTree.getCurrentConfig();
}

void Board::decideWinner(){
    /** Checks the value of result member to output winner **/
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
