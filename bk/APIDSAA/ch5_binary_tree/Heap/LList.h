// Module Name: LList.h
// Objective: provide the generic single linked-list implementation
// Author: jcyang[at]ymail.com
// Date: 2.Feb.2010
// Revision: alpha

#include <iostream>
#include "IList.h"
using namespace std;

template<class Elem>
class SNode {
public:
	Elem value;
	SNode<Elem>* next;
	
	SNode(Elem value, SNode<Elem>* next) {
		this->value = value;
		this->next = next;
	}
	SNode() { }
};

template<class Elem>
class DNode {
public:
	Elem value;
	DNode<Elem>* prev;
	DNode<Elem>* next;

	DNode(Elem value, DNode<Elem>* prev, DNode<Elem>* next) {
		this->value = value;
		this->next = next;
		this->prev = prev;
	}
	DNode() { }
}; 

template<class Elem, class EComp>
class SLList {
protected:
	SNode<Elem>* head;
	SNode<Elem>* tail;
	int size;
public:
	SLList(Elem* initArr, int size) {
		head = new SNode<Elem>[size];
		for (int i = 0; i < size; i++) {
			head[i]->value = initArr[i];
			head[i]->next = &head[i + 1];
		}
		head[size - 1]->next = NULL;
		tail = &head[size - 1];
		size = size;
	}

	SLList() { }

	bool insert(Elem elem) { }
	bool remove(Elem &elem) { }
	bool append(Elem elem) { }
	bool find(Elem &elem) { }
};

template<class Elem, class EComp>
class DLList {
protected:
	DNode<Elem>* head;
	DNode<Elem>* tail;
	int size;
public:
	DLList(Elem initArr, int size) {
		/* Elem* tmpArr = new Elem[size];
		for (int i = 0; i < size; i++) 
			tmpArr[i] = initArr[i];
		sort<Elem, EComp>(tmpArr, size); */
		
		this->size = size;
		head = new DNode<Elem>[size];
		for (int i = 0; i < size; i++) {
			head[i].value = tmpArr[i];
			head[i].prev = &head[i - 1];
			head[i].next = &head[i + 1];
		}
		tail = &head[size - 1];
		head->prev = NULL;
		tail->next = NULL;
	}
	DLList() { }
};
