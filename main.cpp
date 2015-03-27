#include "Circuit.h"
#include "globals.h"

using namespace std;

bool calculateValue(int currentNodeIndex);
bool calculateNodeValue(Node& n);
bool simulateGate(string nodeType, const vector<bool>& inputs);
bool or(const vector<bool>& inputs);
bool buf(const vector<bool>& inputs);
bool inv(const vector<bool>& inputs);
bool nand(const vector<bool>& inputs);
bool xnor(const vector<bool>& inputs);
bool nor(const vector<bool>& inputs);
bool xor(const vector<bool>& inputs);
bool and(const vector<bool>& inputs);

Circuit circuit;

int main()
{
	circuit.parseFile("code1.txt");
	
	circuit.node("ci").setValue(1);
	circuit.node("x[0]").setValue(1);
	circuit.node("x[1]").setValue(0);
	circuit.node("y[0]").setValue(1);
	circuit.node("y[1]").setValue(1);


	// Using the adjacency matrix to traverse the circuit
	for (int i = 0; i < circuit.getNodesCount(); i++)
	{
		if (circuit.node(i).isOutputPort())
		{
			bool result = calculateValue(i);
			cout << circuit.node(i).getName() << ": " << result << endl;
		}
	}
    
	// Using the nodes to traverse the circuit
	for (int i = 0; i < circuit.getOutputNodesCount(); i++)
	{
		bool result = calculateNodeValue(circuit.outputNode(i));
		cout << circuit.outputNode(i).getName() << ": " << result << endl;
	}
	system("pause");
	return 0;
}

bool or(const vector<bool>& inputs)
{
	bool result = inputs[0];
	for (int i = 1; i < inputs.size(); i++)
		result = result || inputs[i];

	return result;
}

bool and(const vector<bool>& inputs)
{
	bool result = inputs[0];
	for (int i = 1; i < inputs.size(); i++)
		result = result && inputs[i];

	return result;
}

bool xor(const vector<bool>& inputs)
{
	bool result = inputs[0];
	for (int i = 1; i < inputs.size(); i++)
		result = result ^ inputs[i];

	return result;
}
bool nor(const vector<bool>& inputs)
{
	return !or(inputs);
}

bool xnor(const vector<bool>& inputs)
{
	return !xor(inputs);
}

bool nand(const vector<bool>& inputs)
{
	return !and(inputs);
}

bool inv(const vector<bool>& inputs)
{
	return !inputs[0];
}

bool buf(const vector<bool>& inputs)
{
	return inputs[0];
}

bool simulateGate(string nodeType, const vector<bool>& inputs)
{
	bool result = false;
	if (nodeType.substr(0, 2) == "OR")
	{
		result = or(inputs);
	}
	else if (nodeType.substr(0, 3) == "AND")
	{
		result = and(inputs);
	}
	else if (nodeType.substr(0, 3) == "XOR")
	{
		result = xor(inputs);
	}
	else if (nodeType.substr(0, 3) == "NOR")
	{
		result = nor(inputs);
	}
	else if (nodeType.substr(0, 4) == "NAND")
	{
		result = nand(inputs);
	}
	else if (nodeType.substr(0, 4) == "XNOR")
	{
		result = xnor(inputs);
	}
	else if (nodeType.substr(0, 3) == "INV")
	{
		result = inv(inputs);
	}
	else if (nodeType.substr(0, 3) == "BUF")
	{
		result = buf(inputs);
	}
	else
	{
		cout << "Unknown gate type" << endl;
		result = false;
	}
	return result;
}

bool calculateValue(int currentNodeIndex)
{
	bool result = false;

	if (circuit.node(currentNodeIndex).isValueSet())
	{
		return circuit.node(currentNodeIndex).getValue();
	}

	else if (circuit.node(currentNodeIndex).isOutputPort())
	{
		for (int i = 0; i < circuit.getNodesCount(); i++)
		{
			if (circuit[i][currentNodeIndex])
			{
				result = calculateValue(i);
				i = circuit.getNodesCount();
			}
		}
	}
	else
	{
		vector<bool> inputs;
		for (int i = 0; i < circuit.getNodesCount(); i++)
		{
			if (circuit[i][currentNodeIndex])
				inputs.push_back(calculateValue(i));
		}

		string nodeType = circuit.node(currentNodeIndex).getType();
		result = simulateGate(nodeType, inputs);
	}

	circuit.node(currentNodeIndex).setValue(result);
	return result;
}

bool calculateNodeValue(Node& n)
{
	bool result = false;

	if (n.isValueSet())
	{
		return n.getValue();
	}

	else if (n.isOutputPort())
	{
		result = calculateNodeValue(n.inputNode(0));
	}
	else
	{
		vector<bool> inputs;
		for (int i = 0; i < n.getInputsCount(); i++)
			inputs.push_back(calculateNodeValue(n.inputNode(i)));

		string nodeType = n.getType();
		result = simulateGate(nodeType, inputs);
	}

	n.setValue(result);
	return result;
}