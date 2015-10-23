#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <queue>
//#include "Circuit.h"

using namespace std;

namespace vp
{
	class Edge
	{
	private:
		unsigned int source;
		vector<unsigned int> destinations;

		string name;

	public:
		Edge();
        Edge(string);
		Edge& operator=(const Edge&);
        
		unsigned int getSource() const;
		unsigned int getDestination(unsigned int) const;
		vector <unsigned int>* getDestinations();
		unsigned int nDestinations() const;
        
		void setSourceNode(unsigned int);
		void addDestinationNode(unsigned int);
		void disconnect();
	};

}
