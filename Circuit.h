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
	void parseFile(const string&);
	void parseModuleLine(const string&);
	void insertNode(const string&);
	void insertNewEdge(const string&, const string&);
	void insertNewNode(const string&, const string&, const string&);
public:
	vector< vector<Connection> > connections;
	vector<unsigned int> outputNodes;
	vector<unsigned int> inputNodes;
	vector<Node> nodes;
	string moduleName;
	map<string, int> nodeIndex;
	map<string, Edge> edges;
	Circuit(string);
	void bfs();
};

