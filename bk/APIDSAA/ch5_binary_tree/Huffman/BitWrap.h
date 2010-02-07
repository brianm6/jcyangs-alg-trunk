// Module Name: BitWrap.h
// Objective: prvoide the bit access interface implementation
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Reivision: alpha
// TODO: support [] operator

#ifndef __BIT_WRAP__
#define __BIT_WRAP__

#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include "hType.h"

class BitWrap {
	friend std::ostream& operator<< ( std::ostream& out, BitSet bits ) {
		out << bits.toString();
		return out;
	}
	friend std::ostream& operator<< ( std::ostream& out, BitSet* bits ) {
		out << bits->toString();
		return out;
	}
private:
	uchar* data;
public:
	BitWrap(uchar* startaddr) {
		data = startaddr;
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
	
};

#endif
