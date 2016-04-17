#include "ConfigTree.h"
#include <iostream>

ConfigTree::ConfigTree()
{
    //ctor
}

ConfigTree::~ConfigTree()
{
    //dtor
}


Node *ConfigTree::takeStep(Position c[]) {
    for (int i = 0; i < 9; i++) {
        if (currentConfig->nextMoves[i]->config == c) {
            return currentConfig->nextMoves[i];
        }
    }
}

void ConfigTree::firstMove(Position c[]) {
    Node *newRoot = new Node(c);
    newRoot->parent = NULL;
    root = newRoot;
}

void ConfigTree::populate() {
    addRec(root, root->config, OMOVE);
    calcProbs(root);
}

void ConfigTree::addRec(Node *parent, Position c[], Position next) {
    Position nextNext;
    if (next == OMOVE) {
        nextNext = XMOVE;
    }
    else {
        nextNext = OMOVE;
    }
    for (int i = 0; i < 9; i++) {
        //Check for open moves in current board config
        if (c[i] == EMPTY) {
            //Set c as next config
            c[i] = next;
            //Build next node
            Node *tsugi = new Node(c);
            tsugi->parent = parent;
            parent->nextMoves.push_back(tsugi);
            addRec(tsugi, tsugi->config, nextNext);
            //return c to former state
            c[i] = EMPTY;
        }
    }
}

void ConfigTree::calcProbs(Node *parent) {
    float totalGames = 0.0;
    float totalWins = 0.0;
    for (int i = 0; i < parent->nextMoves.size(); i++) {
        calcProbs(parent->nextMoves[i]);
        totalGames += parent->nextMoves[i]->totalLeaves;
        totalWins += parent->nextMoves[i]->winLeaves;
    }
    parent->totalLeaves = totalGames;
    parent->winLeaves = totalWins;
    parent->winProb = totalWins / totalGames;
}

int ConfigTree::nextMove() {
    for (int i = 0; i < currentConfig->nextMoves.size(); i++) {
        std::cout << currentConfig->nextMoves[i]->winProb << std::endl;
    }
    return 0;
}
