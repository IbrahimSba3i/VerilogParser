#pragma once
#include <map>
#include <string>
using namespace std;

namespace vp
{
	class Node;
	class Connection;
	class Circuit;
	class Edge;
	class EdgePointer
	{
	private:
		friend class Connection;
		friend class Node;
		friend class Circuit;
		typedef map<string, Edge>::iterator EdgeItr;
		EdgePointer(EdgeItr);
		EdgePointer();
		const Edge& operator*() const;
		const Edge* operator->() const;
		EdgeItr it;
	};
}