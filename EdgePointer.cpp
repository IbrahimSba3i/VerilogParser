#include "EdgePointer.h"
#include "Circuit.h"
#include "Node.h"
#include "Connection.h"
#include "Edge.h"

EdgePointer::EdgePointer(EdgeItr i) : it(i) {}
const Edge& EdgePointer::operator*() const { return it->second; }
const Edge* EdgePointer::operator->() const { return &it->second; }