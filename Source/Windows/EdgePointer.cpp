#include "EdgePointer.h"
#include "Circuit.h"
#include "Node.h"
#include "Connection.h"
#include "Edge.h"

namespace vp
{
	EdgePointer::EdgePointer(EdgeItr i) : it(i) {}
	EdgePointer::EdgePointer() {}
	const Edge& EdgePointer::operator*() const { return it->second; }
	const Edge* EdgePointer::operator->() const { return &it->second; }
}
