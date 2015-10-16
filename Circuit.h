#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <queue>
#include "Node.h"
#include "Edge.h"
#include "Connection.h"
using namespace std;

namespace vp
{

	class Circuit
	{
	private:
		bool verifyFile(const string&);
		void parseModuleLine(const string&);
		void insertNode(const string&);
		void insertNewEdge(const string&, const string&);
		void insertNewNode(const string&, const string&, const string&, const string&, const string&);
		void buildAdjacencyMatrix();
		vector< vector<Connection> > connections;
		vector<int> outputNodes;
		vector<int> inputNodes;
		vector<Node> nodes;
		string moduleName;
		map<string, int> nodeIndex;
		map<string, Edge> edges;
		map<string, pair<double, double> > delays;
		int emptyNodesCounter;
	public:
		friend class Node;
		friend class Edge;

		Circuit();
		Circuit(const string&);
		Circuit(const string&, const string&);
		void parseFile(const string&);						// Gets the path to the Verilog gate level netlist file
		void parseDelaysFile(const string&);

		vector<string> getInputPorts() const;				// Returns a vector containing the names of the input ports
		vector<string> getOutputPorts() const;				// Returns a vector containing the names of the output ports

		string getModuleName() const;						// Returns the Verilog module name

		vector<Connection>& operator[](size_t index);

		Node& node(size_t index);
		Node& node(const string& name);
		size_t getNodesCount() const;
		size_t getNodeIndex(const string& nodeName) const;	// Returns the index of a node

		Node& outputNode(size_t index);
		size_t getOutputNodesCount() const;

		Node& inputNode(size_t index);
		size_t getInputNodesCount() const;

		size_t getGatesCount() const;
	};

}