// Module Name: HuffmanTree.cc
// Objective: test application of the generic huffman coding tree
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
	uchar* charset;
	uint* weight;
	uint size;
	int inputMethod;

	static const uint sSize = 8;
	static const uchar sCharset[sSize] = { 'C', 'D', 'E', 'K', 'L', 'M', 'U', 'Z' };
	static const uint sWeight[sSize] = { 32, 42, 120, 7, 42, 24, 37, 2 };

	cout << "input method (random = 0, manaual = 1) = ";
	cin >> inputMethod;
	
	if (inputMethod == 0) {
		charset = (uchar*)sCharset;
		weight = (uint*)sWeight;
		size = sSize;
	} else if(inputMethod == 1) {
		cout << "size = ";
		cin >> size;
		charset = new uchar[size];
		weight = new uint[size];

		for (uint i = 0; i < size; i++) {
			cout << i <<"st char-weight pair = "; 
			cin >> charset[i] >> weight[i];
		}
	}
	
	
	HuffmanTree tree((const uchar*)charset, (const uint*)weight, size);

	cout << "+ After initialization the huffman tree is : " << endl;
	tree.travesal();
	cout << endl;

	cout << "+ The result huffman code table is : " << endl;
	tree.showCodeTb();
	cout << endl;

	HuffmanTree tree2(true);
	cout << "+ The Default huffman alpha coding tree is : " << endl;
	tree2.travesal(); 
	cout << endl << "+ The default huffman coding table is " << endl;
	tree2.showCodeTb();
	return 0;
}
