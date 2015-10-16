#include <iostream>
#include "Circuit.h"
#include "ParseError.h"

using namespace std;

void printLn();

int main() {
	
	try {
		
		// Initialize Circuit
		Circuit circuit;
		circuit.parseFile("FullAdder.v");
		circuit.parseDelaysFile("gateDelays.delay");

		cout << endl << " Adjacency matrix: " << endl << endl;
		for (int i = 0; i < circuit.getNodesCount(); i++) {
			cout << "  ";

			for (int j = 0; j < circuit.getNodesCount(); j++) {
				cout << circuit[i][j];
			}
			cout << endl;
		}

		cout << endl;
		printLn();

		for (int i = 0; i < circuit.getNodesCount(); i++) {	
			cout << " Node " << i << endl;
			cout << "  name:      " << circuit.node(i).getName() << endl;
			cout << "  type:      " << circuit.node(i).getType() << endl;
			cout << "  is input:  " << (circuit.node(i).isInputPort() ? "Yes" : "No") << endl;
			cout << "  is output: " << (circuit.node(i).isOutputPort() ? "Yes" : "No") << endl;
			cout << "  is gate:   " << (circuit.node(i).isGate() ? "Yes" : "No") << endl;
			cout << "  trise:     " << circuit.node(i).getTRise() << endl;
			cout << "  tfall:     " << circuit.node(i).getTFall() << endl;
			printLn();
		}


		
	}
	catch (ParseError& e) {
		cout << "ParseError: " << e.what() << endl;
	}
	catch (exception& e) {
		cout << e.what() << endl;
	}

	cout << endl << endl;

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}

void printLn() {
	int o = 78;
	cout << " ";
	while (o--) {
		cout << "-";
	}
	cout << endl;
}