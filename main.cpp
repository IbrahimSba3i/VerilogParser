#include "Circuit.h"
#include "globals.h"

using namespace std;

bool calculateValue(int currentNodeIndex);
bool calculateGate(string nodeType, vector<bool> inputs);
bool calculateOr(vector<bool> inputs);
bool calculateBuf(vector<bool> inputs);
bool calculateInv(vector<bool> inputs);
bool calculateNand(vector<bool> inputs);
bool calculateXnor(vector<bool> inputs);
bool calculateNor(vector<bool> inputs);
bool calculateXor(vector<bool> inputs);
bool calculateAnd(vector<bool> inputs);

Circuit circuit;

int main()
{
	circuit.parseFile("code1.txt");
	
	circuit.node("ci").setValue(1);
	circuit.node("x[0]").setValue(1);
	circuit.node("x[1]").setValue(0);
	circuit.node("y[0]").setValue(1);
	circuit.node("y[1]").setValue(1);


	for (int i = 0; i < circuit.getNodesCount(); i++)
	{
		if (circuit.node(i).isOutputPort())
		{
			bool result = calculateValue(i);
			cout << circuit.node(i).getName() << ": " << result << endl;
		}
	}
    
	system("pause");
	return 0;
}

bool calculateOr(vector<bool> inputs)
{
	bool result = inputs[0];
	for (int i = 1; i < inputs.size(); i++)
		result = result || inputs[i];

	return result;
}

bool calculateAnd(vector<bool> inputs)
{
	bool result = inputs[0];
	for (int i = 1; i < inputs.size(); i++)
		result = result && inputs[i];

	return result;
}

bool calculateXor(vector<bool> inputs)
{
	bool result = inputs[0];
	for (int i = 1; i < inputs.size(); i++)
		result = result ^ inputs[i];

	return result;
}
bool calculateNor(vector<bool> inputs)
{
	return !calculateOr(inputs);
}

bool calculateXnor(vector<bool> inputs)
{
	return !calculateXor(inputs);
}

bool calculateNand(vector<bool> inputs)
{
	return !calculateAnd(inputs);
}

bool calculateInv(vector<bool> inputs)
{
	return !inputs[0];
}

bool calculateBuf(vector<bool> inputs)
{
	return inputs[0];
}

bool calculateGate(string nodeType, vector<bool> inputs)
{
	bool result = false;
	if (nodeType.substr(0, 2) == "OR")
	{
		result = calculateOr(inputs);
	}
	else if (nodeType.substr(0, 3) == "AND")
	{
		result = calculateAnd(inputs);
	}
	else if (nodeType.substr(0, 3) == "XOR")
	{
		result = calculateXor(inputs);
	}
	else if (nodeType.substr(0, 3) == "NOR")
	{
		result = calculateNor(inputs);
	}
	else if (nodeType.substr(0, 4) == "NAND")
	{
		result = calculateNand(inputs);
	}
	else if (nodeType.substr(0, 4) == "XNOR")
	{
		result = calculateXnor(inputs);
	}
	else if (nodeType.substr(0, 3) == "INV")
	{
		result = calculateInv(inputs);
	}
	else if (nodeType.substr(0, 3) == "BUF")
	{
		result = calculateBuf(inputs);
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
		result = calculateGate(nodeType, inputs);
	}

	circuit.node(currentNodeIndex).setValue(result);
	return result;
}