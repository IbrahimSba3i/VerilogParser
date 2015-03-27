#pragma once
#include "globals.h"
#include "Edge.h"
using namespace std;

class EdgePointer
{
public:
	typedef map<string, Edge>::iterator EdgeItr;
	EdgePointer(EdgeItr);
	const Edge& operator*() const;
	const Edge* operator->() const;
	EdgeItr it;
};