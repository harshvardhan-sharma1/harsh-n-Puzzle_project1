#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

class State 
{
  public:
    int n;
    vector<int> currState;

  State()
  {
    cout << "Enter the size of n-Puzzle\n";
    cin >> n;

    currState.resize(n+1);
    for (unsigned i = 0; i < currState.size(); i++)
    {
      currState.at(i)= i;
    }
  }

//default constructor for known size
  State(unsigned  int n) : n(n+1)
  {
    for (unsigned i = 0; i < n+1; i++)
    {
      currState.at(i)= i;
    }
  }

  //parameterized constructor (takes in values from a vector)
  State(vector<int>& v) 
  {
    n = v.size();
    currState = v;
  }

  ///copy constructor
  State(const State& other)
  {
    n = other.n;
    currState = other.currState;
  }

  ///assignment operator
//   State& operator=(const State& other)
//   {
//     if (this != &other)
//     {
//       n = other.n;
//       currState = other.currState;
//     }
//     return *this;
//   }

  friend bool operator==(const State& one, const State& two)
  {
    if(one.currState.size() != two.currState.size())
        return false;


    for(unsigned i =0; i<one.currState.size(); i++)
    {
        if(one.currState.at(i) != two.currState.at(i))
            return false;
    }
    return true;
  }

  friend bool operator!=(const State& one, const State& two)
  {

    if(one.currState.size() != two.currState.size())
        return true;

    for(unsigned i =0; i<one.currState.size(); i++)
    {
        if(one.currState.at(i) != two.currState.at(i))
            return true;
    }

    return false;
  }

//checks if the state is equal to the goal state
  bool isGoal()
  {
    for(unsigned i=0; i<currState.size(); i++)
    {
      if(currState.at(i)!= i)
        return false;
    }
    return true;
  }

//displays the puzzle in a matrix format
  void display()
  {
    // int row_size = static_cast<int> (ceil(log2(currState.size())));
    int row_size = static_cast<int> ((log2(currState.size())));
    int r =0;
    for(unsigned i=0; i<currState.size(); i++)
    {
        cout << currState.at(i) << ' ';
        r++;
        if(r == row_size)
        {
            r =0;
            cout << "\n";
        }
    }
    cout << "\n";
  }

//Calculates how many tiles are not in their correct place
  int misplacedTile(State* x) 
  {
    int counter = 0;
    for(unsigned i =0; i< x->currState.size(); i++)
    {
      if(x->currState.at(i) != i)
        counter++;
    }
    return counter;
  }
};


int main()
{ 

    //Testing for states class
    vector<int> v;
    vector<int> v2;

    for(unsigned i=0; i<8; i++)
    {
        v.push_back(i+1);
    }
    for(int i=7; i>=0; i--)
    {
        v2.push_back(i+1);
    }

    State *curr = new State(v);
    curr->display();

    cout << "\n\n\n";
    State *c = new State(v2);
    curr = c;
    curr->display();

    cout << "\n\nV2 == V ?? --> " << (v2==v) << " | V2!=V ?? --> " << (v2!=v) << "\n";
    
    State *c3 = new State();
    c3->display();

    cout << "IS C1 = goal? " << c->isGoal() << endl;
    cout << "IS C3 = goal? " << c3->isGoal() << endl << endl;
    
    for(unsigned i=0; i<8; i++)
    {
      v.at(i) = i+1;
    }
    State *c4 = new State(v);
    c4->display();
    cout << "Misplaced tile C1: " <<c->misplacedTile(c) << endl;
    cout << "Misplaced tile C1: " <<curr->misplacedTile(curr) << endl;
    cout << "Misplaced tile C1: " <<c3->misplacedTile(c3) << endl;
    cout << "Misplaced tile C1: " <<c4->misplacedTile(c4) << endl;

   return 0;
}

