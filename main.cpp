#include "Circuit.h"
#include "ParseError.h"

using namespace std;


Circuit circuit;

int main()
{
	try{
		circuit.parseFile("code6.txt");
		
		cout << endl << " Adjacency matrix: " << endl << endl;
		for (int i = 0; i < circuit.getNodesCount(); i++){
			cout << " ";
			for (int j = 0; j < circuit.getNodesCount(); j++){
				cout << circuit[i][j];
			}
			cout << endl;
		}

		cout << endl;
		int o = 78; cout << " "; while (o--) cout << "-"; cout << endl;

		for (int i = 0; i < circuit.getNodesCount(); i++){	
			cout << " Node " << i << endl;
			cout << "  name:      " << circuit.node(i).getName() << endl;
			cout << "  type:      " << circuit.node(i).getType() << endl;
			cout << "  is input:  " << (circuit.node(i).isInputPort() ? "Yes" : "No") << endl;
			cout << "  is output: " << (circuit.node(i).isOutputPort() ? "Yes" : "No") << endl;
			int o = 78; cout << " "; while (o--) cout << "-"; cout << endl;
		}

		cout << endl << endl;
	}
	catch (ParseError& e)
	{
		cout << "ParseError: " << e.what() << endl;
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	system("pause");
	return 0;
}