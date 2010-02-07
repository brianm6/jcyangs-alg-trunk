// Module Name: HuffmanApp.cc
// Objective: demonstrate the application of huffman coding tree
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Reivision: alpha

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "HuffmanTree.h"
using namespace std;

int* buildWeightTable(ifstream& infile) 
{
	int* wt = new int[256];
	memset(wt, 0, sizeof(int) * 256);

   	while (!infile.eof()) {
		unsigned char ch;
		infile >> ch;
		wt[ch]++;
	}
	infile.set(0, ios_base::beg);
	return wt;
}

int compress(char* srcFile, char* destFile) {
	ifstream infile(srcFile);
	if (infile == NULL) {
		cout << "could not open file " << srcFile << endl;
		return -1;
	}
	int *wt = buildWeightTable(srcFile);
	
	ofstream outfile(destFile);
	if (outfile == NULL) {
		cout << "could not create file " << destFile << endl;
		return -1;
	}

	while (!infile.eof()) {
		unsigned char ch;
		infile >> ch;
		outfile << wt[ch];
	}
	for (int i = 0; i < 256; i++) 
		outfile << wt[ch];

	infile.close();
	outfile.close();

	return 0;
}

int decompress(char* srcFile, char* destFile) {
	ifstream infile(srcFile);
	if (infile == NULL) {
		cout << "+ could not open file " << srcFile << endl;
		return -1;
	}

	infile.seekg(-256, ios_base::end);
	int* wt = new int[256];
	infile.read(wt, 256);
	infile.seekg(0, ios_base::begin);

	ofstream outfile(destFile);
	if (destFile == NULL) {
		cout << "+ could not create file " << destFile << endl;
		return -1;
	}

	while (!infile.eof()) {
		unsigned char ch;
		infile >> ch;
		
}
