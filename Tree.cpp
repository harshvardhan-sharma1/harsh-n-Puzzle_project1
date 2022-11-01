#include "StateClass.cpp"

struct Node
{
    State currState;
    vector<Node*> children;

};
Node* newNode(State newState)
{
    Node* temp = new Node;
    temp->currState = newState;
    return temp;
}
class Tree
{

}
