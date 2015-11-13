#include "Connection.h"
#include "EdgePointer.h"
#include "Edge.h"
#include <iostream>

namespace vp
{
	Connection::Connection() : connectedForward(0), connectedBackward(0), it() {}

	Connection::Connection(int val) : connectedForward(0), connectedBackward(0), it() {}

	Connection::Connection(int val, EdgePointer e) : it(e), connectedForward(0), connectedBackward(0){}

	const Edge& Connection::operator*() const{ return it.operator*(); }

	const Edge* Connection::operator->() const{ return it.operator->(); }

	Connection::operator bool() const{ return connectedForward; }

	bool Connection::isConnectedForward() const{ return connectedForward; }

	bool Connection::isConnectedBackward() const{ return connectedBackward; }

	bool Connection::isConnected() const{ return (connectedForward && connectedBackward); }

	ostream& operator<<(ostream& out, const Connection& c)
	{
		out << bool(c);
		return out;
	}

	bool Connection::operator==(int x) const {
		if (x == 1) {
			return connectedForward;
		}
		else if (x == -1) {
			return connectedBackward;
		}
		else if(x == 0){
			return (!connectedForward && !connectedBackward);
		}
		else {
			return false;
		}
	}

	void Connection::setEdge(EdgePointer it) {
		this->it = it;
	}

	void Connection::connectForward() {
		this->connectedForward = true;
	}

	void Connection::connectBackward() {
		this->connectedBackward = true;
	}
}