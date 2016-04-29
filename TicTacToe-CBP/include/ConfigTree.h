#ifndef CONFIGTREE_H
#define CONFIGTREE_H
#import <vector>

enum Position {EMPTY, XMOVE, OMOVE};
enum Outcome {CONT, PLAYER, COMP, CATS};

struct Node{
    Position config[9];
    Outcome status;
    int winLeaves;
    int totalLeaves;
    float winProb;
    Node *parent;
    std::vector<Node*> nextMoves;
    Node() {}
    Node(Position c[]) {
        for (int i = 0; i < 9; i++) {
            config[i] = c[i];
        }
    }
};


class ConfigTree
{
    public:
        ConfigTree();
        ~ConfigTree();
        void firstMove(int index);
        void populate();
        int nextMove();
        void setConfig(int index, Position current);
        Outcome checkCurrent();
        void printNode(Node *print);
        Position *getCurrentConfig();
    protected:
    private:
        Node *root;
        void addRec(Node *parent, Position config[], Position next);
        void calcProbs(Node *parent);
        Outcome checkStatus(Node *current);
        Node *currentConfig;
};

#endif // CONFIGTREE_H
