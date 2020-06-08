#include "md5.h"
#include<string>
#include<iostream>
# include <stdio.h>
# include <stdlib.h>



using namespace std;
MD5::MD5()
{
	//初始化MD缓冲区
	buffer[0] = 0x67452301;
	buffer[1] = 0xefcdab89;
	buffer[2] = 0x98badcfe;
	buffer[3] = 0x10325476;
}

string  MD5::pad(const char * message)
{

	int len = strlen(message);
	//x % 512 = 64;
	int lnow;
	if (len * 8 % 448 == 0)
	{
		lnow = len * 8 + 512 + 64;
	}
	else
	{
		lnow = (((len * 8 + 64) / 512) + 1) * 512 - 64 + 64;
	}
	int totalgroup = lnow / 512;
	//cout << totalgroup << "个消息分组" << endl;
	unsigned int *group = new unsigned int[totalgroup * 16];
	memset(group, 0, sizeof(unsigned int)*totalgroup * 16);

	for (int i = 0; i < len; i++)
	{
		group[i >> 2] |= message[i] << ((i % 4) * 8);
		//cout << group[i] ;
	}

	group[len >> 2] |= 0x80 << ((len % 4) * 8);
	group[totalgroup * 16 - 2] = len * 8;


	/*for (int i = 0; i < totalgroup * 16; i++)
	{
	cout << group[i];
	}
	cout << endl;*/

	string temp[100];
	for (int i = 0; i < totalgroup; i++)
	{
		unsigned int input[16];
		for (int j = 0; j < 16; j++)
		{
			input[j] = group[j + i * 16];
		}
		temp[i] = fourround(input);
	}
	return temp[totalgroup - 1];

}

string MD5::fourround(unsigned int input[16])
{
	unsigned int a = buffer[0];
	unsigned int b = buffer[1];
	unsigned int c = buffer[2];
	unsigned int d = buffer[3];

	for (int i = 0; i < 64; i++)
	{
		if (i >= 0 && i < 16)
		{
			unsigned f = F(b, c, d);

			unsigned temp = d;
			d = c;
			c = b;
			b = b + moveleft(f + a + input[i] + T[i], s[i]);
			a = temp;


		}
		if (i >= 16 && i < 32)
		{
			unsigned g = G(b, c, d);
			unsigned temp = d;
			d = c;
			c = b;
			b = b + moveleft(g + a + input[(1 + 5 * i) % 16] + T[i], s[i]);
			a = temp;
		}
		if (i >= 32 && i < 48)
		{
			unsigned h = H(b, c, d);
			unsigned temp = d;
			d = c;
			c = b;
			b = b + moveleft(h + a + input[(5 + 3 * i) % 16] + T[i], s[i]);
			a = temp;
		}
		if (i >= 48 && i < 64)
		{
			unsigned ii = I(b, c, d);
			unsigned temp = d;
			d = c;
			c = b;
			b = b + moveleft(ii + a + input[(7 * i) % 16] + T[i], s[i]);
			a = temp;
		}

	}
	buffer[0] += a;
	buffer[1] += b;
	buffer[2] += c;
	buffer[3] += d;


	//cout << buffer[0] + buffer[1] + buffer[2] + buffer[3]<<endl;
	char bufa[9], bufb[9], bufc[9], bufd[9];
	char buffa[9], buffb[9], buffc[9], buffd[9];
	char bufA[9], bufB[9], bufC[9], bufD[9];
	itoa(buffer[0], bufa, 16);   //大端小端的问题
	itoa(buffer[1], bufb, 16);
	itoa(buffer[2], bufc, 16);
	itoa(buffer[3], bufd, 16);

	if (strlen(bufa) != 8)
	{
		bufa[7] = '0';
	}
	else
	{
		for (int i = 0; i < 9; i++)
			buffa[i] = bufa[i];
	}


	if (strlen(bufb) != 8)
	{
		int x = 8 - strlen(bufb);
		for (int i = 0; i < x; i++)
			buffb[i] = '0';
		for (int i = 0; i < 9 - x; i++)
			buffb[i + x] = bufb[i];
	}
	else
	{
		for (int i = 0; i < 9; i++)
			buffb[i] = bufb[i];
	}



	if (strlen(bufc) != 8)
	{
		bufc[7] = '0';
	}
	else
	{
		for (int i = 0; i < 9; i++)
			buffc[i] = bufc[i];
	}


	if (strlen(bufd) != 8)
	{
		bufd[7] = '0';
	}
	else
	{
		for (int i = 0; i < 9; i++)
			buffd[i] = bufd[i];
	}

	/*cout << buffa << endl;
	cout << buffb << endl;
	cout << buffc << endl;
	cout << buffd << endl;*/
	//a
	bufA[0] = buffa[6];
	bufA[1] = buffa[7];
	bufA[2] = buffa[4];
	bufA[3] = buffa[5];
	bufA[4] = buffa[2];
	bufA[5] = buffa[3];
	bufA[6] = buffa[0];
	bufA[7] = buffa[1];
	//b
	bufB[0] = buffb[6];
	bufB[1] = buffb[7];
	bufB[2] = buffb[4];
	bufB[3] = buffb[5];
	bufB[4] = buffb[2];
	bufB[5] = buffb[3];
	bufB[6] = buffb[0];
	bufB[7] = buffb[1];
	//c
	bufC[0] = buffc[6];
	bufC[1] = buffc[7];
	bufC[2] = buffc[4];
	bufC[3] = buffc[5];
	bufC[4] = buffc[2];
	bufC[5] = buffc[3];
	bufC[6] = buffc[0];
	bufC[7] = buffc[1];
	//d
	bufD[0] = buffd[6];
	bufD[1] = buffd[7];
	bufD[2] = buffd[4];
	bufD[3] = buffd[5];
	bufD[4] = buffd[2];
	bufD[5] = buffd[3];
	bufD[6] = buffd[0];
	bufD[7] = buffd[1];

	string result;
	for (int i = 0; i < 8; i++)
	{

		//cout << bufA[i];
		result += bufA[i];
	}
	for (int i = 0; i < 8; i++)
	{
		//cout << bufB[i];
		result += bufB[i];
	}
	for (int i = 0; i < 8; i++)
	{
		//cout << bufC[i];
		result += bufC[i];
	}
	for (int i = 0; i < 8; i++)
	{
		//cout << bufD[i];
		result += bufD[i];
	}

	//cout << endl;
	return result;

}

char * MD5::transfer(unsigned int B)
{
	char bufa[9];
	char buffa[9];
	char bufA[9];

	itoa(B, bufa, 16);   //转化为16进制

	if (strlen(bufa) != 8)  //补零
	{
		int x = 8 - strlen(bufa);
		for (int i = 0; i < x; i++)
			buffa[i] = '0';
		for (int i = 0; i < 9 - x; i++)
			buffa[i + x] = bufa[i];
	}
	else
	{
		for (int i = 0; i < 9; i++)
			buffa[i] = bufa[i];
	}

	bufA[0] = buffa[6];   //大端小端问题
	bufA[1] = buffa[7];
	bufA[2] = buffa[4];
	bufA[3] = buffa[5];
	bufA[4] = buffa[2];
	bufA[5] = buffa[3];
	bufA[6] = buffa[0];
	bufA[7] = buffa[1];

	return bufA;
}

