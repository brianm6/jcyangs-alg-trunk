// Module Name: HuffmanTree.cc
// Objective: application of the generic huffman coding tree
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Revision: alpha

#include <iostream>
#include <iomanip>
#include <bitset>
#include "HuffmanTree.h"
using namespace std;

int main()
{
	char* charset;
	int* weight;
	int size;
	int inputMethod;
	static const int sSize = 8;
	static const char sCharset[sSize] = { 'C', 'D', 'E', 'K', 'L', 'M', 'UZ";
	static const int sWeight[sSize] = { 32, 42, 120, 7, 42, 24, 37, 2 };

	cout << "input method (random = 0, manaual = 1) = ";
	cin >> inputMethod;
	
	if (inputMethod == 0) {
		charset = (char *)sCharset;
		weight = (int *)sWeight;
		size = sSize;
	} else if(inputMethod == 1) {
		cout << "size = ";
		cin >> size;
		charset = new char[size];
		weight = new int[size];

		for (int i = 0; i < size; i++) {
			cout << i <<"st char-weight pair = "; 
			cin >> charset[i] >> weight[i];
		}
	}
	
	
	HuffmanTree< bitset<32> > tree(charset, weight, size);

	cout << "+ After initialization the huffman tree is : " << endl;
	tree.travesal();
	cout <<endl;

	/*
	cout << "+ The result huffman code table is : " << endl;
	for (int i = 0; i < size; i++) {
		cout << charset[i] << setw(45) << tree.getCode(charset[i]) << setw(15) << (int)tree.getLen(charset[i]) << endl;
	}

	// HuffmanTree< bitset<32> > tree2;
	// tree2.travesal(); */
	return 0;
}
