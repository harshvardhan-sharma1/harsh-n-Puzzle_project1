#ifndef __NextNode__
#define __NextNode__

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <map>
#include "NodeClass.cpp"
class nextNodeClass
{
	typedef map<int, vector<int> > availableIndex;
	availableIndex _edges;
public:
void CreateGraphFor8Puzzle()
	{
		_edges.insert(make_pair(0, vector<int>{1, 3}));
		_edges.insert(make_pair(1, vector<int>{0, 2, 4}));
		_edges.insert(make_pair(2, vector<int>{1, 5}));
		_edges.insert(make_pair(3, vector<int>{4, 0, 6}));
		_edges.insert(make_pair(4, vector<int>{3, 5, 1, 7}));
		_edges.insert(make_pair(5, vector<int>{4, 2, 8}));
		_edges.insert(make_pair(6, vector<int>{7, 3}));
		_edges.insert(make_pair(7, vector<int>{6, 8, 4}));
		_edges.insert(make_pair(8, vector<int>{7, 5}));
	}
	nextNodeClass()
	{
		CreateGraphFor8Puzzle();
	}

	const vector<int> getNextNode(int id) const
	{
		availableIndex::const_iterator itr(_edges.find(id));
		if (itr != _edges.end()) 
            return itr->second;
		vector<int> s;
		return s;
	}

	
};
#endif