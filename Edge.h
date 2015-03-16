#pragma once
#include "globals.h"
//#include "EdgePointer.h"
using namespace std;
class EdgePointer;
class Circuit;
class Edge
{
private:
	unsigned int source;
	vector<unsigned int> destinations;
	Circuit* circuit;
public:
    string name;
	Edge();
	Edge(string, Circuit*);
	Edge& operator=(const Edge&);

	unsigned int getSource() const;
	unsigned int getDestination(unsigned int) const;
    vector <unsigned int>* getDestinations();
	unsigned int nDestinations() const;

	void setSourceNode(unsigned int);
	void addDestinationNode(unsigned int);
	void disconnect();
};