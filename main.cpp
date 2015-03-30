#include "Circuit.h"
#include "ParseError.h"

using namespace std;

bool calculateValue(int currentNodeIndex);
bool calculateNodeValue(Node& n);
bool simulateGate(string nodeType, const vector<bool>& inputs);
bool calculate_or(const vector<bool>& inputs);
bool calculate_buf(const vector<bool>& inputs);
bool calculate_inv(const vector<bool>& inputs);
bool calculate_nand(const vector<bool>& inputs);
bool calculate_xnor(const vector<bool>& inputs);
bool calculate_nor(const vector<bool>& inputs);
bool calculate_xor(const vector<bool>& inputs);
bool calculate_and(const vector<bool>& inputs);

Circuit circuit;
map<string, bool> inputValues;
int main()
{
	try{
		circuit.parseFile("code6.txt");
		inputValues["ci"] = 1;
		inputValues["x[0]"] = 1;
		inputValues["x[1]"] = 0;
		inputValues["y[0]"] = 1;
		inputValues["y[1]"] = 1;

		// Using the adjacency matrix to traverse the circuit
		for (int i = 0; i < circuit.getNodesCount(); i++)
		{
			if (circuit.node(i).isOutputPort())
			{
				bool result = calculateValue(i);
				cout << circuit.node(i).getName() << ": " << result << endl;
			}
		}

		cout << "\n";

		// Using the nodes to traverse the circuit
		for (int i = 0; i < circuit.getOutputNodesCount(); i++)
		{
			bool result = calculateNodeValue(circuit.outputNode(i));
			cout << circuit.outputNode(i).getName() << ": " << result << endl;
		}

		cout << "\n";
	}
	catch (ParseError& e)
	{
		cout << "ParseError: " << e.what() << endl;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "Unknown error" << endl;
	}

	system("pause");
	return 0;
}

bool calculate_or(const vector<bool>& inputs)
{
	bool result = inputs[0];
	for (int i = 1; i < inputs.size(); i++)
		result = result || inputs[i];

	return result;
}

bool calculate_and(const vector<bool>& inputs)
{
	bool result = inputs[0];
	for (int i = 1; i < inputs.size(); i++)
		result = result && inputs[i];

	return result;
}

bool calculate_xor(const vector<bool>& inputs)
{
	bool result = inputs[0];
	for (int i = 1; i < inputs.size(); i++)
		result = result ^ inputs[i];

	return result;
}
bool calculate_nor(const vector<bool>& inputs)
{
	return !calculate_or(inputs);
}

bool calculate_xnor(const vector<bool>& inputs)
{
	return !calculate_xor(inputs);
}

bool calculate_nand(const vector<bool>& inputs)
{
	return !calculate_and(inputs);
}

bool calculate_inv(const vector<bool>& inputs)
{
	return !inputs[0];
}

bool calculate_buf(const vector<bool>& inputs)
{
	return inputs[0];
}

bool simulateGate(string nodeType, const vector<bool>& inputs)
{
	bool result = false;
	for (int i = 0; i < nodeType.size(); i++)
	{
		if (nodeType[i] >= 'A' && nodeType[i] <= 'Z')
			nodeType[i] += 32;
	}

	if (nodeType.substr(0, 2) == "or")
	{
		result = calculate_or(inputs);
	}
	else if (nodeType.substr(0, 3) == "and")
	{
		result = calculate_and(inputs);
	}
	else if (nodeType.substr(0, 3) == "xor")
	{
		result = calculate_xor(inputs);
	}
	else if (nodeType.substr(0, 3) == "nor")
	{
		result = calculate_nor(inputs);
	}
	else if (nodeType.substr(0, 4) == "nand")
	{
		result = calculate_nand(inputs);
	}
	else if (nodeType.substr(0, 4) == "xnor")
	{
		result = calculate_xnor(inputs);
	}
	else if (nodeType.substr(0, 3) == "inv")
	{
		result = calculate_inv(inputs);
	}
	else if (nodeType.substr(0, 3) == "buf")
	{
		result = calculate_buf(inputs);
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

	if (circuit.node(currentNodeIndex).isInputPort())
	{
		return inputValues[circuit.node(currentNodeIndex).getName()];
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

	return result;
}

bool calculateNodeValue(Node& n)
{
	bool result = false;

	if (n.isInputPort())
	{
		return inputValues[n.getName()];
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

	return result;
}