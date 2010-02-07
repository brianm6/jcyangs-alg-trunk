// Module Name: HuffmanTree.h
// Objective: provide the generic huffman coding tree implementation
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Revision: alpha

#ifndef __GENERIC_HUFFMANTREE__
#define __GENERIC_HUFFMANTREE__

#include <iostream>
#include <iomanip>
#include <bitset>
#include <cstdio>
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

template<class CodeBitSet>
class HuffmanTree {
protected:
	BinNode<CharWeight>* root;
	int size;
	CodeBitSet* tbCode;
	unsigned char* tbLen;
	BinNode<CharWeight>** sortArr;

	void subBuildTable(BinNode<CharWeight>* subroot) {
		static CodeBitSet code(0);
		static int len;

		if (subroot->isLeaf()) {
			// CodeBitSet tcode;
			// for (int i = 0; i < len; i++) 
			//	tcode[i] = code[len - 1 - i];
			tbCode[subroot->value.ch] = code;
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
		tbCode = new CodeBitSet[size];
		tbLen = new unsigned char[size];
		subBuildTable(root);
	}

	void subTravesal(BinNode<CharWeight>* subroot) {
		if (subroot->value.ch == 0) 
			cout << " " << setw(20) << subroot->value.weight << endl;
			// cout << subroot->value.weight;
		else
			cout << subroot->value.ch << setw(20) << subroot->value.weight << endl;  
		// printf("%c %s\n", subroot->value.ch, subroot->value.weight);
		// printf("good haha");
		if (subroot->lchild != NULL) 
			subTravesal(subroot->lchild);
		if (subroot->rchild != NULL)
			subTravesal(subroot->rchild);
	}
public:
	HuffmanTree(char* charset, int* weight, int size) {
		buildHuffmanTree(charset, weight, size);
	}

	HuffmanTree() {
		static const int aSize = 26;
		static const char aCharset[aSize] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		static const int aWeight[aSize] = { 81, 14, 27, 42, 127, 22, 20, 61, 70, 2, 8, 40, 24, 67, 74, 19, 1, 60, 63, 91, 28, 10, 24, 2, 20, 1 };

		buildHuffmanTree((char*)aCharset, (int*)aWeight, aSize);
	}

	void buildHuffmanTree(char* charset, int* weight, int size) {
		
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
			for (int i = 1; i < size - 1; i++) 
				sortArr[i] = sortArr[i + 1];
			--sortSize;
		}

		root = sortArr[0];

		buildTable();
	}
	
	CodeBitSet getCode(const char ch) {
		return tbCode[ch];
	}

	unsigned char getLen(const char ch) {
		return tbLen[ch];
	}

	int getCodeLen(const char ch, CodeBitSet& code) {
		code = getCode(ch);
		return getLen(ch);
	}

	void travesal() {
		subTravesal(root);
	}
	
	void show() {
		travesal();
	}

	CodeBitSet* getCodeTable() {
		return tbCode;
	}

	unsigned char* getLenTable() {
		return tbLen;
	}
};

#endif

