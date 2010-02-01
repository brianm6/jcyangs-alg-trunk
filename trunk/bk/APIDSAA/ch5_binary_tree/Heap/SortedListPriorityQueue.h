// Module Name: SLPriorQueue.h
// Objective: provide the generic implementation of sorted list priority queue
// Author: jcyang[at]ymail.com
// Date: 29.Jan.2010
// Revisoin: Alpha

#include "PriorityQueue.h"
#include "AList.h"

template<class Elem, class Prior>
class ElemPrior {
public:
	Elem elem;
	Prior prior;
	ElemPrior(const Elem elem, const Prior prior) {
		this->elem = elem;
		this->prior = prior;
	}
};

template<class Elem, class Prior, class PComp>
class ElemPriorComp {
public:
	bool gt(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::gt(e1.prior, e2.prior);
	}

	bool ge(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::ge(e1.prior, e2.prior);
	}

	bool lt(ElemPrior<Elem, Prior> e1, ElemPrior<Elem, Prior> e2) {
		return PComp::lt(e1.prior, e2.prior);
	}
};

template<class Elem, class Prior, class PComp>
class SLPriorQueue : public IPriorityQueue<Elem, Prior> {
private:
	ElemPrior<Elem, Prior>* elemPriorArr;
	SAList< ElemPrior<Elem, Prior>, ElemPriorComp<Elem, Prior, PComp> >* elemPriorList;
	int size;
	int maxsize;
public:
	SLPriorQueue(const Elem* initElemArr, const Prior* intPriorArr, int size, int maxsize) {
		if (size <= 0) return;
		this->size = size;
		this->maxsize = maxsize;

		elemPriorArr = new ElemPrior[maxsize];
		for (int i = 0; i < size; i++)
			elemPriorArr[i] = new ElemPrior(initElemArr[i], initPriorArr[i]);
		elemPriorArr = new SAList< ElemPrior<Elem, Prior>, ElemPriorComp<Elem, Prior, PComp> >(elemPriorArr, size, maxsize);
	}

	bool insert(const Elem elem, const Prior prior) {
		ElemPrior<Elem, Prior> elemPrior(elem, prior);
		return elemPriorList.insert(elemPrior);
	}

	bool getNext(Elem& elem) {
		ElemPrior<Elem, Prior> elemPrior;
		bool isGet;
		
		isGet = elemPriorList.removeMax(elemPrior);
		elem = elemPrior.elem;
		
		return isGet;
	}

	bool peekNext(Elem& elem) {
		ElemPrior<Elem, Prior> elemPrior;
		bool isGet;

		isGet = elemPriorList.findMax(elemPrior);
		elem = elemPrior.elem;

		return isGet;
	}
};
