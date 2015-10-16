#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <queue>

using namespace std;

namespace vp
{

	class EdgePointer;
	class Circuit;
	class Node;
	class Edge
	{
	private:
		unsigned int source;
		vector<unsigned int> destinations;
		Circuit* circuit;

		string name;

		Edge(string, Circuit*);
		Edge& operator=(const Edge&);

		unsigned int getSource() const;
		unsigned int getDestination(unsigned int) const;
		vector <unsigned int>* getDestinations();
		unsigned int nDestinations() const;

		void setSourceNode(unsigned int);
		void addDestinationNode(unsigned int);
		void disconnect();

	public:
		friend class Circuit;
		friend class Node;
		Edge();
	};

}
