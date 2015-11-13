#include "Circuit.h"
#include "EdgePointer.h"
#include "ParseError.h"

namespace vp
{
	Circuit::Circuit()
	{
		emptyNodesCounter = 0;
	}

	Circuit::Circuit(const string& filename)
	{
		emptyNodesCounter = 0;

		parseFile(filename);
	}

	Circuit::Circuit(const string& filename, const string& delaysFileName)
	{
		emptyNodesCounter = 0;

		parseFile(filename);
		parseDelaysFile(delaysFileName);
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
		nodes.push_back(Node(port, this));
		if (delays.count(nodes[nodes.size() - 1].getType())){
			nodes[nodes.size() - 1].setTRise(delays[nodes[nodes.size() - 1].getType()].first);
			nodes[nodes.size() - 1].setTFall(delays[nodes[nodes.size() - 1].getType()].second);
		}
	}

	void Circuit::parseFile(const string& fileName)
	{
		if (!verifyFile(fileName)) throw ParseError("File not found");
		string line;
		ifstream inputFile(fileName.c_str());

		inputFile >> line;
		while (line != "module") inputFile >> line;
		getline(inputFile, line);
		int openBracketIndex = line.find("(");
		moduleName = line.substr(1, openBracketIndex - 1);

		string osp = "[\\t\\n\\r ]*";
		string sp = "[\\t\\n\\r ]+";
		string delayPart = "((?:#\\(" + osp + "([0-9.]+)" + osp + "," + osp + "([0-9.]+)" + osp + "\\))?)";
		regex wirePattern("(input|output|inout|reg|wire)" + osp + "(\\[\\d+\\:\\d+\\])?" + sp + "(\\w+)");
		regex gatePattern("([A-Za-z0-9]+)" + sp + delayPart + osp + "([_0-9a-zA-z]+)?" + osp + "\\(([^]+)\\)");
		regex assignPatern("assign (.+) = 1'b(0|1);");
		smatch match;
		while (getline(inputFile, line, ';')){

			int commentIndex = line.find("//");
			int nwlnIndex = line.find("\n");
			if (nwlnIndex != -1 && commentIndex != -1 && nwlnIndex > commentIndex){
				line.erase(commentIndex, nwlnIndex - commentIndex + 1);
			}

			if (regex_search(line, match, wirePattern)){
				// parsing the array operator[7:0]
				string arr = match[2].str();
				if (arr.size()){
					int colonIndex = arr.find(":");
					int firstNumber = atoi(arr.substr(1, colonIndex - 1).c_str());
					int secondNumber = atoi(arr.substr(colonIndex + 1, arr.size() - 1 - colonIndex).c_str());
					if (firstNumber < secondNumber) swap(firstNumber, secondNumber);
					for (int i = firstNumber; i >= secondNumber; i--)
						insertNewEdge(match[3].str() + "[" + to_string(i) + "]", match[1].str());
				}
				else
					insertNewEdge(match[3].str(), match[1].str());
			}
			else if (regex_search(line, match, gatePattern)){
				insertNewNode(match[5], match[1], match[6], match[3], match[4]);
			}
			else if (regex_search(line, match, assignPatern)){
				edges[match[1].str()] = Edge(match[1].str(), this);
				string constval = (match[2].str() == "1") ? "CONST_ONE" : "CONST_ZERO";
				if (!nodeIndex.count(constval))
					insertNode(constval);
				edges[match[1].str()].setSourceNode(nodeIndex[constval]);
			}
		}
		inputFile.close();

		buildAdjacencyMatrix();


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

	void Circuit::insertNewNode(const string& nodeName, const string& nodeType, const string& portDescription, const string& trise, const string& tfall)
	{
		insertNode(nodeName == "" ? (string("UNKNOWN_GATE_") + to_string(emptyNodesCounter++)) : nodeName);
		nodes[nodes.size() - 1].assignTask(nodeType, portDescription, trise, tfall);
	}

	vector<Connection>& Circuit::operator[](size_t index)
	{
		if (index >= connections.size())  throw out_of_range("Index out of range");
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
		if (!nodeIndex.count(nodeName)) throw invalid_argument("Node \"" + nodeName + "\" not found");
		return node(nodeIndex[nodeName]);
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

	void Circuit::buildAdjacencyMatrix()
	{
		connections.resize(nodes.size(), vector<Connection>(nodes.size()));
		for (int i = 0; i < connections.size(); i++){
			for (int j = 0; j < nodes[i].outputs.size(); j++){
				for (int k = 0; k < nodes[i].outputs[j]->nDestinations(); k++){
					connections[i][nodes[i].outputs[j]->getDestination(k)].setEdge(nodes[i].outputs[j]);
					connections[nodes[i].outputs[j]->getDestination(k)][i].setEdge(nodes[i].outputs[j]);
					connections[i][nodes[i].outputs[j]->getDestination(k)].connectForward();
					connections[nodes[i].outputs[j]->getDestination(k)][i].connectBackward();
				}
			}
		}
	}

	void Circuit::parseDelaysFile(const string& fileName)
	{
		if (!verifyFile(fileName)) throw ParseError("File not found");

		ifstream inputFile(fileName.c_str());

		string gateType;
		double d1, d2;
		while (inputFile >> gateType >> d1 >> d2){
			delays[gateType] = make_pair(d1, d2);
		}

		for (int i = 0; i < getNodesCount(); i++){
			if (delays.count(node(i).getType())){
				if (node(i).getTRise() == 0)
					node(i).setTRise(delays[node(i).getType()].first);
				if (node(i).getTFall() == 0)
					node(i).setTFall(delays[node(i).getType()].second);
			}
		}

		inputFile.close();
	}

	size_t Circuit::getGatesCount() const {
		return getNodesCount() - getInputNodesCount() - getOutputNodesCount();
	}

	size_t Circuit::getNodeIndex(const string& nodeName) const {
		return nodeIndex.at(nodeName);
	}
}