#pragma once
#include "Edge.h"
using namespace std;

class EdgePointer
{
private:
	friend class Connection;
	friend class Node;
	friend class Circuit;
	typedef map<string, Edge>::iterator EdgeItr;
	EdgePointer(EdgeItr);
	const Edge& operator*() const;
	const Edge* operator->() const;
	EdgeItr it;
};