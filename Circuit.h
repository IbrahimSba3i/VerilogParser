#pragma once
#include "globals.h"
#include "Node.h"
#include "Edge.h"
#include "Connection.h"
#include <fstream>
#include <regex>
using namespace std;

class Circuit
{
private:
	bool verifyFile(const string&);
	void parseModuleLine(const string&);
	void insertNode(const string&);
	void insertNewEdge(const string&, const string&);
	void insertNewNode(const string&, const string&, const string&);
	vector< vector<Connection> > connections;
	vector<int> outputNodes;
	vector<int> inputNodes;
	vector<Node> nodes;
	string moduleName;
	map<string, int> nodeIndex;
	map<string, Edge> edges;
public:
	friend class Node;
	friend class Edge;

	Circuit();										
	void parseFile(const string&);						// Gets the path to the Verilog gate level netlist file
	
	vector<string> getInputPorts() const;				// Returns a vector containing the names of the input ports
	vector<string> getOutputPorts() const;				// Returns a vector containing the names of the output ports

	vector<int> getInputsIndices() const;				// Returns a vector containing the indices of the input ports in the adjacency matrix
	vector<int> getOutputsIndices() const;				// Returns a vector containing the indices of the output ports in the adjacency matrix
	
	string getModuleName() const;						// Returns the Verilog module name
	size_t getNodeIndex(const string& nodeName) const;	// Returns the index of a node
	
	vector<Connection>& operator[](size_t index);	

	Node& node(size_t index);
	Node& node(string name);
	size_t getNodesCount() const;

};

