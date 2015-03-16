#include "Connection.h"

Connection::Connection() :value(0), it(NULL){}

Connection::Connection(int val) :value(val), it(NULL){}

Connection::Connection(int val, EdgePointer e) :it(&e), value(val){}

const Edge& Connection::operator*() const{	return it->operator*();}

const Edge* Connection::operator->() const{	return it->operator->();}

Connection::operator int(){	return value;}

bool Connection::isForward() const{	return (value == 1);}

bool Connection::isBackward() const{ return (value == -1);}

bool Connection::isConnected() const{ return (value == 0);}