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
	bool isForward() const;
	bool isBackward() const;
	bool isConnected() const;
	operator int();
private:
	EdgePointer* it;
	int value;
};