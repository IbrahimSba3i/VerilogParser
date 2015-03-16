#include "Circuit.h"
#include "globals.h"

using namespace std;


int main()
{
    Circuit X("code1.txt");
    
    X.bfs();
    
	system("pause");
	return 0;
}
