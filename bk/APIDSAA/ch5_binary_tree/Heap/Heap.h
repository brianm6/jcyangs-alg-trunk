// Module Name: Heap.h
// Objective: provide the generic heap implementation 
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Revision: alpha

#ifndef __GENERIC_HEAP__
#define __GENERIC_HEAP__

#include <iostream>
#include "..\BST\BinNode.h"
#include "Sort.h"
using namespace std;

template<class Elem, class EComp>
class MaxHeap {
private:
	Elem* elemArr;
	int size;
	int maxsize;

	void siftDown(int pos) {
		while (pos < size) {
			int maxchild = (EComp::gt(elemArr[2 * pos], elemArr[2 * pos + 1])) ? 2 * pos : 2 * pos + 1;
			if (EComp::gt(elemArr[maxchild], elemArr[pos])) {
				swap<Elem>(elemArr[maxchild], elemArr[pos]); 
				pos = maxchild;
			} else
				return ;
		}
	}

	void siftUp(int pos) {
		while (pos > 0) {
			int father = pos / 2;
			if (EComp::gt(elemArr[pos], elemArr[father])) {
				swap<Elem>(elemArr[pos], elemArr[father]);
				pos = father;
			} else
				return ;
		}
	}
		
public:
	MaxHeap(const Elem* initArr, int size, int maxsize) {
		this->size = size;
		this->maxsize = maxsize;

		elemArr = new Elem[maxsize];
		for (int i = 0; i < size; i++) 
			elemArr[i] = initArr[i];
		// sort<Elem, EComp>(elemArr, size);
		dsort<Elem, EComp>(elemArr, size);	
	}

	bool peekMax(Elem& elem) {
		if (size == 0)
			return false;
   		elem = elemArr[0];
		return true;
	}

	bool removeMax(Elem& elem) {
   		if (size == 0)
			return false;
		else {
			elem = elemArr[0];
			elemArr[0] = elemArr[size - 1];
			siftDown(0);
			--size;
		}
	}

	bool insert(const Elem elem) {
		if (size == maxsize)
			return false;

		elemArr[size] = elem;
		siftUp(size);
		++size;
		return true;
	}

	void show() {
		cout << "size = " << size << endl;
		for (int i = 0; i < size; i++) 
			cout << elemArr[i] << endl;
	}
};

#endif
