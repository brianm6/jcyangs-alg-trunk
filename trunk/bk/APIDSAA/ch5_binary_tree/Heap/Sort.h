// Module Name: Sort.h
// Objective: provide the generic implementions of various sort algorithm
// Author: jcyang[at]ymail.com
// Date: 30.Jan.2010
// Revision: Alpha

#ifndef __GENERIC_SORT__
#define __GENERIC_SORT__

#include <iostream>
using namespace std;

template<class Elem>
void mySwap(Elem& e1, Elem& e2) {
	Elem te;
	te = e1;
	e1 = e2;
	e2 = te;
}

template<class Elem, class EComp>
void sort(Elem* elemArr, int size) {
	int i;
	for (i = 0; i < size; i++) {
		Elem* pMinElem = &elemArr[i];
		for (int j = i + 1; j < size; j++) {
			if (EComp::lt(elemArr[j], *pMinElem)) 
				pMinElem = &elemArr[j];
		}
		mySwap<Elem>(elemArr[i], *pMinElem);
	}
}

template<class Elem, class EComp>
void dsort(Elem* elemArr, int size) {
	int i;
	for (i = 0; i < size; i++) {
		Elem* pMinElem = &elemArr[i];
		for (int j = i + 1; j < size; j++) {
			if (EComp::gt(elemArr[j], *pMinElem)) 
				pMinElem = &elemArr[j];
		}
		mySwap<Elem>(elemArr[i], *pMinElem);
	}
}

#endif
