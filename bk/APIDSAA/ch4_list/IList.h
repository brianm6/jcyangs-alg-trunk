// Module Name: IList.h
// Objective: provide the generic list interface 
// Author: jcyang[at]ymail.com
// Date: 30.Jan.2010
// Revision: Alpha

#ifndef __LIST_INTERFACE__
#define __LIST_INTERFACE__

template<class Elem>
class IList {
public:
	virtual bool insert(const Elem elem) = 0;
	virtual bool remove(Elem& elem) = 0;
};

#endif
