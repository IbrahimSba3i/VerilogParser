#pragma once
#include "EdgePointer.h"

#define FORWARD_CONNECTED	1
#define BACKWARD_CONNECTED	-1
#define NOT_CONNECTED		0

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