#pragma once
#include "globals.h"
#include "EdgePointer.h"
using namespace std;

class Circuit;
class Node
{
private:
	Circuit* circuit;
    
public:
    int level;
    string type;
    string name;
	vector<EdgePointer> inputs;
	vector<EdgePointer> outputs;

	Node();
	Node(string, Circuit*);
	void setNodeType(string);
	void addOutput(EdgePointer);
	void addInput(EdgePointer);
	void assignTask(const string&, const string&);
};

