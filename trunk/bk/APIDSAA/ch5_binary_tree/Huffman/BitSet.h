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
		memset(data, 0, sizeof(uchar) * bytelen);
	}

	BitSet(std::string bitstr) {
		length = bitstr.length();
		uint bytelen = (uint)ceil((double)length / 8);
		data = new uchar[bytelen];
		for (uint i = 0; i < length; i++) 
			set(i, bitstr[i] - '0');
	}

	BitSet(std::string bitstr, uint bitlen) {
		length = bitlen;
		uint bytelen = (uint)ceil((double)length / 8);
		data = new uchar[bytelen];
		for (uint i = 0; i < bitlen; i++)
			set(i, bitstr[i] - '0');
	}

	int get(uint index) const {
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
	
	uint getLength() const {
		return length;
	}

	bool equal(const BitSet& bitset) {
		uint len = bitset.getLength();
		if (len != length) 
			return false;

		for (int i = 0; i < len; i++) 
			if (bitset.get(i) != get(i))
				return false;

		return true;
	}

	std::string toString() const {
		std::string str;
		for (int i = 0; i < length; ++i)
			str += (char)(this->get((uint)i) + '0');
		return str;
	}
};

#endif
