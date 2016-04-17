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
}

void ConfigTree::addRec(Node *parent, Position c[], Position next) {


}
