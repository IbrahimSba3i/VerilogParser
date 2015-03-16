#include "Node.h"
#include "Circuit.h"

Node::Node()
{
	
}

Node::Node(string name, Circuit* circuit)
{
	this->name = name;
	this->circuit = circuit;
	/*
	runFunction[0] = &Node::runInput;
	runFunction[1] = &Node::runOutput;
	runFunction[2] = &Node::runInout;
	runFunction[3] = &Node::runAnd;
	runFunction[4] = &Node::runOr;
	runFunction[5] = &Node::runNot;
	runFunction[6] = &Node::runNand;
	runFunction[7] = &Node::runNor;
	runFunction[8] = &Node::runXor;
	runFunction[9] = &Node::runXnor;
	runFunction[10] = &Node::runDFlipflop;
	runFunction[11] = &Node::runSRFlipflop;
	runFunction[12] = &Node::runBuffer;
	*/
}

void Node::setNodeType(string nodeType)
{
	this->type = nodeType;
}

void Node::addOutput(EdgePointer edge)
{
	outputs.push_back(edge);
}

void Node::addInput(EdgePointer edge)
{
	inputs.push_back(edge);
}

void Node::assignTask(const string& typeOfNode, const string& portsDescription)
{
	this->setNodeType(typeOfNode);
	regex pattern("\\.([A-Z]+)\\((.+?)\\),[^]+?\\.([A-Z]+)\\((.+?)\\)(?:,[^]+?\\.([A-Z]+)\\((.+?)\\))?(?:,[^]+?\\.([A-Z]+)\\((.+)\\))?(?:,[^]+?\\.([A-Z]+)\\((.+?)\\))?");
	smatch match;
	if (regex_search(portsDescription, match, pattern)){
		for (int i = 1; i < 10; i += 2){
			const string& Q = match[i].str();
			const string& W = match[i + 1].str();
			if (match[i].length() && match[i + 1].length()){
				if (match[i] == "Q" || match[i] == "Y"){
					addOutput(EdgePointer(circuit->edges.find(match[i + 1])));
					circuit->edges[match[i + 1]].setSourceNode(circuit->nodeIndex[name]);
				}
				else{
					addInput(EdgePointer(circuit->edges.find(match[i + 1])));
					circuit->edges[match[i + 1]].addDestinationNode(circuit->nodeIndex[name]);
				}
			}
		}
	}
}

/*

void Node::runInput(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runOutput(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runInout(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runAnd(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runOr(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runNot(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runNand(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runNor(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runXor(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runXnor(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runDFlipflop(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runSRFlipflop(const string& typeOfNode, const string& portsDescription)
{

}

void Node::runBuffer(const string& typeOfNode, const string& portsDescription)
{

}


regex patterns[] =	{	regex("\\.[A-Z]+\\((.+)\\),[^]+\\.[A-Z]+\\((.+)\\)"),																	// Two variables
regex("\\.[A-Z]+\\((.+)\\),\\.[A-Z]+\\((.+)\\),[^]+\\.[A-Z]+\\((.+)\\)"),												// Three variables
regex("\\.[A-Z]+\\((.+)\\),\\.[A-Z]+\\((.+)\\),\\.[A-Z]+\\((.+)\\),[^]+\\.[A-Z]+\\((.+)\\)"),							// Four variables
regex("\\.[A-Z]+\\((.+)\\),\\.[A-Z]+\\((.+)\\),\\.[A-Z]+\\((.+)\\),\\.[A-Z]+\\((.+)\\),[^]+\\.[A-Z]+\\((.+)\\)")		// Five variables
};

*/