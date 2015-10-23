#include "Connection.h"
#include <iostream>

namespace vp
{
	Connection::Connection() :value(0), it(NULL){}

	Connection::Connection(int val) : value(val), it(NULL){}

	Connection::Connection(int val, EdgePointer e) : it(&e), value(val){}

	const Edge& Connection::operator*() const{ return it->operator*(); }

	const Edge* Connection::operator->() const{ return it->operator->(); }

	Connection::operator bool() const{ return (value == 1); }

	bool Connection::isConnectedForward() const{ return (value == 1); }

	bool Connection::isConnectedBackward() const{ return (value == -1); }

	bool Connection::isConnected() const{ return (value == 0); }

	ostream& operator<<(ostream& out, const Connection& c)
	{
		out << bool(c);
		return out;
	}

	bool Connection::operator==(int x) const {
		return (value == x);
	}
}