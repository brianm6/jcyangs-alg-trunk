// Module Name: BSTDict.h
// Objective: implmenetate the generic BSTDict base on BST
// Author: jcyang[at]ymail.com
// Date: 28.Jan.2010

#include "BST.h"

template<class Key, class Elem>
class Dict {
public:
	virtual bool add(const Key key, const Elem elem) = 0;
	virtual bool remove(const Key key, Elem& elem) = 0;
	virtual bool get(const Key key, Elem& elem) = 0;
};

template<class Key>
class KeyValue {
public:
	Key key;
	int index;
	KeyValue(Key key, int index) {
		this->key = key;
		this->index = index;
	}
	KeyValue() { }
};

template<class Key, class KComp>
class KeyValueComp {
public:
	static bool gt(KeyValue<Key> kv1, KeyValue<Key> kv2) {
		return KComp::gt(kv1.key, kv2.key);
	}
	static bool lt(KeyValue<Key> kv1, KeyValue<Key> kv2) {
		return KComp::lt(kv1.key, kv2.key);
	}
	static bool eq(KeyValue<Key> kv1, KeyValue<Key> kv2) {
		return KComp::eq(kv1.key, kv2.key);
	}
	static bool ge(KeyValue<Key> kv1, KeyValue<Key> kv2) {
		return KComp::ge(kv1.key, kv2.key);
	}
};

template<class Key, class KComp, class Elem, class EComp>
class BSTDict : public Dict<Key, Elem> {
private:
	BST< KeyValue<Key>, KeyValueComp<Key, KComp> >* bst;
	Elem* elemArr;
	KeyValue<Key>* keyValueArr;
	int size;
	int maxsize;
public:
	BSTDict(Key* initKeyArr, Elem* initElemArr, int size, int maxsize) {
		this->size = size;
		this->maxsize = maxsize;

		elemArr = new Elem[maxsize];
		keyValueArr = new KeyValue<Key>[size];
		for (int i = 0; i < size; i++) {
			elemArr[i] = initElemArr[i];
			KeyValue<Key> t(initKeyArr[i], i);
			keyValueArr[i] = t;
		}

		bst = new BST< KeyValue<Key>, KeyValueComp<Key, KComp> >((const KeyValue<Key>*)keyValueArr, size);
	}
	
	bool add(const Key key, const Elem elem) {
		if (size == maxsize) 
			return false;
		else {
			Elem e(elem);
			elemArr[++size] = e;
			KeyValue<Key> keyVal(key, size);
			bst->insert(keyVal);
		}
	}

	bool remove(const Key key, Elem& elem) {
		BinNode< KeyValue<Key> >* target;

		KeyValue<Key> keyVal(key, 0);
		if (bst->find(keyVal, target)) {
			elem = elemArr[target->value.index];
			bst->deleteElem(keyVal);
			return true;
		} else
			return false;
	}

	bool get(const Key key, Elem& elem) {
		BinNode< KeyValue<Key> >* target;
		KeyValue<Key> keyVal(key, 0);

		if (bst->find(keyVal, target)) {
			elem = elemArr[target->value.index];
			return true;
		} else 
			return false;
	}
};
