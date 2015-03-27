#pragma once
#include "EdgePointer.h"

class Connection
{
public:
	Connection();
	Connection(int);
	Connection(int, EdgePointer);
	const Edge& operator*() const;
	const Edge* operator->() const;
	bool isConnectedForward() const;
	bool isConnectedBackward() const;
	bool isConnected() const;
	operator bool();
private:
	EdgePointer* it;
	int value;
};