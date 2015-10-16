#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <queue>
using namespace std;

namespace vp
{
	class Node;
	class NodePointer
	{
	private:
		friend class Circuit;
		typedef vector<Node>::iterator NodeItr;
		NodePointer(NodeItr);
		NodePointer(int = 0);
		const Node& operator*() const;
		const Node* operator->() const;
		NodeItr it;
	};
}