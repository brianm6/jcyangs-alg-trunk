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
#include <stdint.h>
#include "hType.h"

class BitWrap {
private:
	uchar* data;
public:
	BitWrap(uchar* startaddr) {
		data = startaddr;
	}

	void reset(uchar* startaddr) {
		data = startaddr;
	}

	int get(uint64_t index) {
		uchar* tbyte = data + index / 8;
		uint bitpos = index % 8; 
		return ( ( ( *tbyte >> bitpos ) & 0x01 ) != 0 ); // little endian
	}

	bool set(uint64_t index, int value) {
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
	
	bool set(uint64_t index, BitSet bitset) {
		uint bitsetLen = bitset.getLength();
		if (bitsetLen == 0)
			return false;
		for (uint i = 0; i < bitsetLen; i++)
			if (!set(index++, bitset.get(i))) 
				return false;
		return true;
	}

	BitSet* getBitSet(uint64_t index, uint len) {
		BitSet* bitset = new BitSet(len);
		for (uint i = 0; i < len; i++) 
			bitset->set(i, get(index++));
		return bitset;
	}
};

#endif
