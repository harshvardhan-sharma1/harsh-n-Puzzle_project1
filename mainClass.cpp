#include "StateClass.cpp"
#include "NodeClass.cpp"
#include "nextNodeClass.cpp"
class Solve
{
private:
    typedef shared_ptr<Node> nodePtr;
	typedef vector<nodePtr> NodeList;
	NodeList _openlist;
	NodeList _closedlist;
	const State& _goal;
	bool solved;
    
public:
	Solve( State& first, const State& goal) : _goal(goal), solved(false)
	{
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

	///Returns next node in the search
	

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