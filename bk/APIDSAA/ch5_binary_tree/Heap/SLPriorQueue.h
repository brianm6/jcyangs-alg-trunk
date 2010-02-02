// Module Name: SLPriorQueue.h
// Objective: provide the generic implementation of sorted list priority queue
// Author: jcyang[at]ymail.com
// Date: 29.Jan.2010
// Revisoin: Alpha

#include <iostream>
#include "IPriorityQueue.h"
#include "AList.h"
#include "SLList.h"

template<class Elem, class Prior>
class ElemPrior {
	friend std::ostream& operator<<(std::ostream &out, ElemPrior<Elem, Prior> elemPrior) {
		out << elemPrior.elem << std::setw(20) << elemPrior.prior;
		return out;
	}
	friend std::ostream& operator<<(std::ostream &out, ElemPrior<Elem, Prior>* elemPrior) {
		out << elemPrior->elem << std::setw(20) << elemPrior.prior;
		return out;
	}
public:
	Elem elem;
	Prior prior;
	ElemPrior(const Elem elem, const Prior prior) {
		this->elem = elem;
		this->prior = prior;
	}
	ElemPrior() { }
};

template<class Elem, class Prior, class PComp>
class ElemPriorComp {
public:
	static bool gt(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::gt(e1.prior, e2.prior);
	}

	static bool ge(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::ge(e1.prior, e2.prior);
	}

	static bool lt(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::lt(e1.prior, e2.prior);
	}

	static bool eq(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::eq(e1.prior, e2.prior);
	}
};

template<class Elem, class Prior, class PComp>
class SLPriorQueue : public IPriorityQueue<Elem, Prior> {
private:
	ElemPrior<Elem, Prior>* elemPriorArr;
	// SAList< ElemPrior<Elem, Prior>, ElemPriorComp<Elem, Prior, PComp> >* elemPriorList;
	SSLList< ElemPrior<Elem, Prior>, ElemPriorComp<Elem, Prior, PComp> >* elemPriorList;
	int size;
	int maxsize;
public:
	SLPriorQueue(const Elem* initElemArr, const Prior* initPriorArr, int size, int maxsize) {
		if (size <= 0) return;
		this->size = size;
		this->maxsize = maxsize;

		elemPriorArr = new ElemPrior<Elem, Prior>[maxsize];
		for (int i = 0; i < size; i++) {
			ElemPrior<Elem, Prior> tmpElemPrior(initElemArr[i], initPriorArr[i]);
			elemPriorArr[i] = tmpElemPrior;
		}
		// elemPriorList = new SAList< ElemPrior<Elem, Prior>, ElemPriorComp<Elem, Prior, PComp> >(elemPriorArr, size, maxsize);
		elemPriorList = new SSLList< ElemPrior<Elem, Prior>, ElemPriorComp<Elem, Prior, PComp> >(elemPriorArr, size);
	}

	bool insert(const Elem elem, const Prior prior) {
		ElemPrior<Elem, Prior> elemPrior(elem, prior);
		
	    if (elemPriorList->insert(elemPrior) == true) {
			++size;
			return true;
		} else 
			return false;
	}

	bool getNext(Elem& elem) {
		ElemPrior<Elem, Prior> elemPrior;
		bool isGet;
		
		isGet = elemPriorList->removeMax(elemPrior);
		elem = elemPrior.elem;
		--size;
		
		return isGet;
	}

	bool peekNext(Elem& elem) {
		ElemPrior<Elem, Prior> elemPrior;
		bool isGet;

		isGet = elemPriorList->peekMax(elemPrior);
		elem = elemPrior.elem;

		return isGet;
	}

	void show() {
		elemPriorList->show();
	}

	size_t getSize() {
		return elemPriorList->getSize();
	}
};
