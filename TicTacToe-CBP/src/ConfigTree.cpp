#include "ConfigTree.h"
#include <iostream>

ConfigTree::ConfigTree()
{
    /** Set up the root of the tree and set current configuration to root
        Postpone tree construction so 9! final configs avoided **/
    //ctor
    Position c[9];
    for (int i = 0; i < 9; i++) {
        c[i] = EMPTY;
    }
    Node *newRoot = new Node(c);
    newRoot->parent = NULL;
    root = newRoot;
    currentConfig = root;
}

ConfigTree::~ConfigTree()
{
    //dtor
}

void ConfigTree::firstMove(int index) {
    /** Doesn't create new nodes, just modifies current root/cc **/
    root->config[index] = XMOVE;
    currentConfig->config[index] = XMOVE;
    currentConfig->status = CONT;
}

void ConfigTree::populate() {
    /** First recursively build the whole tree, then calculate probabilities **/
    addRec(root, root->config, OMOVE);
    calcProbs(root);
}

void ConfigTree::addRec(Node *parent, Position c[], Position next) {
    /** Recursively build the configuration tree. Each node is a possible config
        of the board. Children are the n <= 8 moves possible from the current config.
        Any node that contains win conditions does not produce children to trim tree **/
    Position nextNext;
    //Make sure we only add non-completed games
    if (parent->status == CONT) {
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
                //Build next node (tsugi = next), add to children
                Node *tsugi = new Node(c);
                tsugi->status = checkStatus(tsugi);
                tsugi->parent = parent;
                parent->nextMoves.push_back(tsugi);
                //recursively generate paths from tsugi
                addRec(tsugi, tsugi->config, nextNext);
                //return c to former state
                c[i] = EMPTY;
            }
        }
    }
}

void ConfigTree::calcProbs(Node *parent) {
    /** Calculate the win probabilities to serve as basic AI
        Always count self in total, and only count self if a
        computer win for win % **/
    float totalGames = 1;
    float totalWins = 0;
    if (parent->status == COMP) {
        totalWins += 1;
    }
    else if (parent->status == CONT){
        for (int i = 0; i < parent->nextMoves.size(); i++) {
            //Recursively generate probs for children first
            calcProbs(parent->nextMoves[i]);
            totalGames += parent->nextMoves[i]->totalLeaves;
            totalWins += parent->nextMoves[i]->winLeaves;
        }
    }
    parent->totalLeaves = totalGames;
    parent->winLeaves = totalWins;
    parent->winProb = totalWins / totalGames;
}

int ConfigTree::nextMove() {
    /** Checks the current board configuration for the next
        possible move with the highest win % and returns the
        index of the next move **/
    int index = 0;
    float maxProb = -1;
    for (int i = 0; i < currentConfig->nextMoves.size(); i++) {
        if (currentConfig->nextMoves[i]->winProb > maxProb) {
            maxProb = currentConfig->nextMoves[i]->winProb;
            index = i;
        }
    }
    Node *nextM = currentConfig->nextMoves[index];
    for (int i = 0; i < 9; i++) {
        if (currentConfig->config[i] != nextM->config[i]) {
            index = i;
        }
    }
    return index;
}

void ConfigTree::setConfig(int index, Position current) {
    /** Updates the tree's current config to the next move **/
    Node *tmp = currentConfig;
    for (int i = 0; i < currentConfig->nextMoves.size(); i++) {
        if (currentConfig->nextMoves[i]->config[index] == current) {
            tmp = currentConfig->nextMoves[i];
        }
    }
    currentConfig = tmp;
}

Outcome ConfigTree::checkStatus(Node *current) {
    /** Check the board config for win conditions and return
        an outcome.
        COMP = Computer win
        PLAYER = Player win
        CATS = Cat's game
        CONT = Continue with next turn*/
    Position *config = current->config;
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

Outcome ConfigTree::checkCurrent() {
    /** Return the win conditions of the current config **/
    return checkStatus(currentConfig);
}

void ConfigTree::printNode(Node *print) {
    /** For debugging purposes only **/
    std::cout << print->status << std::endl;
    std::cout << print->config[0] << " " << print->config[1] << " " << print->config[2] << std::endl;
    std::cout << print->config[3] << " " << print->config[4] << " " << print->config[5] << std::endl;
    std::cout << print->config[6] << " " << print->config[7] << " " << print->config[8] << std::endl;
    std::cout << "Win chance: " << print->winProb << std::endl;
}

Position *ConfigTree::getCurrentConfig() {
    /** Returns a pointer to the current config array **/
    return currentConfig->config;
}
