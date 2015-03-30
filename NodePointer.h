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

class Node;
class NodePointer
{
public:
	typedef vector<Node>::iterator NodeItr;
	NodePointer(NodeItr);
	NodePointer(int = 0);
	const Node& operator*() const;
	const Node* operator->() const;
	NodeItr it;
};