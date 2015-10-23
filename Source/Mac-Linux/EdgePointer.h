#pragma once
#include <map>
#include <string>
#include "Edge.h"
using namespace std;

namespace vp
{
	class EdgePointer
	{
	public:
		typedef map<string, Edge>::iterator EdgeItr;
		EdgePointer(EdgeItr);
		const Edge& operator*() const;
		const Edge* operator->() const;
		EdgeItr it;
	};
}