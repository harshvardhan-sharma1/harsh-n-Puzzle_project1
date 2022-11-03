#include "StateClass.cpp"

class Node
{
    public:
    State _state;
    Node* parent;
    int depth;
    
    vector<Node*> children;
    
    Node()
    {
        // _state;
        _state = State(); 
        parent  = nullptr;
        depth  = 0;
    }

    Node(vector<int> v) 
    {
        _state = State(v);
        parent = nullptr;
        depth = 0;
    }

    Node(State& given, Node* p, int depth = 0) :_state(given), depth(depth)
    {
        parent = p;
    }

    void setParent(Node* p)
    {
        this->parent = p;
    }

    Node* getParent()
    {
        return parent;
    }

    State& getState()
    {
        return _state;
    }

    int getDepth()
    {
        return depth;
    }

    void print()
    {
        cout << "______Node{\n";
        // for (unsigned int i = 0; i < _state->size(); ++i)
        // {
        //     cout << _state->currState.at(i);
        // }
        _state.display();
        cout << "______Depth: " << depth << " }\n\n";
    }
};

int main()
{
    //1 -- Basic constructor test
    vector<int> v;
    for(unsigned i=0; i<9; i++)
    {
        v.push_back(i+1);
    }
    v.at(v.size()-1) = 0;
    State _state(v);
    Node n1(_state, nullptr, -1);
    n1.print();



    return 0;
}

class Tree
{
    
};
