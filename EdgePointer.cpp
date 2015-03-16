#include "EdgePointer.h"
#include "Edge.h"

EdgePointer::EdgePointer(EdgeItr i) : it(i) {}
const Edge& EdgePointer::operator*() const { return it->second; }
const Edge* EdgePointer::operator->() const { return &it->second; }