// Module Name: DecodeHuffmanTree.h
// Objective: provide the decode huffman tree implementation
// Author: jcyang[at]ymail.com
// Date: 11.Feb.2010
// Revision: alpha

#ifndef __DECODE_HUFFMAN_TREE__
#define __DECODE_HUFFMAN_TREE__

#include <iostream>
#include <vector>
#include <stdint.h>
#include "..\BST\BinNode.h"
#include "hType.h"
#include "BitWrap.h"
using namespace std;

class State {
	friend ostream& operator<<(ostream& out, State state) {
		if (state.bTerminated == true) 
			out << state.stateNum << '(' << state.ch << ')';
		else
			out << state.stateNum << "(|)";
		return out;
	}
	friend ostream& operator<<(ostream& out, State* state) {
		if (state->bTerminated == true) 
			out << state->stateNum << '(' << state->ch << ')';
		else
			out << state->stateNum << "(|)";
		return out;
	}
public:
	bool bTerminated;
	uchar ch;
	int stateNum;

	State(int num, bool bt, uchar chval = 0) 
			: stateNum(num), bTerminated(bt), ch(chval) { }
	State() { }
};

class DecodeHuffmanTree {
private:
	BinNode<uchar>* root;
	uchar* destr;
	uint length;
	State state[512][2];
	int stateNum;

	BinNode<uchar>* subDeserialize(uchar* destr, uint& len) {
		if (length >= 3 && destr[0] == 0xff && destr[1] == 0 && destr[2] == 0xff) {
			// cout << destr[0];
			len = 3;
			length -= len;
			return new BinNode<uchar>(0, NULL, NULL);
		} else if (destr[0] == 0)  {
			// cout << "|";
			uint lchildLen = 0;
			uint rchildLen = 0;
			BinNode<uchar>* lchild = subDeserialize(&destr[1], lchildLen);
			BinNode<uchar>* rchild = subDeserialize(&destr[1 + lchildLen], rchildLen);
			len = lchildLen + rchildLen + 1;
			length -= len;
			return new BinNode<uchar>(0, lchild, rchild);
		} else {
			// cout << destr[0];
			length -= 1;
			len = 1;
			return new BinNode<uchar>(destr[0], NULL, NULL);
		}
	}
	
	State subConstructStateTable(BinNode<uchar>* subroot) {
		if (subroot->isLeaf()) {
			State ts(stateNum, true, subroot->value);
			++stateNum;
			return ts;
		} else {
			uint currStateNum = stateNum;
			++stateNum;
			state[currStateNum][0] = subConstructStateTable(subroot->lchild);
			state[currStateNum][1] = subConstructStateTable(subroot->rchild);
			State ts(currStateNum, false);
			return ts;
		}
	}

/*	State* subConstructStateTable(BinNode<uchar>* subroot) {
		if (subroot->isLeaf()) 
			return new State(stateNum++, true, subroot->value);
		else {
			uint currStateNum = stateNum;
			++stateNum;
			state[currStateNum][0] = subConstructStateTable(subroot->lchild);
			state[currStateNum][1] = subConstructStateTable(subroot->rchild);
			return new State(currStateNum, false);
		}
	} */

	void constructStateTable() {
		subConstructStateTable(root);	
	}

	void subShowTree(BinNode<uchar>* subroot) {
		if (subroot->isLeaf()) 
			// cout << (int)subroot->value << setw(5) << subroot->value << "   ";
			cout << (int)subroot->value << " ";
		else {
			cout << '|';
			subShowTree(subroot->lchild);
			subShowTree(subroot->rchild);
		}
	}
	
public:
	DecodeHuffmanTree() { }

	DecodeHuffmanTree(uchar* destr, uint len) {
		deserialize(destr, len);
	}

	void deserialize(uchar* destr, uint len) {
		this->destr = destr;
		this->length = len;

		// for (int i = 0; i < len; ++i) 
		//	cout << (int)destr[i] << "   ";

		uint tmplen;
		root = subDeserialize(destr, tmplen);

		
		stateNum = 1;
		// show();
		constructStateTable();
	}

	void showStateTable() {
		cout << "StateNum" << setw(20) << " 0 " << setw(20) << " 1 " << endl;
		for (int i = 1; i < stateNum; i++) 
			cout << i << setw(20) << state[i][0] << setw(20) << state[i][1] << endl;
	}	

	uchar decode(string codestr, uint& codelen) {
		int charpos = 0;
		int statenum = 1;
		int currbit = codestr[charpos] - '0';
		// cout << codestr << endl;
		// cout << statenum << setw(10) << currbit << endl;
		while (state[statenum][currbit].bTerminated != true) {
			statenum = state[statenum][currbit].stateNum;
			currbit = codestr[++charpos] - '0';
		//	cout << statenum << setw(10) << currbit << endl;
		}
		codelen = charpos + 1;
		return state[statenum][currbit].ch;
	}

	inline int bit(uchar* start, uint64_t pos) {
		uint disp = pos / 8;
		uint off = pos % 8;
		//cout << "disp = " << disp << " off = " << off << endl;
		//BitWrap bitwrap(start);
		//cout << bitwrap.get(pos) << endl;
		int bit;
		__asm {
			mov eax, start;
			add eax, disp;
			mov ecx, off;
			bt [eax], ecx;
			lahf;
			and ah, 1;
			test ah, ah;
			jz zero;
			mov bit, 1;
			jmp end;
zero:
			mov bit, 0;
end:
		}
		// cout << "bit = " << bit << endl;
		return bit;
	}
			
	void decode(uchar* idata, uchar* odata, uint64_t bitlen) {
		uint64_t bitpos = 0;
		uint64_t charpos = 0;
		while (bitpos < bitlen) {
			int statenum = 1;
			int currbit = bit(idata, bitpos++);
			while (state[statenum][currbit].bTerminated != true) {
				statenum = state[statenum][currbit].stateNum;
				currbit = bit(idata, bitpos++);
			}
			odata[charpos++] = state[statenum][currbit].ch;
		}
	}

	void showTree() {
		subShowTree(root);
	}
};

#endif
