#pragma once
#include "globals.h"
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