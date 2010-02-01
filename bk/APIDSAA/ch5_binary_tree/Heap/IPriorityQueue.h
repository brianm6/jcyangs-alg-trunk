// Module Name: IPrioirtyQueue.h
// Objective: provide the interface for priority queue
// Author: jcyang[at]ymail.com
// Date: 30.Jan.2010
// Revision: alpha

template<class Elem, class Priority>
class IPriorityQueue {
public:
	virtual bool insert(const Elem elem, const Priority priority) = 0;
	virtual bool getNext(Elem& elem) = 0;
	virtual bool peekNext(Elem& elem) = 0;
};
