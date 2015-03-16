#include "Edge.h"

Edge::Edge()
{
	this->circuit = NULL;
	source = UNKNOWN_INDEX;
}

Edge::Edge(string name, Circuit* circuit)
{
	this->name = name;
	this->circuit = circuit;
	source = UNKNOWN_INDEX;
}

Edge& Edge::operator=(const Edge& rhs)
{
	name = rhs.name;
	circuit = rhs.circuit;
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
	source = UNKNOWN_INDEX;
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