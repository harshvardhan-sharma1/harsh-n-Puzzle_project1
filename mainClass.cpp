#include "StateClass.cpp"
#include "NodeClass.cpp"
#include "nextNodeClass.cpp"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>
typedef shared_ptr<Node> nodePtr;
typedef vector<nodePtr> NodeList;
class Solve
{
    public:
    
private:
	NodeList _openlist;
	NodeList _closedlist;
	const State& _goal;
	bool solved;

public:
    enum Type
	{
		ASTAR_MANHATTAN = 0,
		UNIFORM_COST_SEARCH,
		ASTAR_MISPLACED,
	};
private:
    Type _type;
    
public:
    
	Solve( State& first, const State& goal, int i) : _goal(goal), solved(false)
	{
        if(i==0)
            _type = UNIFORM_COST_SEARCH;
        else if(i==1)
            _type = ASTAR_MISPLACED;
        else
            _type = ASTAR_MANHATTAN;

		nodePtr root(new Node(first, nullptr, 0));
		_openlist.push_back(root);
	}

	virtual ~Solve()
	{
	}

	bool isSolved() const
	{
		return solved;
	}

    bool isPresent(State& a, vector<shared_ptr<Node> >& list)
    {
        for(unsigned i=0; i<list.size(); i++)
        {
            if(a == list.at(i)->getState())
                return true;
        }
        return false;
    }

	bool isSolvable(State& state)
	{
		int count = 0;
		vector<int> arr = state.getState();
		for (unsigned int i = 0; i < arr.size()-1; i++)
        {
			for (unsigned int j = i + 1; j < arr.size(); j++)
			{	// Value 0 is used for empty space 
				if (arr.at(j) && arr.at(i) && arr.at(i)> arr.at(j))
					count++;
            }
        }
		return (count % 2 == 0);
	}

    class CompareManHattan
    {
    public:
        bool operator()(const shared_ptr<Node>& n1, const shared_ptr<Node>& n2) const
        {
            State& state1 = n1->getState();
            int cost1 = state1.manhattan(state1) + n1->getDepth();
            State& state2 = n2->getState();
            int cost2 = state2.manhattan(state2) + n2->getDepth();

            return cost1 < cost2;
        }
    };

    class CompareMisplacedTile
    {
    public:
        bool operator()(const shared_ptr<Node>& n1, const shared_ptr<Node>& n2) const
        {
            State& state1 = n1->getState();
            int cost1 = state1.misplacedTile(state1) + n1->getDepth();
            State& state2 = n2->getState();
            int cost2 = state2.misplacedTile(state2) + n2->getDepth();

            return cost1 < cost2;
        }
    };
	///Returns next node in the search
    nodePtr GetNextNode()
	{
		if (_openlist.empty()) return 0;
		nodePtr current;

		switch (_type)
		{
			case UNIFORM_COST_SEARCH:
		{
			current = _openlist[0];
			_openlist.erase(_openlist.begin());
			_closedlist.push_back(current);

			break;
		}

		case ASTAR_MANHATTAN:
		{
			NodeList::iterator current_itr(min_element(_openlist.begin(), _openlist.end(), CompareManHattan()));

			if (current_itr == _openlist.end())
                return 0;

			//copy the value first to a shared pointer and then erase from the open list.
			current = *current_itr;

			// now erase from the open list.
			_openlist.erase(current_itr);
			_closedlist.push_back(current);

			break;
		}

        case ASTAR_MISPLACED:
		{
			NodeList::iterator current_itr(min_element(_openlist.begin(), _openlist.end(), CompareMisplacedTile()));

			if (current_itr == _openlist.end())
                return 0;

			//copy the value first to a shared pointer and then erase from the open list.
			current = *current_itr;

			// now erase from the open list.
			_openlist.erase(current_itr);
			_closedlist.push_back(current);

			break;
        }
	    }
        return current;
    }
    

	// expand the graph by looking into the neighbours for the given node.
	void ExpandNode(nodePtr current, nextNodeClass& graph)
	{
		if (current->getState() == _goal)
		{
			solved = true;
			return;
		}

		int zero_index = current->getState().findEmptyTile();
        vector<int> neighbours = graph.getNextNode(zero_index);

		for (int next : neighbours)
		{
			State state = current->getState();
			state.Swap(zero_index, next);
            cout << "\n"; state.display(); cout << "\n";

			if (!isPresent(state, _closedlist))
			{
				nodePtr n(new Node(state, current, current->getDepth() + 1));
				_openlist.push_back(n);
				//static int s_lineNum = 1;
				//n->print(std::cout, s_lineNum++);
				//_closedlist.push_back(n);
			}
		}
	}


};


int main(int argc, char* argv[])
{
	srand(time(0));
	nextNodeClass g;

    vector<int> v={ 1, 2, 3, 4, 5, 0, 7, 6, 8};
    vector<int> g0al={ 1, 2, 3, 4, 5, 6, 7, 8, 0 };
    State goal(g0al);
	State start(v);


	std::cout << "Start State:\n";
	start.display();
	std::cout << "Solving puzzle...\n";
	std::shared_ptr<Node> node;
	Solve solver(start, goal, 2);
	int count = 0;
	while (!solver.isSolved())
	{
		node = solver.GetNextNode();
		solver.ExpandNode(node, g);
        cout << "after expand node\n";
		count++;
        if(count == 25)
            break;
	}

	// accumulate the nodes for the solution.
	vector<nodePtr> solution;
	nodePtr s = node;
	do
	{
		solution.push_back(s);
		s = s->getParent();
	} while (s != NULL);

	// print the solution.
	std::cout << "The puzle can be solved in " << solution.size() - 1 << " steps. Solution below\n";
	for (int i = (int)solution.size() - 1; i >= 0; i--)
	{
		solution[i]->getState().display();
        cout << "\n";
	}
	std::cout << "\n";

	return 0;
}