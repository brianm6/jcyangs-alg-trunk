// Module Name: EncodeHuffmanTree.h
// Objective: provide the huffman encoding tree implementation
// Author: jcyang[at]ymail.com
// Date: 11.Feb.2010
// Revision: alpha

#ifndef __ENCODE_HUFFMAN_TREE__
#define __ENCODE_HUFFMAN_TREE__

#include <iostream>
#include <iomanip>
#include <vector>
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

class EncodeHuffmanTree {
protected:
	BinNode<CharWeight>* root;
	uchar* charset;
	uchar* charpos;
	uint size;
	BitSet** tbCode;
	uint* tbLen;
	vector<uchar> repStr;
	
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
        if (!subroot->isLeaf()) 
            cout << " " << setw(20) << subroot->value.weight << endl;
        else
            cout << (uint)subroot->value.ch << setw(5) << subroot->value.ch << setw(20) << subroot->value.weight << endl;  
        if (subroot->lchild != NULL) 
            subTravesal(subroot->lchild);
        if (subroot->rchild != NULL)
            subTravesal(subroot->rchild);
    }

	void subShowTree(BinNode<CharWeight>* subroot) {
		if (subroot->isLeaf()) 
			// cout << (int)subroot->value << setw(5) << subroot->value << "   ";
			cout << (int)subroot->value.ch << " ";
		else {
			cout << '|';
			subShowTree(subroot->lchild);
			subShowTree(subroot->rchild);
		}
	}

	void subSerialize(BinNode<CharWeight>* subroot) {
		if (subroot->isLeaf())  {
			if (subroot->value.ch == 0) {
				repStr.push_back(0xff);
				repStr.push_back(subroot->value.ch);
				repStr.push_back(0xff);
			} else
				repStr.push_back(subroot->value.ch);
			return ;
		} else {
			repStr.push_back(0);
			subSerialize(subroot->lchild);
			subSerialize(subroot->rchild);
		}
	}
	
public:
	EncodeHuffmanTree(const uchar* charset, const uint* weight, const uint size) {
		this->charset = new uchar[size];
		this->size = size;
		charpos = new uchar[256];

		for (uint i = 0; i < size; i++) {
			this->charset[i] = charset[i];
			charpos[charset[i]] = i;
		}

		buildHuffmanTree(charset, weight, size);
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
		
		// prepare the serialize object
		subSerialize(root);
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

	BitSet** getCodeTb() {
		return tbCode;
	}

	uint* getLenTb() {
		return tbLen;
	}
	
	vector<uchar> serialize() {
		return repStr;
	}	
	
		void travesal() {
		subTravesal(root);
	}
	
	void show() {
		travesal();
	}

	void showTree() {
		subShowTree(root);
	}

	void showCodeTb() {
		for (uint i = 0; i < size; i++) {
			cout <<  i << setw(5) << charset[i] << " :   " << tbCode[charpos[charset[i]]] << 
									setw(10) << tbLen[charpos[charset[i]]] << endl;
		}
	}
};

#endif
