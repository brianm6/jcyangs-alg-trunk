// Module Name: BitSet.h
// Objective: prvoide the bit access interface implementation
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Reivision: alpha
// TODO: support [] operator

#ifndef __BITSET__
#define __BITSET__

#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include "hType.h"
using namespace std;

class BitSet {
	friend std::ostream& operator<< ( std::ostream& out, BitSet bits ) {
		out << bits.toString();
		return out;
	}
	friend std::ostream& operator<< ( std::ostream& out, BitSet* bits ) {
		out << bits->toString();
		return out;
	}
private:
	uint length;
	uchar* data;
public:
	BitSet(uint bitlen) {
		length = bitlen;
		uint bytelen = (uint)ceil((double)bitlen / 8);
		data = new uchar[bytelen];
		memset(data, 0, sizeof(uint) * bytelen);
	}

	BitSet(std::string bitstr, bool debug) {
		cout << "BEGIN " << endl;
		length = bitstr.length();
		cout << length << endl;
		cout << bitstr << endl;
		cout << "before abc " << endl;
		string abc(bitstr);
		cout << "abc = " << abc[0] << endl;
		cout << bitstr[1] << endl;
		// cout << bitstr.at[0] << endl;
		cout << bitstr[0] << endl;

		uint bytelen = (uint)ceil((double)(length / 8));
		cout << bytelen << endl;

		data = new uchar[bytelen];
		cout << (int)data << endl;

		for (uint i = 0; i < length; i++)  {
			cout << "before access bitstr " << endl;
			cout << bitstr[i];
			cout << "after access bitstr " << endl;
			set(length - 1 - i, bitstr[i] - '0');
		}
	}

	BitSet(std::string bitstr) {
		length = bitstr.length();
		uint bytelen = (uint)ceil((double)length / 8);
		data = new uchar[bytelen];
		for (uint i = 0; i < length; i++) 
			set(length - 1 - i, bitstr[i] - '0');
	}

	BitSet(std::string bitstr, uint bitlen) {
		length = bitlen;
		uint bytelen = (uint)ceil((double)length / 8);
		data = new uchar[bytelen];
		for (uint i = 0; i < bitlen; i++)
			set(bitlen - 1 - i, bitstr[i] - '0');
	}

	int get(uint index) {
		uchar* tbyte = data + index / 8;
		uint bitpos = index % 8; 
		return ( ( ( *tbyte >> bitpos ) & 0x01 ) != 0 ); // little endian
	}

	bool set(uint index, int value) {
		if (value != 0 && value != 1) 
			return false;

		uchar* tbyte = data + index / 8;
		int bitpos = index % 8;
		int mbit = 1;
		mbit = mbit << bitpos;
		if (value == 0) 
			*tbyte &= ~mbit;
		else 
			*tbyte |= mbit;
		return true;
	}
	
	uint getLength() {
		return length;
	}

	std::string toString() {
		std::string str;
		for (int i = length - 1; i >= 0; i--)
			str += (char)(this->get((uint)i) + '0');
		return str;
	}
};

#endif
