#include "Circuit.h"
#include <iostream>

using namespace std;

int main() {
	
	// Example 3
	Circuit circuit;
	circuit.parseFile("FullAdder.v");

	// Display all the nodes in the circuit
	cout << "All nodes: " << endl;
	for (int i = 0; i < circuit.getNodesCount(); i++) {
		cout << "  " << circuit.node(i).getType() << " " << circuit.node(i).getName() << endl;
	}
	cout << endl;


	// Access a certain node
	Node X = circuit.node(6);		// access a node by its index
	Node B = circuit.node("B");		// access a node by its name
	

	// Display properties of a certain node
	cout << "Node properties:" << endl;
	cout << "  name:      " << X.getName() << endl;
	cout << "  type:      " << X.getType() << endl;
	cout << "  is input:  " << (X.isInputPort() ? "Yes" : "No") << endl;
	cout << "  is output: " << (X.isOutputPort() ? "Yes" : "No") << endl;
	cout << "  is gate:   " << (X.isGate() ? "Yes" : "No") << endl;
	cout << "  trise:     " << X.getTRise() << endl;
	cout << "  tfall:     " << X.getTFall() << endl;
	cout << endl;
	
	// Check the input connections of a certain node
	cout << "Inputs: " << endl;
	for (int i = 0; i < X.getInputsCount(); i++) {
		Node t = X.inputNode(i);
		cout << "  " << t.getType() << " " << t.getName() << endl;
	}
	cout << endl;

	// Check the output connections of a certain node
	cout << "Outputs: " << endl;
	for (int i = 0; i < X.getOutputsCount(); i++) {
		Node t = X.outputNode(i);
		cout << "  " << t.getType() << " " << t.getName() << endl;
	}
	cout << endl;

	return 0;
}

