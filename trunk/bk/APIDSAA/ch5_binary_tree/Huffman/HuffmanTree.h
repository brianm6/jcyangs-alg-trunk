// Module Name: HuffmanTree.h
// Objective: provide the generic huffman coding tree implementation
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Revision: alpha

#include <iostream>
#include "..\BST\BinNode.h"
#include "..\Heap\Sort.h"
using namespace std;

class CharWeight {
public:
	char ch;
	int weight;
};

class BinNodeCharWeightComparator {
public:
	static bool gt(BinNode<CharWeight>* e1, BinNode<CharWeight>* e2) {
		return e1->value.weight > e2->value.weight;
	}
	static bool lt(BinNode<CharWeight>* e1, BinNode<CharWeight>* e2) {
		return e1->value.weight < e2->value.weight;
	}
};

class HuffmanTree {
private:
	BinNode<CharWeight>* root;
	int size;
	bitset<32>* tbCode;
	int* tbLen;
	
	void subBuildTable(BinNode<CharWeight>* subroot) {
		static bitset<32> code;
		static int len;

		if (subroot->isLeaf()) {
			bitset<32> tcode;
			for (int i = 0; i < len; i++) 
				tcode[i] = code[len - 1 - i];
			tbCode[subroot->value.ch] = tcode;
			tbLen[subroot->value.ch] = len;
			return ;
		}
		if (subroot->lchild != NULL) {
			code[len++] = 0;
			subBuildTable(subroot->lchild);
			--len;
		}
		if (subroot->rchild != NULL) {
			code[len++] = 1;
			subBuildTable(subroot->rchild);
			--len;
		}
	}

	void buildTable() {
		tbCode = new bitset<32>[255];
		tbLen = new int[255];
		subBuildTable(root);
	}

	void subTravesal(BinNode<CharWeight>* subroot) {
		cout << subroot->value.ch << setw(20) << subroot->value.weight << endl;
		if (subroot->lchild != NULL) 
			subTravesal(subroot->lchild);
		if (subroot->rchild != NULL)
			subTravesal(subroot->rchild);
	}
public:
	HuffmanTree(char* charset, int* weight, int size) {
		BinNode<CharWeight>** sortArr;
		
		this->size = size;
		sortArr = new BinNode<CharWeight>*[size];
		for (int i = 0; i < size; i++) {
			CharWeight tmp;
			tmp.ch = charset[i];
			tmp.weight = weight[i];
			sortArr[i] = new BinNode<CharWeight>(tmp, NULL, NULL); 
		}

		int sortSize = size;
		while (sortSize > 1) {
			sort<BinNode<CharWeight>*, BinNodeCharWeightComparator>(sortArr, sortSize);		
			CharWeight sum; 
			sum.ch = NULL; 
			sum.weight = sortArr[0]->value.weight + sortArr[1]->value.weight;
			sortArr[0] = new BinNode<CharWeight>(sum, sortArr[0], sortArr[1]);
			for (int i = 1; i < size; i++) 
				sortArr[i] = sortArr[i + 1];
			--sortSize;
		}

		root = sortArr[0];

		buildTable();
		delete [] sortArr;
	}
	
	bitset<32> getCode(const char ch) {
		return tbCode[ch];
	}

	int getLen(const char ch) {
		return tbLen[ch];
	}

	int getCodeLen(const char ch, bitset<32>& code) {
		code = getCode(ch);
		return getLen(ch);
	}

	void travesal() {
		subTravesal(root);
	}
};
