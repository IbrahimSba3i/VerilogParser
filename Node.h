#pragma once
#include "globals.h"
#include "EdgePointer.h"
using namespace std;

class Circuit;

/*
	Node class represents an input/output port or a gate 
*/

class Node
{
private:
	Circuit* circuit;
	int level;
	string type;
	string name;
	vector<EdgePointer> inputs;
	vector<EdgePointer> outputs;
	void setNodeType(string);
	void addOutput(EdgePointer);
	void addInput(EdgePointer);
	void assignTask(const string&, const string&);

	bool resultValue;
	bool valueSet;

	Node();
	Node(string, Circuit*);

public:
	friend class Circuit;
	friend class Edge;

	string getName() const;				// Returns the input or gate name
	string getType() const;				// Returns the type of the gate

	bool isInputPort() const;
	bool isOutputPort() const;

	bool getValue() const;
	void setValue(bool resultValue);
	bool isValueSet() const;
};

