#pragma once
#include "mydes.h"

unsigned char ByteSub(unsigned char input_byte)
{
	unsigned char temp = sBox[int(input_byte)];
	return temp;
}

unsigned char inverse_ByteSub(unsigned char input_byte)
{
	unsigned char temp = invsBox[int(input_byte)];
	return temp;
}
