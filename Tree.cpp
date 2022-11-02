#include "StateClass.cpp"

class Node
{
    State *currState;
    vector<Node*> children;
    Node* parent;
    int depth;
    
    Node()
    {
        currState = new State();
        parent  = nullptr;
        depth  = 0;
    }

    Node(State* given, Node* p)
    {
        currState = given;
        parent = p;
        depth = p->depth +1 ;
    }

    Node* newNode(State *newState)
    {
        Node* temp = new Node;
        temp->currState = newState;
        return temp;
    }

    void Node::setParent(Node* p)
    {
        this->parent = p;
    }

};

class Tree
{

}
