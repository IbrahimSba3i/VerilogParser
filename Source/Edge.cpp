#include "Edge.h"

namespace vp
{
	Edge::Edge()
	{
		source = -1;
	}

	Edge::Edge(string name)
	{
		this->name = name;
		source = -1;
	}

	Edge& Edge::operator=(const Edge& rhs)
	{
		name = rhs.name;
		source = rhs.source;
		destinations = rhs.destinations;
		return *this;
	}

	void Edge::setSourceNode(unsigned int index)
	{
		source = index;
	}

	void Edge::addDestinationNode(unsigned int index)
	{
		destinations.push_back(index);
	}

	void Edge::disconnect()
	{
		source = -1;
		destinations.clear();
	}

	unsigned int Edge::getSource() const
	{
		return source;
	}

	unsigned int Edge::getDestination(unsigned int i) const
	{
		return destinations[i];
	}

	vector <unsigned int>* Edge::getDestinations()
	{
		return &destinations;
	}

	unsigned int Edge::nDestinations() const
	{
		return destinations.size();
	}
}