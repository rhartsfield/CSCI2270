#include <iostream>
#include <limits>
#include "Board.h"

using namespace std;

bool displayMenu();

int main()
{
    bool playAgain = displayMenu();
    while (playAgain) {
        Board gameBoard;
        gameBoard.clearScreen();
        gameBoard.displayBoard();
        while (!gameBoard.isGameFinished()) {
            gameBoard.playerTurn();
            gameBoard.computerTurn();
        }
        gameBoard.decideWinner();
        char ret;
        cout << "Return to Menu? (Y/N)" << endl;
        cin >> ret;
        if (ret == 'Y' || ret == 'y') {
            gameBoard.clearScreen();
            playAgain = displayMenu();
        }
        else {
            cout << "Ok, thanks for playing!" << endl;
            playAgain = false;
        }
    }
    return 0;
}

bool displayMenu() {
    int choice;
    cout << "\033[2J\033[1;1H";
    cout << "Welcome to Tic-Tac-Toe!" << endl << endl;
    cout << "Please select an option:" << endl;
    cout << "1. Play vs. Computer" << endl;
    cout << "2. Quit" << endl;
    cin >> choice;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (choice == 1) {
        return true;
    }
    else if (choice == 2) {
        cout << "Ok, thanks for playing!" << endl;
        return false;
    }
    else {
        cout << "\033[2J\033[1;1H";
        return displayMenu();
    }
}
