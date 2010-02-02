// Module Name: SLList.h
// Objective: provide the generic sorted link-list implementation
// Author: jcyang[at]ymail.com
// Date: 2.Feb.2010
// Revision: alpha

#include <iostream>
#include "LList.h"
#include "Sort.h"
using namespace std;

template<class Elem, class EComp>
class SSLList : SLList<Elem, EComp> {
private:
	SNode<Elem>* getPrevNode(SNode<Elem>* currNode) {
		if (currNode == head)
			return NULL;
		SNode<Elem>* travNode = head;
		while (travNode != tail) {
			if (travNode->next == currNode)
				return travNode;
			else
				travNode = travNode->next;
		}
	}
public:
	SSLList(Elem* initArr, int size) {
		this->size = size;
		Elem* tmpArr = new Elem[size];
		for (int i = 0; i < size; i++) 
			tmpArr[i] = initArr[i];
		sort<Elem, EComp>(tmpArr, size);
		head = new SNode<Elem>[size];
		for (int i = 0; i < size; i++) {
			head[i].value = tmpArr[i];
			head[i].next = &head[i + 1];
		}
		tail = &head[size - 1];
		tail->next = NULL;
	}
		
	bool insert(const Elem elem) {
		if (EComp::lt(elem, head->value)) {
			head = new SNode<Elem>(elem, head);
			++size;
			return true;
		}
		SNode<Elem>* currNode = head;
		SNode<Elem>* nextNode = head->next;
		while (currNode != tail) {
			if (EComp::lt(elem, nextNode->value))
				break;
			else {
				currNode = currNode->next;
				nextNode = nextNode->next;
			}
		}
		if (currNode != tail) 
			currNode->next = new SNode<Elem>(elem, nextNode);
		else {
			tail->next = new SNode<Elem>(elem, NULL);
			tail = tail->next;
		}
		++size;
		return true;
	}
		
	bool append(const Elem elem) {
		tail->next = new SNode<Elem>(elem, NULL);
		size++;
	}

	bool find(const Elem elem) {
		SNode<Elem>* node = head;
		if (EComp::eq(tail->value, elem)) 
			return true;
		while (node != tail) {
			if (EComp::eq(node->value, elem)) 
				return true;
			else
				node = node->next;
		}
		return false;
	}

	bool peekMax(Elem& elem) {
		elem = tail->value;
		return true;
	}

	bool removeMax(Elem& elem) {
		if (size-- == 1) {
			elem = head->value;
			delete head;
			return true;
		} else {
			elem = tail->value;
			SNode<Elem>* tmpTail = tail;
			tail = getPrevNode(tail);
			tail->next = NULL;
			delete tmpTail;
		}
	}

	bool removeMin(Elem& elem) {
		elem = *head;
		SNode<Elem>* tmpHead = head;
		head = head->next;
		delete tmpHead;
	}

	void show() {
		cout << "size = " << size << endl;
		cout << head->value << endl;
		if (head == tail)
			return ;
		SNode<Elem>* currNode = head;
		while (currNode != tail) {
			cout << currNode->next->value << endl;
			currNode = currNode->next;
		}
	}
};


template<class Elem, class EComp>
class SDLList : DLList<Elem, EComp> {
private:

public:
	SDLList(Elem* initArr, int size) {
		Elem* tmpArr = new Elem[size];
		for (int i = 0; i < size; i++) 
			tmpArr[i] = initArr[i];
		sort<Elem, EComp>(tmpArr, size);
		
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
		
	bool insert(const Elem elem) {
		if (EComp::lt(elem, head->value)) {
			head = new DNode<Elem>(elem, head, NULL);
			++size;
			return true;
		}
		DNode<Elem>* currNode = head;
		DNode<Elem>* nextNode = head->next;
		while (currNode != tail) {
			if (EComp::lt(elem, nextNode->value))
				break;
			else {
				currNode = currNode->next;
				nextNode = nextNode->next;
			}
		}
		if (currNode != tail) 
			currNode->next = new DNode<Elem>(elem, currNode, nextNode);
		else {
			tail->next = new DNode<Elem>(elem, tail, NULL);
			tail = tail->next;
		}
		++size;
		return true;
	}
		
	bool append(const Elem elem) {
		tail->next = new DNode<Elem>(elem, tail, NULL);
		size++;
	}

	bool find(const Elem elem) {
		DNode<Elem>* node = head;
		if (EComp::eq(tail->value, elem)) 
			return true;
		while (node != tail) {
			if (EComp::eq(node->value, elem)) 
				return true;
			else
				node = node->next;
		}
		return false;
	}

	bool peekMax(Elem& elem) {
		elem = tail->value;
		return true;
	}

	bool removeMax(Elem& elem) {
		if (size-- == 1) {
			elem = head->value;
			delete head;
			return true;
		} else {
			elem = tail->value;
			DNode<Elem>* tmpTail = tail;
			tail = tail->prev;
			tail->next = NULL;
			delete tmpTail;
		}
	}

	bool removeMin(Elem& elem) {
		elem = *head;
		DNode<Elem>* tmpHead = head;
		head = head->next;
		delete tmpHead;
	}

	void show() {
		cout << "size = " << size << endl;
		cout << head->value << endl;
		if (head == tail)
			return ;
		DNode<Elem>* currNode = head;
		while (currNode != tail) {
			cout << currNode->next->value << endl;
			currNode = currNode->next;
		}
	}
};
