// Module Name: wBitSet.h
// Objective: prvoide the bit access interface implementation
// Author: jcyang[at]ymail.com
// Date: 3.Feb.2010
// Platform: Win32
// Reivision: alpha

#include <windows.h>

class BitSet {
private:
	PBYTE start;
public:
	BitSet(PBYTE data) {
		start = data;
	}

	int getBit(int index) {
		PBYTE tbyte += index / 8;
		int bitpos = index % 8;
		return ( ( ( tbyte << (bitpos - 1) ) & 0x80 ) != 0)
	}

	void setBit(int index, int value) {
		PBYTE tbyte += index / 8;
		int bitpos = index % 8;
		int mbit = 1;
		mbit << bitpos;
		if (value == 0) {
			tbyte
		if (value == 0) {


	}

