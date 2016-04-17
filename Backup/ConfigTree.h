#ifndef CONFIGTREE_H
#define CONFIGTREE_H
#import <vector>
enum Position {EMPTY, XMOVE, OMOVE};
enum Outcome {CONT, PLAYER, COMP, CATS};

struct Node{
    Position config[9];
    int winLeaves;
    int totalLeaves;
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
        Node *root;
        Node *currentConfig;
        ConfigTree();
        ~ConfigTree();
        void firstMove(Position config[]);
        void populate();
        Node *takeStep(Position config[]);
    protected:
    private:
        void addRec(Node *parent, Position config[], Position next);
};

#endif // CONFIGTREE_H
