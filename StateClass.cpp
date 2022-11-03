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
    cout << "Enter n for n-Puzzle\n";
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
    currState.resize(n);
    for (unsigned i = 0; i < n; i++)
    {
      currState.at(i)= i;
    }
  }

  //parameterized constructor (takes in values from a vector)
  State(vector<int>& v) : n(v.size())
  {
    currState = v;
  }

  ///copy constructor
  State(const State& a)
  {
    n = a.n;
    currState = a.currState;
  }

  //assignment operator
  State& operator=(const State& other)
  {
    if (this != &other)
    {
      n = other.n;
      currState = other.currState;
    }
    return *this;
  }

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

  int size()
  {
    return currState.size();
  }

  int at(int index)
  {
    return currState.at(index);
  }
  
  //Finds the index of an empty tile
  int findEmptyTile()
  {
    for(unsigned i=0; i<currState.size(); i++)
    {
      if(currState.at(i)==0)
        return i;
    } 
    return currState.size() -1;
  }

  //Swaps the value at two indices
  void Swap(int a, int b)
  {
    int temp = currState.at(a);
    currState.at(a)  = b;
    currState.at(b) = temp;
  }

//checks if the state is equal to the goal state
  bool isGoal()
  {
    for(unsigned i=0; i<currState.size()-1; i++)
    {
      if(currState.at(i)!= i+1)
        return false;
    }
    return true;
  }

  vector<int>& getState()
  {
    return currState;
  }

  void SetState(vector<int>& v)
  {
    currState = v;
  }

//displays the puzzle in a matrix format
  void display()
  {
    // int row_size = static_cast<int> (ceil(log2(currState.size())));
    // int row_size = static_cast<int> ((log2(currState.size())));
    int row_size = static_cast<int>(sqrt(currState.size()));
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
    if(x->currState.back()!=0)
      counter++;
    for(unsigned i =0; i< x->currState.size()-1; i++)
    {
      if(x->currState.at(i) != i+1 && x->currState.at(i)!=0)
        counter++;
    }
    return counter;
  }

//Calculates the manhattan distance from goal state
  int manhattan(State* x)
  {
    //1 --- Making goal state
    vector< vector<int> > goalState(x->currState.size());
    int row_size = static_cast<int> ((log2(x->currState.size())));
    int col_size = x->currState.size() / row_size;
    vector<int> row (row_size);
    vector< vector<int> > puzzle(x->currState.size());
    vector<int> x_row(row_size);
    unsigned int k=1;
    for(unsigned i=0; i<row_size; i++)
    {
      for(unsigned j =0; j<col_size; j++)
      {
        row.at(j)=k;
        x_row.at(j) = x->currState.at(k-1);
        k++;
      }
      goalState.at(i) = row;
      puzzle.at(i) = x_row;
    }
    goalState.at(row_size-1).at(col_size-1) = 0;
    
    /*-- :Debugging: ---*/
    // cout << "\n\n\n";
    // for(unsigned i=0; i<row_size; i++)
    // {
    //   for(unsigned j =0; j<col_size; j++)
    //   {
    //     cout << puzzle.at(i).at(j) <<"," << goalState.at(i).at(j) << '\t';
    //   }
    //   cout << endl;
    // }

    //2 -- Calculating Manhattan Distance
    int dist=0;

    for(int i=0; i<row_size; i++)
    {
    for(int j=0; j<col_size; j++)
    {
      if(puzzle.at(i).at(j)!=0)
      {
        for(int m=0; m<row_size; m++)
        {
        for(int n=0; n<col_size; n++)
        {
          if(puzzle.at(i).at(j) == goalState.at(m).at(n))
          {
            dist += abs(i-m) + abs(j-n);
            // continue;
          }
        }
        }
      }
    }
    }
	  return dist;
  }
};


// int main()
// { 

    //Testing for states class
    // vector<int> v;
    // vector<int> v2;

    // for(unsigned i=0; i<8; i++)
    // {
    //     v.push_back(i+1);
    // }
    // v.push_back(0);
    // for(int i=7; i>=0; i--)
    // {
    //     v2.push_back(i+1);
    // }
    // v2.push_back(0);

    // State *c = new State(v2);
    // State *curr = new State(v);
    // State *c3 = new State(v2);
    // for(unsigned i=0; i<8; i++)
    // {
    //   v.at(i) = i+1;
    // }
    // v.at(v.size()-1) = 0;
    // State *c4 = new State(v);

    // //--------------- BASIC TESTS ---------------
    // cout << "\nC1:\n";
    // c->display();
    // cout << "\n\n\n";
    
    // cout << "\nC2:\n";
    // curr->display();
    // cout << "\n\n\n";
        
    // cout << "\nC3:\n";
    // c3->display();
    // cout << "\n\n\n";

    // cout << "\nC4:\n";
    // c4->display();
    // cout << "\n\n\n";

    // cout << "\n\nV2 == V ?? --> " << (v2==v) << " | V2!=V ?? --> " << (v2!=v) << "\n";
    // cout << "IS C1 = goal? " << c->isGoal() << endl;
    // cout << "IS C2 = goal? " << curr->isGoal() << endl;
    // cout << "IS C3 = goal? " << c3->isGoal() << endl;
    // cout << "IS C4 = goal? " << c4->isGoal() << endl << endl;
    
    // cout << "Misplaced tile C1: " <<c->misplacedTile(c) << endl;
    // cout << "Misplaced tile C2: " <<curr->misplacedTile(curr) << endl;
    // cout << "Misplaced tile C3: " <<c3->misplacedTile(c3) << endl;
    // cout << "Misplaced tile C4: " <<c4->misplacedTile(c4) << endl;

    //---------------Tests for Misplaced tiles and Manhattan heuristic---------------
    // vector<int> a = {7,2,4,5,0,6,8,3,1};
    // State *x = new State(a);
    //  a = {1,2,4,3,0,6,7,8,5};
    // State *y = new State(a);
    // x->display();
    // y->display();
    // cout << "Misplaced tile for X: " << x->misplacedTile(x) << endl;
    // cout << "Manhattan for X: " << x->manhattan(x) << endl;
    // cout << "Misplaced tile for Y: " << y->misplacedTile(y) << endl;
    // cout << "Manhattan for Y: " << y->manhattan(y) << endl;


//    return 0;
// }

