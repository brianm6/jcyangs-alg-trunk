/// Module Name: HuffmanTree.h
// Objective: provide the generic huffman coding tree implementation
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Revision: alpha

#ifndef __GENERIC_HUFFMANTREE__
#define __GENERIC_HUFFMANTREE__

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <stdint.h>
#include "hType.h"
#include "..\BST\BinNode.h"
#include "..\Heap\Sort.h"
#include "BitSet.h"
using namespace std;

class CharWeight {
public:
	uchar ch;
	uint weight;
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
protected:
	BinNode<CharWeight>* root;
	uchar* charset;
	uchar* charpos;
	uint size;
	BitSet** tbCode;
	uint* tbLen;
	string repstr;

	void subBuildTable(BinNode<CharWeight>* subroot) {
		static string code;
		
		if (subroot->isLeaf()) {
			tbCode[charpos[subroot->value.ch]] = new BitSet(code);
			tbLen[charpos[subroot->value.ch]] = code.length(); 
			return ;
		}
		if (subroot->lchild != NULL) {
			code += '0'; 
			 subBuildTable(subroot->lchild);
			 code.erase(code.end() - 1);
		}
		if (subroot->rchild != NULL) {
			 code += '1'; 
			subBuildTable(subroot->rchild);
			 code.erase(code.end() - 1);
		}
	}

	void buildTable() {
		tbCode = new BitSet*[size];
		tbLen = new uint[size];

		for (uint i = 0; i < size; i++) {
			tbCode[i] = NULL;
			tbLen[i] = 0;
		}
		subBuildTable(root);
	}

	void subTravesal(BinNode<CharWeight>* subroot) {
		if (subroot->isLeaf()) 
			cout << " " << setw(20) << subroot->value.weight << endl;
		else
			cout << (uint)subroot->value.ch << setw(5) << subroot->value.ch << setw(20) << subroot->value.weight << endl;  
		if (subroot->lchild != NULL) 
			subTravesal(subroot->lchild);
		if (subroot->rchild != NULL)
			subTravesal(subroot->rchild);
	}

	void subSerialize(BinNode<CharWeight>* subroot) {
		static const string branchNode = "\x00\x00";
		if (subroot->isLeaf())  {
			repstr += subroot->value.ch;
			return ;
		} else {
			repstr += branchNode;
			subSerialize(subroot->lchild);
			subSerialize(subroot->rchild);
		}
	}

	BinNode<uchar>* subDeSerialize(const char* repstr) {
		if (repstr[1] == 0 && repstr[2] == 0) 
			return new BinNode<uchar>(0, subDeSerialize(&repstr[3]), subDeSerialize(&repstr[4]));
		else 
			return new BinNode<uchar>(*repstr, NULL, NULL);
	}

public:
	HuffmanTree(const uchar* charset, const uint* weight, const uint size) {
		this->charset = new uchar[size];
		this->size = size;
		charpos = new uchar[256];

		for (uint i = 0; i < size; i++) {
			this->charset[i] = charset[i];
			charpos[charset[i]] = i;
		}

		buildHuffmanTree(charset, weight, size);
	}

	HuffmanTree() { }
	HuffmanTree(bool isdefault) {
		static const uint aSize = 26;
		static const uchar aCharset[aSize] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
		static const uint aWeight[aSize] = { 81, 14, 27, 42, 127, 22, 20, 61, 70, 2, 8, 40, 24, 67, 74, 19, 1, 60, 63, 91, 28, 10, 24, 2, 20, 1 };

		this->charset = new uchar[aSize];
		this->size = aSize;
		charpos = new uchar[256];
		for (uint i = 0; i < aSize; i++)  {
			this->charset[i] = aCharset[i];
			charpos[charset[i]] = i;
		}

		buildHuffmanTree(aCharset, aWeight, aSize);
	}

	void buildHuffmanTree(const uchar* charset, const uint* weight, const uint size) {
		BinNode<CharWeight>** sortArr;
		
		// initialize the to-be-sorted array
		sortArr = new BinNode<CharWeight>*[size];
		for (uint i = 0; i < size; i++) {
			CharWeight tmp;
			tmp.ch = charset[i];
			tmp.weight = weight[i];
			sortArr[i] = new BinNode<CharWeight>(tmp, NULL, NULL); 
		}
		
		// create the huffman coding tree
		int sortArrSize = size;
		while (sortArrSize > 1) {
			sort<BinNode<CharWeight>*, BinNodeCharWeightComparator>(sortArr, sortArrSize);		

			CharWeight sum; 
			sum.ch = NULL; 
			sum.weight = sortArr[0]->value.weight + sortArr[1]->value.weight;
			sortArr[0] = new BinNode<CharWeight>(sum, sortArr[0], sortArr[1]);
			for (int i = 1; i < sortArrSize - 1; i++) 
				sortArr[i] = sortArr[i + 1];
			--sortArrSize;
		}

		root = sortArr[0];

		// build the code and length table
		buildTable();
	}
	
	BitSet* getCode(const uchar ch) {
		return tbCode[ch];
	}

	uint getLen(const uchar ch) {
		return tbLen[ch];
	}

	uint getCodeLen(const uchar ch, BitSet*& code) {
		code = getCode(ch);
		return getLen(ch);
	}

	void travesal() {
		subTravesal(root);
	}
	
	void show() {
		travesal();
	}

	void showCodeTb() {
		for (uint i = 0; i < size; i++) {
			cout <<  i << setw(5) << charset[i] << " :   " << tbCode[charpos[charset[i]]] << 
									setw(10) << tbLen[charpos[charset[i]]] << endl;
		}
	}

	BitSet** getCodeTable() {
		return tbCode;
	}

	uint* getLenTable() {
		return tbLen;
	}
	
	string serialize() {
		return repstr;
	}	
};

#endif
