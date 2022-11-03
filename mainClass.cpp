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
	enum Type
	{
		DEPTH_FIRST = 0,
		BREADTH_FIRST,
		GREEDY_BEST_FIRST,
		ASTAR,
	};

private:
    Type _type;

public:
	Solve( State& first, const State& goal, Type type = Type::ASTAR)
		: _goal(goal), solved(false), _type(type)
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
	nodePtr GetNextNode()
	{
		if (_openlist.empty()) 
            return nullptr;
		
        nodePtr current;

		switch (_type)
		{
		case ASTAR:
		{
			NodeList::iterator current_itr(std::min_element(
				_openlist.begin(),
				_openlist.end(),
				CompareFunctorForAStar()));

			if (current_itr == _openlist.end()) return 0;

			//copy the value first to a shared pointer and then erase from the open list.
			current = *current_itr;

			// now erase from the open list.
			_openlist.erase(current_itr);
			_closedlist.push_back(current);

			break;
		}
		case GREEDY_BEST_FIRST:
		{
			NodeList::iterator current_itr(std::min_element(
				_openlist.begin(),
				_openlist.end(),
				CompareFunctorForGreedyBestFirst()));

			if (current_itr == _openlist.end()) return 0;

			//copy the value first to a shared pointer and then erase from the open list.
			current = *current_itr;

			// now erase from the open list.
			_openlist.erase(current_itr);
			_closedlist.push_back(current);

			break;
		}
		case BREADTH_FIRST:
		{
			current = _openlist[0];
			_openlist.erase(_openlist.begin());
			_closedlist.push_back(current);

			break;
		}
		case DEPTH_FIRST:
			//current = _openlist[0];
			NodeList::iterator current_itr(_openlist.begin());
			if (current_itr == _openlist.end()) return 0;

			//copy the value first to a shared pointer and then erase from the open list.
			current = *current_itr;

			// now erase from the open list.
			_openlist.erase(current_itr);
			_closedlist.push_back(current);

			break;
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