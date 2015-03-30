#include "Circuit.h"
#include "EdgePointer.h"
#include "ParseError.h"

Circuit::Circuit()
{
	
}

bool Circuit::verifyFile(const string& fileName)
{
	ifstream in(fileName.c_str());
	if (in.fail())
		return false;
	in.close();
	return true;
}

void Circuit::parseModuleLine(const string& line)
{
	int startIndex = 0;
	while (startIndex < line.size()){
		int commaIndex = line.find(",", startIndex);
		if (commaIndex == -1) commaIndex = line.size();
		insertNode(line.substr(startIndex, commaIndex - startIndex));
		startIndex = commaIndex + 2;
	}
}

void Circuit::insertNode(const string& port)
{
	if (nodeIndex.count(port)) throw ParseError("gate " + port + " already declared");
	nodeIndex[port] = nodes.size();
	nodes.push_back(Node(port,this));
    //cout << "New Node: " << port << endl;
}

void Circuit::parseFile(const string& fileName)
{
	if (!verifyFile(fileName)) throw ParseError("File not found");
	string ignoredString, line;
	ifstream inputFile(fileName.c_str());
	getline(inputFile, ignoredString);		// ignore the comment on the first line
	inputFile >> ignoredString;				// ignore the word "module"
	getline(inputFile, line);
	int openBracketIndex = line.find("(");
	moduleName = line.substr(1, openBracketIndex - 1);

	regex pattern1("(input|output|inout|reg|wire)( \\[\\d+\\:\\d+\\])? (\\w+)");
	regex pattern2("([A-Za-z0-9]+) ([_0-9a-zA-z]+) \\(([^]+)\\)");
	regex pattern3("assign (.+) = 1'b(0|1);");
	/*
		match group 0 contains the entire string
		match group 1 contains the type of the edge
		match group 2 contains the array definition
		match group 3 contains the variable name
	*/
	smatch match;
	while (getline(inputFile, line, ';')){
		if (regex_search(line, match, pattern1)){
			// parsing the array operator[7:0]
			string arr = match[2].str();
			if (arr.size()){
				int colonIndex = arr.find(":");
				int firstNumber = atoi(arr.substr(2, colonIndex - 1).c_str());
				int secondNumber = atoi(arr.substr(colonIndex + 1, arr.size() - 1 - colonIndex).c_str());
				if (firstNumber < secondNumber) swap(firstNumber, secondNumber);
				for (int i = firstNumber; i >= secondNumber; i--)
					insertNewEdge(match[3].str() + "[" + to_string(i) + "]", match[1].str());
			}
			else
				insertNewEdge(match[3].str(), match[1].str());
		}
		else if (regex_search(line, match, pattern2))	// pattern1 doesn't match the string then it is a node
			insertNewNode(match[2], match[1], match[3]);
		else if (regex_search(line, match, pattern3)){
			edges[match[1].str()] = Edge(match[1].str(), this);
			(match[2]=="1")? edges[match[1].str()].setSourceNode(CONST_ONE) : edges[match[1].str()].setSourceNode(CONST_ZERO);
		}
	}
	connections.resize(nodes.size(), vector<Connection>(nodes.size()));
	for (int i = 0; i < connections.size(); i++){
		for (int j = 0; j < nodes[i].outputs.size(); j++){
			for (int k = 0; k < nodes[i].outputs[j]->nDestinations(); k++){
				connections[i][nodes[i].outputs[j]->getDestination(k)] = Connection(1,nodes[i].outputs[j]);
				connections[nodes[i].outputs[j]->getDestination(k)][i] = Connection(-1, nodes[i].outputs[j]);
			}
		}
	}

}

void Circuit::insertNewEdge(const string& edgeName, const string& edgeType)
{
	if (edges.count(edgeName)) throw ParseError("wire \"" + edgeName + "\" already declared");
	edges[edgeName] = Edge(edgeName, this);
	EdgePointer pointer = edges.find(edgeName);
	if (edgeType == "input"){
		insertNode(edgeName);
		int nodeIndex = nodes.size() - 1;
		inputNodes.push_back(nodeIndex);
		nodes[nodeIndex].setNodeType("INPUT_PORT");
		nodes[nodeIndex].addOutput(pointer);
		edges[edgeName].setSourceNode(nodeIndex);
	}
	else if (edgeType == "output"){
		insertNode(edgeName);
		int nodeIndex = nodes.size() - 1;
		outputNodes.push_back(nodeIndex);
		nodes[nodeIndex].setNodeType("OUTPUT_PORT");
		nodes[nodeIndex].addInput(pointer);
		edges[edgeName].addDestinationNode(nodeIndex);
	}
}

void Circuit::insertNewNode(const string& nodeName, const string& nodeType, const string& portDescription)
{
	insertNode(nodeName);
	nodes[nodes.size() - 1].assignTask(nodeType, portDescription);
}

vector<Connection>& Circuit::operator[](size_t index)
{
	return connections[index];
}

std::string Circuit::getModuleName() const
{
	return moduleName;
}

Node& Circuit::node(size_t index)
{
	if (index >= getNodesCount()) throw out_of_range("Node index out of range");
	return nodes[index];
}

Node& Circuit::node(const string& nodeName)
{
	return nodes[nodeIndex[nodeName]];
}

size_t Circuit::getNodesCount() const
{
	return nodes.size();
}

size_t Circuit::getInputNodesCount() const
{
	return inputNodes.size();
}

Node& Circuit::inputNode(size_t index)
{
	if (index >= getInputNodesCount()) throw out_of_range("Node index out of range");
	return node(inputNodes[index]);
}

size_t Circuit::getOutputNodesCount() const
{
	return outputNodes.size();
}

Node& Circuit::outputNode(size_t index)
{
	if (index >= getOutputNodesCount()) throw out_of_range("Node index out of range");
	return node(outputNodes[index]);
}
