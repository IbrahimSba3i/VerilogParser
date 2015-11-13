#pragma once
#include "EdgePointer.h"
#define FORWARD_CONNECTED	1
#define BACKWARD_CONNECTED	-1
#define NOT_CONNECTED		0

namespace vp
{
	class Edge;
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
		operator bool() const;
		bool operator==(int) const;

		void setEdge(EdgePointer it);
		void connectForward();
		void connectBackward();
	private:
		EdgePointer it;
		bool connectedForward;
		bool connectedBackward;
	};
}